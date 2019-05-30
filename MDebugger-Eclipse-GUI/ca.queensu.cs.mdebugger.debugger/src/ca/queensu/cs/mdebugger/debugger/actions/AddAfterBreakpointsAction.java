package ca.queensu.cs.mdebugger.debugger.actions;

import ca.queensu.cs.mdebugger.debugger.breakpoints.MDebuggerBreakpointPosition;

public class AddAfterBreakpointsAction extends ToggleBreakpointAction {

	public AddAfterBreakpointsAction() {
		this.actionKind = ActionKind.ADD;
		this.position = MDebuggerBreakpointPosition.AFTER;
	}

	
}
