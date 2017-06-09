/*******************************************************************************
 * Copyright (c) 2016 School of Computing -- Queen's University
 *
 * Description: no description currently
 * 
 * Contributors:
 *     Nicolas Hili <hili@cs.queensu.ca> - initial API and implementation
 ******************************************************************************/
package ca.queensu.cs.mdebugger.debugger.model;

import java.util.Timer;
import java.util.TimerTask;

import org.eclipse.core.runtime.CoreException;
import org.eclipse.debug.core.DebugEvent;
import org.eclipse.debug.core.DebugException;
import org.eclipse.debug.core.ILaunch;
import org.eclipse.debug.core.model.IBreakpoint;
import org.eclipse.debug.core.model.IDebugTarget;
import org.eclipse.debug.core.model.IStackFrame;
import org.eclipse.debug.core.model.IThread;
import org.eclipse.debug.core.model.IVariable;
import org.eclipse.papyrusrt.umlrt.uml.internal.impl.ClassRTImpl;
import org.eclipse.uml2.uml.Element;

import ca.queensu.cs.mdebugger.debugger.breakpoints.MDebuggerBreakpoint;
import ca.queensu.cs.mdebugger.debugger.breakpoints.MDebuggerBreakpointPosition;
import ca.queensu.cs.mdebugger.debugger.stackframes.CapsuleStackFrame;
import ca.queensu.cs.mdebugger.debugger.variables.MDebuggerVariable;

/**
 * @author nicolas
 *
 */
public class CapsuleThread extends MDebuggerDebugElement implements IThread {

	private String capsuleName;
	
	private String[] events;
	
	private String currentState;
	
	private Timer timer;
	private CapsuleThreadTimerTask task;
	
	private boolean isSuspended = true;

	private String capsuleClassName;
	
	public enum ElementKind {
		TRANSITION, STATE
	}
	
	public enum EventPosition {
		BEFORE, AFTER
	}
	
	public enum ActionCodeType{
		ENTRY, EXIT, EFFECT 
	}
	
	private ElementKind currentElementKind;
	private String currentElementName;
	private String currentUserFriendlyStateName;
	private EventPosition currentPosition;
	private ActionCodeType currentActionCodeType;

