package ca.queensu.cs.debugger.transformation.commands;

import java.util.ArrayList;
import java.util.List;

import org.eclipse.core.runtime.IStatus;
import org.eclipse.emf.ecore.EAnnotation;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.transaction.RecordingCommand;
import org.eclipse.emf.transaction.TransactionalEditingDomain;
import org.eclipse.jface.dialogs.ErrorDialog;
import org.eclipse.papyrusrt.codegen.UMLRTCodeGenerator;
import org.eclipse.papyrusrt.codegen.config.CodeGenProvider;
import org.eclipse.swt.widgets.Display;
import org.eclipse.uml2.uml.Element;
import org.eclipse.uml2.uml.Model;

public class GenerateCodeCommand {// extends RecordingCommand {

	private Model model;

	public GenerateCodeCommand(TransactionalEditingDomain domain) {
	//	super(domain);
		// TODO Auto-generated constructor stub
	}

	//@Override
	protected void doExecute() {
		
		List<EObject> targets = new ArrayList<>();
		
		/** The code generator. */
		System.out.println("Start generarting code");
		UMLRTCodeGenerator generator = CodeGenProvider.getDefault().get();
		generator.setRegenerate(true);
		try {
			String topCapsuleName = getTopCapsuleName(model);
			targets.add(model);

			final IStatus status = generator.generate(targets, topCapsuleName, true);
//			Display.getDefault().syncExec(new Runnable() {
//				@Override
//				public void run() {
					ErrorDialog.openError(Display.getCurrent().getActiveShell(), "UML-RT Code Generator", null, status);
//				}
//			});
		} finally {
			generator.setRegenerate(false);
		}
	}
	
	public void setInstrumentedModel(Model model) {
		this.model = model;
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
	

}
