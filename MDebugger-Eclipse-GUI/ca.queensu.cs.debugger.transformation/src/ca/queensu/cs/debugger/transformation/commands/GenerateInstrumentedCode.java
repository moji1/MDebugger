package ca.queensu.cs.debugger.transformation.commands;

import java.io.IOException;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.URIUtil;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.EAnnotation;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.emf.ecore.util.EcoreUtil;
import org.eclipse.emf.transaction.RecordingCommand;
import org.eclipse.emf.transaction.TransactionalEditingDomain;
import org.eclipse.emf.transaction.util.TransactionUtil;
import org.eclipse.epsilon.common.parse.problem.ParseProblem;
import org.eclipse.epsilon.common.util.StringProperties;
import org.eclipse.epsilon.emc.emf.EmfModel;
import org.eclipse.epsilon.eol.EolModule;
import org.eclipse.epsilon.eol.IEolExecutableModule;
import org.eclipse.epsilon.eol.exceptions.EolRuntimeException;
import org.eclipse.epsilon.eol.exceptions.models.EolModelLoadingException;
import org.eclipse.epsilon.eol.execute.context.Variable;
import org.eclipse.epsilon.eol.models.IModel;
import org.eclipse.epsilon.eol.models.IRelativePathResolver;
import org.eclipse.jface.dialogs.ErrorDialog;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.papyrus.editor.PapyrusMultiDiagramEditor;
import org.eclipse.papyrus.infra.core.resource.ModelSet;
import org.eclipse.papyrus.infra.core.services.ServiceException;
import org.eclipse.papyrus.infra.core.services.ServicesRegistry;
import org.eclipse.papyrus.infra.emf.utils.EMFHelper;
import org.eclipse.papyrusrt.codegen.UMLRTCodeGenerator;
import org.eclipse.papyrusrt.codegen.config.CodeGenProvider;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.FileDialog;
import org.eclipse.ui.IEditorPart;
import org.eclipse.ui.console.ConsolePlugin;
import org.eclipse.ui.console.IConsole;
import org.eclipse.ui.console.IConsoleManager;
import org.eclipse.ui.console.MessageConsole;
import org.eclipse.ui.console.MessageConsoleStream;
import org.eclipse.ui.handlers.HandlerUtil;
import org.eclipse.uml2.uml.Element;
import org.eclipse.uml2.uml.Model;

public class GenerateInstrumentedCode extends AbstractHandler {

	protected IEolExecutableModule module;
	protected List<Variable> parameters = new ArrayList<Variable>();
	
	protected Object result;
	
	private org.eclipse.emf.common.util.URI uri;
	
	public IEolExecutableModule createModule() {
		return new EolModule();
	}
	  
	public List<IModel> getModels() throws Exception {
		List<IModel> models = new ArrayList<IModel>();
		String namespaceURI = 	"http://www.eclipse.org/uml2/5.0.0/UML," +
								"http://www.eclipse.org/papyrus/umlrt/cppproperties," +
								"http://www.eclipse.org/papyrus/umlrt," +
								"http://www.eclipse.org/emf/2002/Ecore," +
								"http://www.eclipse.org/papyrus/umlrt/statemachine," +
								"http://www.eclipse.org/papyrus/infra/gmfdiag/css"
				;
		models.add(createEmfModelByURI("UMLRTModel", "UMLRTModel", uri, 
				namespaceURI, true, true));
		models.add(createEmfModelByURI("UMLRTModel", "DebuggingAgent", org.eclipse.emf.common.util.URI.createPlatformResourceURI("/CommGateWay/model.uml", true), 
				namespaceURI, true, true));
		//models.add(createEmfModelByURI("DebuggingAgent", "DebuggingAgent", uri.toString(), 
		//		namespaceURI, true, true));
		return models;
	}
	  
	  public void postProcess() {};
	  