	/**
	 * @param target
	 */
	public CapsuleThread(IDebugTarget target, String capsuleName) {
		super(target);
		this.capsuleClassName = capsuleName.split(":")[0];
		this.capsuleName = capsuleName;
		this.currentState = "";
		timer = new Timer();
		task = new CapsuleThreadTimerTask(this.getDebugTarget(), this.capsuleName);
		timer.schedule(task, 1000, 1000);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.ISuspendResume#canResume()
	 */
	@Override
	public boolean canResume() {
		return this.getDebugTarget().canResume();
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.ISuspendResume#canSuspend()
	 */
	@Override
	public boolean canSuspend() {
		return this.getDebugTarget().canSuspend();
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.ISuspendResume#isSuspended()
	 */
	@Override
	public boolean isSuspended() {
		return this.isSuspended;
		//return this.getDebugTarget().isSuspended() || this.isSuspended;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.ISuspendResume#resume()
	 */
	@Override
	public void resume() throws DebugException {
		this.isSuspended = false;
		fireResumeEvent(DebugEvent.RESUME);
		((MDebuggerDebugTarget)getDebugTarget()).resumeCapsule(getCapsuleName());
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.ISuspendResume#suspend()
	 */
	@Override
	public void suspend() throws DebugException {
		// TODO Auto-generated method stub

	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IStep#canStepInto()
	 */
	@Override
	public boolean canStepInto() {
		// TODO Auto-generated method stub
		return false;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IStep#canStepOver()
	 */
	@Override
	public boolean canStepOver() {
		return this.isSuspended();
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IStep#canStepReturn()
	 */
	@Override
	public boolean canStepReturn() {
		// TODO Auto-generated method stub
		return false;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IStep#isStepping()
	 */
	@Override
	public boolean isStepping() {
		return isSuspended();
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IStep#stepInto()
	 */
	@Override
	public void stepInto() throws DebugException {
		// TODO Auto-generated method stub

	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IStep#stepOver()
	 */
	@Override
	public void stepOver() throws DebugException {
		((MDebuggerDebugTarget)this.getDebugTarget()).stepOver(this.getCapsuleName());
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IStep#stepReturn()
	 */
	@Override
	public void stepReturn() throws DebugException {
		// TODO Auto-generated method stub

	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.ITerminate#canTerminate()
	 */
	@Override
	public boolean canTerminate() {
		return this.getDebugTarget().canTerminate();
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.ITerminate#isTerminated()
	 */
	@Override
	public boolean isTerminated() {
		return this.getDebugTarget().isTerminated();
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.ITerminate#terminate()
	 */
	@Override
	public void terminate() throws DebugException {
		timer.cancel();
		timer.purge();
		fireTerminateEvent();
	}
	

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IThread#getTopStackFrame()
	 */
	@Override
	public IStackFrame getTopStackFrame() throws DebugException {
		if (!this.isSuspended() || this.events == null)
			return null;
		
		// retrieving the events
		CapsuleStackFrame stackFrame = new CapsuleStackFrame(this, ""); // we remove the two first arguments
		
		String event = events[0];
		
		// Retrieving each value
		String[] eventInfos = event.split(";");
		String eventSourceKind = eventInfos[1];
		String eventType = eventInfos[2];
		String capsuleName = eventInfos[3];
		String capsulePartName = eventInfos[4];
		int capsuleIndex = Integer.parseInt(eventInfos[5]);
		String currentState = eventInfos[6];
		int weirdNumber = Integer.parseInt(eventInfos[7]);
		int timestamp = Integer.parseInt(eventInfos[8]);
		int timestampNano = Integer.parseInt(eventInfos[9]);
		String[] var = eventInfos[10].split("\n");
		// TODO payload parameters
		
		//stackFrame.suspend();
		
		stackFrame.setTimestamp(timestamp);
		stackFrame.setTimestampNano(timestampNano);
		stackFrame.setCurrentState(currentState);
		stackFrame.setEventSourceKind(eventSourceKind);
		stackFrame.setEventType(eventType);
		stackFrame.setWeirdNumber(weirdNumber);
		stackFrame.setVariables(var);
		
		stackFrame.setName("["+timestamp+"]: " + stackFrame.getEventType());
			
		return stackFrame;
				
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IThread#getStackFrames()
	 */
	@Override
	public IStackFrame[] getStackFrames() throws DebugException {
		
		if (!this.isSuspended() || this.events == null)
			return new IStackFrame[0];
		
		// retrieving the events
		IStackFrame[] stackFrames = new CapsuleStackFrame[events.length]; // we remove the two first arguments
		
		for (int i = 0; i < events.length; i++) {
			
			// Instantiating a stackframe per event
			CapsuleStackFrame stackFrame = new CapsuleStackFrame(this, "");

			String event = events[i];
			
			// Retrieving each value
			String[] eventInfos = event.split(";");
			String eventSourceKind = eventInfos[1];
			String eventType = eventInfos[2];
			String capsuleName = eventInfos[3];
			String capsulePartName = eventInfos[4];
			int capsuleIndex = Integer.parseInt(eventInfos[5]);
			String currentState = eventInfos[6];
			int weirdNumber = Integer.parseInt(eventInfos[7]);
			int timestamp = Integer.parseInt(eventInfos[8]);
			int timestampNano = Integer.parseInt(eventInfos[9]);
			String[] var = eventInfos[10].split("\n");
			String status = eventInfos[11].split(":")[1];
			// TODO payload parameters
			
			//stackFrame.suspend();
			
			stackFrame.setTimestamp(timestamp);
			stackFrame.setTimestampNano(timestampNano);
			stackFrame.setCurrentState(currentState);
			stackFrame.setEventSourceKind(eventSourceKind);
			stackFrame.setEventType(eventType);
			stackFrame.setWeirdNumber(weirdNumber);
			stackFrame.setVariables(var);
			stackFrame.setName("["+timestamp+"]: " + stackFrame.getEventType());

			if (i > 0)
				((CapsuleStackFrame) stackFrames[i-1]).compareToPreviousStackFrame(stackFrame);
			
			stackFrames[i] = stackFrame;
			
				
			
		}
		
		return stackFrames;
	}
	
	public void setEvents(String[] events) {
		
		if (this.events != null && this.events.length > 0) {
			if (events[0].split(";")[0].equals(this.events[0].split(";")[0])) {
				return;
			}
		}
		this.events = events;
		
		String currentState = events[0].split(";")[6];
		this.setCurrentState(currentState);

		String status = events[0].split(";")[11].split(":")[1];
		boolean isSuspended = status.equals("1");
		
		if (this.isSuspended && !isSuspended) {
			this.isSuspended = false;
//			fireChangeEvent(DebugEvent.RESUME);
		}
		else if (!this.isSuspended && isSuspended) {
			this.isSuspended = true;
//			fireChangeEvent(DebugEvent.SUSPEND);
		}
		fireChangeEvent(DebugEvent.CHANGE);
		
	}
	
	public void pushEvent(String event) {
		
		int l = events.length;
		
		for (int i = l-2; i >= 0; i--) {
			events[i+1] = events[i];
		}
		
		String currentState = event.split(";")[6];
		this.setCurrentState(currentState);
		
		fireChangeEvent(DebugEvent.CHANGE);
		
		events[0] = event;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IThread#hasStackFrames()
	 */
	@Override
	public boolean hasStackFrames() throws DebugException {
		return this.events != null  && this.isSuspended();
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IThread#getPriority()
	 */
	@Override
	public int getPriority() throws DebugException {
		return 0;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IThread#getName()
	 */
	@Override
	public String getName() throws DebugException {
		String name = this.capsuleName;
		if (!currentUserFriendlyStateName.equals(""))
			name += " ["+currentUserFriendlyStateName+"]";
		return name;
	}
	
	public String getCapsuleName() {
		return this.capsuleName;
	}
	
	public String getCapsuleClassName() {
		return capsuleClassName;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IThread#getBreakpoints()
	 */
	@Override
	public IBreakpoint[] getBreakpoints() {
		return new IBreakpoint[0];
	}
	
	public void modifyValue(String name, String expression) {
		((MDebuggerDebugTarget)this.getDebugTarget()).modifyValue(this.getCapsuleName(), name, expression);
	}

	public String getCurrentState() {
		return currentState;
	}

	public void setCurrentState(String currentState) {
		this.currentState = currentState;
		String[] currentStateFragment = currentState.split("::");
		if (currentStateFragment.length > 0) {
			currentUserFriendlyStateName = currentStateFragment[currentStateFragment.length-1];
			
			currentStateFragment = currentUserFriendlyStateName.split("__");
			if (currentStateFragment.length == 4) {
				
				currentPosition = ("A".equals(currentStateFragment[1])) ? EventPosition.AFTER : EventPosition.BEFORE;
				currentElementName = currentStateFragment[3];
				currentUserFriendlyStateName = (EventPosition.AFTER.equals(currentPosition)) ? "After " : "Before ";

				switch (currentStateFragment[2]) {
				case "En":
					currentActionCodeType = ActionCodeType.ENTRY;
					currentElementKind = ElementKind.STATE;
					currentUserFriendlyStateName += "state entry's ";
					break;
					
				case "Ex":
					currentActionCodeType = ActionCodeType.EXIT;
					currentElementKind = ElementKind.STATE;
					currentUserFriendlyStateName += "state exit's ";
					break;
					
				case "Ac":
					currentActionCodeType = ActionCodeType.EFFECT;
					currentElementKind = ElementKind.TRANSITION;
					currentUserFriendlyStateName += "transition effect's ";
					break;
				}
				
				currentUserFriendlyStateName += " action code of ";
				currentUserFriendlyStateName += (ElementKind.TRANSITION.equals(currentElementKind)) ? "transition " : "state ";
				currentUserFriendlyStateName += currentElementName;
			}
		}
	}
	
	public void breakpointAdded(MDebuggerBreakpoint breakpoint) {
		Element element = breakpoint.getElement();
		String ownerCapsuleName = getOwnerCapsuleName(element);
		if (capsuleClassName.equals(ownerCapsuleName)) {
			((MDebuggerDebugTarget)getDebugTarget()).addBreakpoint(breakpoint, capsuleName);
		}
    }
	
	public void breakpointRemoved(MDebuggerBreakpoint breakpoint) {
		Element element = breakpoint.getElement();
		String ownerCapsuleName = getOwnerCapsuleName(element);
		if (capsuleClassName.equals(ownerCapsuleName)) {
			((MDebuggerDebugTarget)getDebugTarget()).removeBreakpoint(breakpoint, capsuleName);
		}
	}
	
	private String getOwnerCapsuleName(Element element) {
		if (element instanceof ClassRTImpl) {
			return ((org.eclipse.uml2.uml.Class) element).getName();
		}
		else if (element.getOwner() != null) {
			return getOwnerCapsuleName(element.getOwner());
		}
		return "";
	}

}
