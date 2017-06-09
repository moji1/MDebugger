package ca.queensu.cs.mdebugger.debugger.actions;

import org.eclipse.jface.action.IAction;

import ca.queensu.cs.mdebugger.debugger.breakpoints.MDebuggerBreakpointPosition;

public class RemoveBeforeBreakpointsAction extends ToggleBreakpointAction {

	@Override
	public void run(IAction action) {
		this.actionKind = ActionKind.REMOVE;
		this.position = MDebuggerBreakpointPosition.BEFORE;
		super.run(action);
	}
}