	  public void preProcess() {};
	  
	  
	@Override
	public Object execute(ExecutionEvent event) throws ExecutionException {
		
		// first step: copy the model
		
		IEditorPart editor = HandlerUtil.getActiveEditor(event);

		
		ModelSet modelSet = null;
		final ResourceSet resourceSet = new ResourceSetImpl();
		Object result = null;
		
		if (!(editor instanceof PapyrusMultiDiagramEditor)) {
			return null;
		}
		
		ServicesRegistry services = ((PapyrusMultiDiagramEditor)editor).getServicesRegistry();
		try {
			modelSet = services.getService(ModelSet.class);
		} catch (ServiceException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		TransactionalEditingDomain editingDomain = TransactionUtil.getEditingDomain(modelSet);
		
		
		
		ISelection sel = HandlerUtil.getCurrentSelection(event);
		if (sel instanceof IStructuredSelection) {
			List<EObject> targets = new ArrayList<>();

			IStructuredSelection selection = (IStructuredSelection) sel;
			if (!selection.isEmpty()) {
				EObject eobj = EMFHelper.getEObject(selection.getFirstElement());
				Resource res = eobj.eResource();
				URI modelUri = res.getURI();
				
				String lastSegment = modelUri.trimFileExtension().lastSegment();
				URI uriDebug = modelUri.trimFileExtension().trimSegments(1).appendSegment(lastSegment+"_debug").appendFileExtension("uml");
				Resource debugRes = resourceSet.createResource(uriDebug, "uml");
				
				EcoreUtil.resolveAll(res);
				
				// copy all elements
				EcoreUtil.Copier copier = new EcoreUtil.Copier();
				Collection<EObject> umlObjects = copier.copyAll(res.getContents());
				copier.copyReferences();
				
				editingDomain.getCommandStack().execute(new RecordingCommand(editingDomain) {

					@Override
					protected void doExecute() {

						for (EObject umlObject: umlObjects) {
							if (umlObject instanceof Model) {
								Model model = (Model) umlObject;
								model.setName(model.getName() + "_debug");
							}
							debugRes.getContents().add(umlObject);
						}
						
						try {
							res.save(null);
							debugRes.save(null);
						} catch (IOException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}
					
				});
				
				
				uri = uriDebug;
				
		// second step: instrument the model
				
				String eolScript = "EOLScripts/UMLRTInstrumentv0.1.eol";
				//String eolScript = event.getParameter("ca.queensu.cs.debugger.transformation.commands.parameter.eolScript");
		        
		        if (eolScript.equals("")) {
		        	FileDialog dialog = new FileDialog(Display.getCurrent().getActiveShell(), SWT.OPEN);
		        	dialog.setFilterExtensions(new String [] {"*.eol"});
		        	eolScript = dialog.open();
		        }
		        
				uri = uriDebug;
				System.out.println(uri);
				
				MessageConsole myConsole = findConsole("MDebugger Console");
			    MessageConsoleStream out = myConsole.newMessageStream();
			    
			    
			    module = createModule();
			    try {

			    	module.parse(getFileURI(eolScript));
			    if (module.getParseProblems().size() > 0) {
			      System.err.println("Parse errors occured...");
			      for (ParseProblem problem : module.getParseProblems()) {
			        System.err.println(problem.toString());
			      }
			      return null;
			    }

				for (IModel model : getModels()) {
				  module.getContext().getModelRepository().addModel(model);
				}
			    
			    for (Variable parameter : parameters) {
			      module.getContext().getFrameStack().put(parameter);
			    }
			    
			    preProcess();
				try {
					execute(module);
				} catch (EolRuntimeException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			    postProcess();
			    
			    module.getContext().getModelRepository().dispose();

			    } catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				try {
					res.save(null);
					debugRes.save(null);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				System.out.println(debugRes);		
				
		// third step: generate the code
				
				/** The code generator. */
				System.out.println("Start generarting code");
				UMLRTCodeGenerator generator = CodeGenProvider.getDefault().get();
				generator.setRegenerate(true);
				try {
					Model model = (Model) debugRes.getContents().get(0);
					String topCapsuleName = getTopCapsuleName(model);
					targets.add(model);

					final IStatus status = generator.generate(targets, topCapsuleName, true);
//					Display.getDefault().syncExec(new Runnable() {
//						@Override
//						public void run() {
							ErrorDialog.openError(Display.getCurrent().getActiveShell(), "UML-RT Code Generator", null, status);
//						}
//					});
				} finally {
					generator.setRegenerate(false);
				}
				
			}
		}
				
		return result;
	}
	

	/**
	 * Obtains the name of the Top capsule.
	 * 
	 * @param root
	 *            - The model's root {@link Element}.
	 * @return The name of the Top capsule.
	 */
	public static String getTopCapsuleName(Element root) {
		String retVal = null;

		EAnnotation anno = root.getEAnnotation("UMLRT_Default_top");
		if (anno != null) {
			retVal = anno.getDetails().get("top_name");
		}

		return retVal != null ? retVal : "Top";
	}
	
	public List<Variable> getParameters() {
	    return parameters;
	  }
	  
	  protected Object execute(IEolExecutableModule module) 
	      throws EolRuntimeException {
	    return module.execute();
	  }
	  
      // loading EMF model
	  protected EmfModel createEmfModelByURI(String name, String aliases, 
			  org.eclipse.emf.common.util.URI uri, String metamodel, boolean readOnLoad, boolean storeOnDisposal) 
	          throws EolModelLoadingException, URISyntaxException {
	    EmfModel emfModel = new EmfModel();
	    StringProperties properties = new StringProperties();
	    properties.put(EmfModel.PROPERTY_NAME, name);
	    properties.put(EmfModel.PROPERTY_ALIASES, aliases);
	    properties.put(EmfModel.PROPERTY_METAMODEL_URI, metamodel);
	    properties.put(EmfModel.PROPERTY_MODEL_URI, uri);
	  	properties.put(EmfModel.PROPERTY_READONLOAD, readOnLoad + "");
	    properties.put(EmfModel.PROPERTY_STOREONDISPOSAL, 
	       storeOnDisposal + "");
	    emfModel.load(properties, (IRelativePathResolver) null);
	    return emfModel;
	  }
	  
	  protected java.net.URI getFileURI(String fileName) throws URISyntaxException {

		java.net.URI uri= URIUtil.fromString("file:"+fileName);
		
		if (uri.isAbsolute())
			return uri;
		
		uri = TransformUMLRTModel.class.getClassLoader().getResource("../" + fileName).toURI();
		return uri;
	  }
	  
	  private MessageConsole findConsole(String name) {
	      ConsolePlugin plugin = ConsolePlugin.getDefault();
	      IConsoleManager conMan = plugin.getConsoleManager();
	      IConsole[] existing = conMan.getConsoles();
	      for (int i = 0; i < existing.length; i++)
	         if (name.equals(existing[i].getName()))
	            return (MessageConsole) existing[i];
	      //no console found, so create a new one
	      MessageConsole myConsole = new MessageConsole(name, null);
	      conMan.addConsoles(new IConsole[]{myConsole});
	      return myConsole;
	   }

}
