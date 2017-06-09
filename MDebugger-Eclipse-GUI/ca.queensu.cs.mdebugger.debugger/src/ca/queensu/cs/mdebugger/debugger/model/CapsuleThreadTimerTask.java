package ca.queensu.cs.mdebugger.debugger.model;

import java.util.TimerTask;

import org.eclipse.debug.core.model.IDebugTarget;

public class CapsuleThreadTimerTask extends TimerTask {

	MDebuggerDebugTarget debugTarget;
	private String capsuleName;
	
	public CapsuleThreadTimerTask(IDebugTarget debugTarget, String capsuleName) {
		this.debugTarget = (MDebuggerDebugTarget) debugTarget;
		this.capsuleName = capsuleName;
	}

	@Override
	public void run() {
		this.debugTarget.requestEventList(capsuleName, 5);

	}

}
