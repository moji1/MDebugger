package ca.queensu.cs.mdebugger.debugger.actions;

import org.eclipse.core.runtime.CoreException;
import org.eclipse.debug.core.DebugPlugin;
import org.eclipse.debug.core.model.IBreakpoint;
import org.eclipse.debug.ui.actions.IToggleBreakpointsTargetExtension;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.gef.GraphicalEditPart;
import org.eclipse.gmf.runtime.notation.View;
import org.eclipse.jface.action.IAction;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.ui.IActionDelegate;
import org.eclipse.ui.IWorkbenchPart;
import org.eclipse.uml2.uml.Element;
import org.eclipse.uml2.uml.OpaqueBehavior;
import org.eclipse.uml2.uml.Transition;

import ca.queensu.cs.mdebugger.debugger.Activator;
import ca.queensu.cs.mdebugger.debugger.breakpoints.MDebuggerBreakpointPosition;
import ca.queensu.cs.mdebugger.debugger.breakpoints.MDebuggerBreakpoint;

public abstract class ToggleBreakpointAction implements IActionDelegate {
	
	public enum ActionKind {
	    ADD,
	    REMOVE
	}
	
	protected MDebuggerBreakpointPosition position = MDebuggerBreakpointPosition.BEFORE;
	protected ActionKind actionKind = ActionKind.ADD;
	protected OpaqueBehavior actionCode;
	
	@Override
	public void run(IAction action) {
		
		if (actionCode == null)
			return;
		
		try {
			if (ActionKind.ADD.equals(actionKind)) {
				enableBreakPoint();
			}
			else {
				disableBreakPoint();
			}
		}
		catch (CoreException e) {
			e.printStackTrace();
		}
	}
	
	private IBreakpoint getBreakpoint(Element element, MDebuggerBreakpointPosition position) {
		for (IBreakpoint breakpoint : DebugPlugin.getDefault().getBreakpointManager().getBreakpoints(Activator.PLUGIN_ID)) {
			if (breakpoint instanceof MDebuggerBreakpoint) {
				MDebuggerBreakpoint b = (MDebuggerBreakpoint)breakpoint;
				if (element.equals(b.getElement()) && position.equals(b.getPosition())) {
					return b;
				}
			}
		}
		return null;
	}
	
	private void enableBreakPoint() throws CoreException {
		if (getBreakpoint(actionCode, position) == null) {
			MDebuggerBreakpoint breakpoint = new MDebuggerBreakpoint(actionCode, position);
			DebugPlugin.getDefault().getBreakpointManager().addBreakpoint(breakpoint);
		}
	}
	
	private void disableBreakPoint() throws CoreException {
		IBreakpoint breakpointToRemove = getBreakpoint(actionCode, position);

		if (breakpointToRemove != null) {
			DebugPlugin.getDefault().getBreakpointManager().removeBreakpoint(breakpointToRemove, true);
		}
		
	}

	@Override
	public void selectionChanged(IAction action, ISelection selection) {
		Object obj = ((IStructuredSelection)selection).getFirstElement();
		if (!(obj instanceof GraphicalEditPart))
			return;
				
		GraphicalEditPart editPart = (GraphicalEditPart)obj;
		EObject element = ((View) editPart.getModel()).getElement();
		
		if (element instanceof OpaqueBehavior)
			actionCode = (OpaqueBehavior)element;
		else if (element instanceof Transition)
			actionCode = (OpaqueBehavior) ((Transition)element).getEffect();
		
		if(actionCode != null) {
			if (getBreakpoint(actionCode, position) == null) {
				action.setEnabled(ActionKind.ADD.equals(actionKind));
			}else {
				action.setEnabled(ActionKind.REMOVE.equals(actionKind));
			}
		}
	}
	
}
