/*******************************************************************************
 * Copyright (c) 2016 School of Computing -- Queen's University
 *
 * Description: this code is an handler that allows to execute an EOL transformation programmatically
 * TODO: the UML model should be get from the Eclipse selection
 * TODO: The handler can be activated when a class is selected. Its activation should only be possible when a UML model is selected.
 * 
 * This code is inspired by: 
 * http://www.eclipse.org/epsilon/examples/index.php?example=org.eclipse.epsilon.examples.standalone
 * 
 * Contributors:
 *     Nicolas Hili <hili@cs.queensu.ca> - initial API and implementation
 *     Mojtaba Bagherzadeh <mojtaba@cs.queensu.ca> fix the integration with Eclipse  Oxygen by embedding the Epsilon Jar files in plugin
 ******************************************************************************/

package ca.queensu.cs.debugger.transformation.commands;

import java.io.PrintStream;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.ArrayList;
import java.util.List;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.core.runtime.URIUtil;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.transaction.impl.ResourceSetManager;
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
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.papyrus.infra.emf.utils.EMFHelper;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.FileDialog;
import org.eclipse.ui.console.ConsolePlugin;
import org.eclipse.ui.console.IConsole;
import org.eclipse.ui.console.IConsoleManager;
import org.eclipse.ui.console.MessageConsole;
import org.eclipse.ui.console.MessageConsoleStream;
import org.eclipse.ui.handlers.HandlerUtil;
import org.eclipse.uml2.uml.Model;


public class TransformUMLRTModel extends AbstractHandler {

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
		IStructuredSelection structuredSelection = HandlerUtil.getCurrentStructuredSelection(event);
		Object umlmodel = structuredSelection.getFirstElement();
		
        String eolScript = event.getParameter("ca.queensu.cs.debugger.transformation.commands.parameter.eolScript");
        
        if (eolScript.equals("")) {
        	FileDialog dialog = new FileDialog(Display.getCurrent().getActiveShell(), SWT.OPEN);
        	dialog.setFilterExtensions(new String [] {"*.eol"});
        	eolScript = dialog.open();
        }
        
		final EObject eobj = EMFHelper.getEObject(umlmodel);
		
		if (!(eobj instanceof Model))
			return null;
		
		uri = eobj.eResource().getURI();
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
		result = execute(module);
	    postProcess();
	    
	    module.getContext().getModelRepository().dispose();

	    } catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	    
	    return null;
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
	  
	  protected URI getFileURI(String fileName) throws URISyntaxException {

		URI uri= URIUtil.fromString("file:"+fileName);
		
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
