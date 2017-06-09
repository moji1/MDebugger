package ca.queensu.cs.mdebugger.debugger.actions;

import org.eclipse.jface.action.IAction;

import ca.queensu.cs.mdebugger.debugger.breakpoints.MDebuggerBreakpointPosition;

public class AddAfterBreakpointsAction extends ToggleBreakpointAction {

	@Override
	public void run(IAction action) {
		this.actionKind = ActionKind.ADD;
		this.position = MDebuggerBreakpointPosition.AFTER;
		super.run(action);
	}
}
