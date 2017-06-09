package ca.queensu.cs.debugger.transformation.commands;

import java.io.FileInputStream;
import java.io.FileNotFoundException;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IWorkspaceRoot;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.Path;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.transaction.RecordingCommand;
import org.eclipse.emf.transaction.TransactionalEditingDomain;
import org.eclipse.uml2.uml.Element;
import org.eclipse.uml2.uml.Stereotype;

public class CopyModelCommand extends RecordingCommand {

	private Resource res;
	private TransactionalEditingDomain domain;
	private Resource copiedResource;

	public CopyModelCommand(TransactionalEditingDomain domain) {
		super(domain);
		this.domain = domain;
		// TODO Auto-generated constructor stub
	}
	

	@Override
	protected void doExecute() {
		String path = res.getURI().toPlatformString(true);
		IWorkspaceRoot root = ResourcesPlugin.getWorkspace().getRoot();
		IFile file = root.getFile(new Path(path));
		String name = new Path(path).removeFileExtension().lastSegment() + "_debug";
		IFile copiedFile = root.getFile(new Path(path).removeFileExtension().removeLastSegments(1).append(name).addFileExtension("uml"));
		System.out.println(file.exists());
		System.out.println(copiedFile.exists());
		try {
			copiedFile.create(file.getContents(), true, null);
		} catch (CoreException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
/*		ResourceSet resourceSet = res.getResourceSet();
		URI modelUri = res.getURI();
		URI debugUri = URI.createURI(modelUri.toString());
		String lastSegment = debugUri.trimFileExtension().lastSegment();
		debugUri = debugUri.trimFileExtension().trimSegments(1).appendSegment(lastSegment+"_debug").appendFileExtension("uml");
		System.out.println(debugUri);
		Resource debugRes = resourceSet.createResource(debugUri, "uml");
		
		try {
			
			EcoreUtil.resolveAll(res);
		
			// copy all elements
			EcoreUtil.Copier copier = new EcoreUtil.Copier();
			
//			Model model = (Model) res.getContents().get(0);
					
//			EList<PackageableElement> pes = model.getPackagedElements();
//			EList<PackageableElement> copyPes = new BasicEList<>();
			
/*			Package debugPackage = UMLFactory.eINSTANCE.createPackage();
			debugPackage.setName(((Model)res.getContents().get(0)).getName() + "_Debug");
			model.getNestedPackages().add(debugPackage);
			
			for (PackageableElement pe : pes) {
				
				if (pe.equals(debugPackage))
					continue;
				
				PackageableElement copyPe = (PackageableElement) copier.copy(pe);
				debugPackage.getPackagedElements().add(copyPe);
				copyStereotypeApplications(pe, copyPe);
				
//				copyPes.add(copyPe);
			}
			
/*			for (PackageableElement pe : copyPes) {
				debugPackage.getPackagedElements().add(pe);
			} */
			
/*			Collection<EObject> umlObjects = copier.copyAll(res.getContents());
			copier.copyReferences();
	
				for (EObject umlObject: umlObjects) {
					if (umlObject instanceof Model) {
						Model model = (Model) umlObject;
						model.setName(model.getName() + "_debug");
					}
					debugRes.getContents().add(umlObject);
				}
			
			debugRes.save(null);
			setCopiedResource(debugRes);
			
		} catch (IOException e) {
			e.printStackTrace();
		}*/
	}
	

	private void copyStereotypeApplications (Element initial, Element output) {
		for (Stereotype stereotype : initial.getAppliedStereotypes()) {
			output.applyStereotype(stereotype);
		}
		
		for (int i = 0; i < output.getOwnedElements().size(); i++) {
			copyStereotypeApplications(initial.getOwnedElements().get(i), output.getOwnedElements().get(i));
		}
	}

	public void setResource(Resource resource) {
		this.res = resource;
	}
	
	public void setCopiedResource(Resource copiedResource) {
		this.copiedResource = copiedResource;
	}
	
	public Resource getCopiedResource() {
		return this.copiedResource;
	}
}