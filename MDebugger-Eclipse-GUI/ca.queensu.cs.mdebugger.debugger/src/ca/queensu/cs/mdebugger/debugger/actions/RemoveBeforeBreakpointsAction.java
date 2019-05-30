package ca.queensu.cs.mdebugger.debugger.actions;

import ca.queensu.cs.mdebugger.debugger.breakpoints.MDebuggerBreakpointPosition;

public class RemoveBeforeBreakpointsAction extends ToggleBreakpointAction {

	public RemoveBeforeBreakpointsAction() {
		this.actionKind = ActionKind.REMOVE;
		this.position = MDebuggerBreakpointPosition.BEFORE;
	}

}
