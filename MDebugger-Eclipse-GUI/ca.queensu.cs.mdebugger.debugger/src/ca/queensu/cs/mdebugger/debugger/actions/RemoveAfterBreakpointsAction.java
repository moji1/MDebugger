package ca.queensu.cs.mdebugger.debugger.actions;


import ca.queensu.cs.mdebugger.debugger.breakpoints.MDebuggerBreakpointPosition;

public class RemoveAfterBreakpointsAction extends ToggleBreakpointAction {

	public RemoveAfterBreakpointsAction() {
		this.actionKind = ActionKind.REMOVE;
		this.position = MDebuggerBreakpointPosition.AFTER;
	}
}
