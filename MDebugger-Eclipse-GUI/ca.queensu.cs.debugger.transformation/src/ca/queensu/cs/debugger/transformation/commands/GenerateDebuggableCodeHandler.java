package ca.queensu.cs.debugger.transformation.commands;

import java.util.HashMap;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.Command;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IWorkspaceRoot;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.Path;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.transaction.RecordingCommand;
import org.eclipse.emf.transaction.TransactionalEditingDomain;
import org.eclipse.emf.transaction.util.TransactionUtil;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.papyrus.infra.emf.utils.EMFHelper;
import org.eclipse.ui.IWorkbenchSite;
import org.eclipse.ui.commands.ICommandService;
import org.eclipse.ui.handlers.HandlerUtil;
import org.eclipse.ui.services.IEvaluationService;
import org.eclipse.uml2.uml.Element;
import org.eclipse.uml2.uml.Model;

public class GenerateDebuggableCodeHandler extends AbstractHandler {

	@Override
	public Object execute(ExecutionEvent event) throws ExecutionException {
		
		
		EObject eobj = getCurrentSelection(event);
		Resource resource = getCurrentResource(eobj);
		TransactionalEditingDomain editingDomain = getEditingDomain(eobj);
		Object result;
		
		if (eobj == null || resource == null || editingDomain == null)
			return null;
		
		String path = resource.getURI().toPlatformString(true);
		IWorkspaceRoot root = ResourcesPlugin.getWorkspace().getRoot();
		IFile file = root.getFile(new Path(path));
		String name = new Path(path).removeFileExtension().lastSegment() + "_debug";
		IFile copiedFile = root.getFile(new Path(path).removeFileExtension().removeLastSegments(1).append(name).addFileExtension("uml"));
		try {
			if (copiedFile.exists()) {
				copiedFile.delete(true, null);
			}
			copiedFile.create(file.getContents(), true, null);
		} catch (CoreException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		URI uri = resource.getURI().trimFileExtension().trimSegments(1).appendSegment(name).appendFileExtension("uml");
		
		InstrumentModelCommand instrumentCommand = new InstrumentModelCommand(editingDomain);
		instrumentCommand.setResourceToInstrument(uri);
		instrumentCommand.doExecute();
		
	//	editingDomain.getCommandStack().execute(instrumentCommand);
	
/*		CopyModelCommand copyCommand = new CopyModelCommand(editingDomain);
		copyCommand.setResource(resource);
		
		editingDomain.getCommandStack().execute(copyCommand); */
		
/*		Resource copiedResource = copyCommand.getCopiedResource();
		
		InstrumentModelCommand instrumentCommand = new InstrumentModelCommand(editingDomain);
		instrumentCommand.setResourceToInstrument(copiedResource);
		
		editingDomain.getCommandStack().execute(instrumentCommand); */
		return null;
	}
	
	private EObject getCurrentSelection(ExecutionEvent event) {
		ISelection sel = HandlerUtil.getCurrentSelection(event);
		if (sel instanceof IStructuredSelection) {
			IStructuredSelection selection = (IStructuredSelection) sel;
			if (!selection.isEmpty()) {
				EObject eobj = EMFHelper.getEObject(selection.getFirstElement());
				return eobj;
			}
		}
		return null;
	}
	
	private Resource getCurrentResource(EObject eobj) {
		return (eobj != null) ? eobj.eResource() : null;
	}
	
	private TransactionalEditingDomain getEditingDomain(EObject eobj) {
		return TransactionUtil.getEditingDomain(eobj);
	}

}
