package ca.queensu.cs.debugger.transformation.commands;

import java.net.URI;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.List;

import org.eclipse.core.runtime.URIUtil;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.transaction.RecordingCommand;
import org.eclipse.emf.transaction.TransactionalEditingDomain;
import org.eclipse.epsilon.common.parse.problem.ParseProblem;
import org.eclipse.epsilon.common.util.StringProperties;
import org.eclipse.epsilon.emc.emf.EmfModel;
import org.eclipse.epsilon.eol.EolModule;
import org.eclipse.epsilon.eol.IEolExecutableModule;
import org.eclipse.epsilon.eol.exceptions.EolRuntimeException;
import org.eclipse.epsilon.eol.exceptions.models.EolModelLoadingException;
import org.eclipse.epsilon.eol.models.IModel;
import org.eclipse.epsilon.eol.models.IRelativePathResolver;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.FileDialog;
import org.eclipse.ui.console.ConsolePlugin;
import org.eclipse.ui.console.IConsole;
import org.eclipse.ui.console.IConsoleManager;
import org.eclipse.ui.console.MessageConsole;
import org.eclipse.ui.console.MessageConsoleStream;
import org.eclipse.uml2.uml.Model;

public class InstrumentModelCommand {// extends RecordingCommand {

	private Resource resourceToInstrument;
	private org.eclipse.emf.common.util.URI resourceToInstrumentUri;
	private TransactionalEditingDomain domain;
	
	protected IEolExecutableModule module;

	public InstrumentModelCommand(TransactionalEditingDomain domain) {
	//	super(domain);
		this.domain = domain;
	}

//	@Override
	protected void doExecute() {
		String eolScript = "EOLScripts/UMLRTInstrumentv0.1.eol";
		
		if (eolScript.equals("")) {
        	FileDialog dialog = new FileDialog(Display.getCurrent().getActiveShell(), SWT.OPEN);
        	dialog.setFilterExtensions(new String [] {"*.eol"});
        	eolScript = dialog.open();
        }
        
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
	      return;
	    }

		for (IModel model : getModels()) {
		  module.getContext().getModelRepository().addModel(model);
		}
	    
		Object object = execute(module);
	    System.out.println(((org.eclipse.uml2.uml.Model)object).getPackagedElements());
	//	this.resourceToInstrument.save(null);
		
		GenerateCodeCommand generateCommand = new GenerateCodeCommand(domain);
		generateCommand.setInstrumentedModel((Model) object);
		generateCommand.doExecute();
		
//		domain.getCommandStack().execute(generateCommand);
		
	    module.getContext().getModelRepository().dispose();
	    

	    } catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public IEolExecutableModule createModule() {
		return new EolModule();
	}
	  
	public List<IModel> getModels() throws Exception {
		List<IModel> models = new ArrayList<IModel>();
		String namespaceURI = 	"http://www.eclipse.org/uml2/5.0.0/UML," +
								"http://www.eclipse.org/uml2/5.0.0/Types," +
								"http://www.eclipse.org/uml2/5.0.0/UML/Profile/Standard," +
								"http://www.eclipse.org/papyrus/umlrt/cppproperties," +
								"http://www.eclipse.org/papyrus/umlrt," +
								"http://www.eclipse.org/emf/2002/Ecore," +
								"http://www.eclipse.org/papyrus/umlrt/statemachine," +
								"http://www.eclipse.org/papyrus/umlrt/systemelements," +
								"http://www.eclipse.org/papyrus/infra/gmfdiag/css"
				;
		models.add(createEmfModelByURI("UMLRTModel", "UMLRTModel", this.resourceToInstrumentUri, 
				namespaceURI, true, true));
		models.add(createEmfModelByURI("UMLRTModel", "DebuggingAgent", org.eclipse.emf.common.util.URI.createPlatformResourceURI("/CommGateWay/model.uml", true), 
				namespaceURI, true, true));
//		models.add(createEmfModelByURI("UMLPrimitiveTypes", "UMLPrimitiveTypes", org.eclipse.emf.common.util.URI.createPlatformPluginURI("/org.eclipse.uml2.uml.resources/libraries/UMLPrimitiveTypes.library.uml", true), 
//				namespaceURI, true, true));
		//models.add(createEmfModelByURI("DebuggingAgent", "DebuggingAgent", uri.toString(), 
		//		namespaceURI, true, true));
		return models;
	}
	
	protected Object execute(IEolExecutableModule module)  throws EolRuntimeException {
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
	  	properties.put(EmfModel.PROPERTY_STOREONDISPOSAL, storeOnDisposal + "");
	    emfModel.load(properties, (IRelativePathResolver) null);
	    return emfModel;
	}
	
	
	public void setResourceToInstrument(org.eclipse.emf.common.util.URI resourceUri) {
		this.resourceToInstrumentUri = resourceUri;
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
  
  
  protected URI getFileURI(String fileName) throws URISyntaxException {

	URI uri= URIUtil.fromString("file:"+fileName);
	
	if (uri.isAbsolute())
		return uri;
	
	uri = TransformUMLRTModel.class.getClassLoader().getResource("../" + fileName).toURI();
	return uri;
  }

}
