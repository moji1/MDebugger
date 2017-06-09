package ca.queensu.cs.mdebugger.debugger.actions;

import org.eclipse.jface.action.IAction;

import ca.queensu.cs.mdebugger.debugger.breakpoints.MDebuggerBreakpointPosition;

public class AddBeforeBreakpointsAction extends ToggleBreakpointAction {

	@Override
	public void run(IAction action) {
		this.actionKind = ActionKind.ADD;
		this.position = MDebuggerBreakpointPosition.BEFORE;
		super.run(action);
	}
}
