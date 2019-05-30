package ca.queensu.cs.mdebugger.debugger.actions;

import ca.queensu.cs.mdebugger.debugger.breakpoints.MDebuggerBreakpointPosition;

public class AddBeforeBreakpointsAction extends ToggleBreakpointAction {

	public AddBeforeBreakpointsAction() {
		this.actionKind = ActionKind.ADD;
		this.position = MDebuggerBreakpointPosition.BEFORE;
	}

}
