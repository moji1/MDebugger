/*******************************************************************************
 * Copyright (c) 2016 School of Computing -- Queen's University
 *
 * Description: no description currently
 * 
 * Contributors:
 *     Nicolas Hili <hili@cs.queensu.ca> - initial API and implementation
 ******************************************************************************/
package ca.queensu.cs.mdebugger.debugger.stackframes;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

import org.eclipse.debug.core.DebugException;
import org.eclipse.debug.core.ILaunch;
import org.eclipse.debug.core.model.IDebugTarget;
import org.eclipse.debug.core.model.IStackFrame;
import org.eclipse.debug.core.model.IThread;
import org.eclipse.debug.core.model.IVariable;

import ca.queensu.cs.mdebugger.debugger.model.CapsuleThread;
import ca.queensu.cs.mdebugger.debugger.model.CapsuleThread.ActionCodeType;
import ca.queensu.cs.mdebugger.debugger.model.CapsuleThread.ElementKind;
import ca.queensu.cs.mdebugger.debugger.model.CapsuleThread.EventPosition;
import ca.queensu.cs.mdebugger.debugger.variables.MDebuggerVariable;

/**
 * @author nicolas
 *
 */
public class CapsuleStackFrame extends MDebuggerStackFrame {

	private String name;
	private String currentState;
	private int timestamp;
	private int timestampNano;
	private CapsuleThread capsuleThread;
	private IVariable[] variables;
	private int weirdNumber;
	
	public ElementKind currentElementKind;
	public String currentElementName;
	private String currentUserFriendlyStateName;
	private EventPosition currentPosition;
	private ActionCodeType currentActionCodeType;
	
	
	public static enum Event_Source_Kind {
		SIGNALLING,
		METHOD,
		ACTIONECODE,
		TRANISTION,
		STATE,
		CAPSULE,
		ATTRIBUTE,
		TIMER,
		RESOURCE,
		CONNECTION,
		DEBUG,
		RESERVE1,
		RESERVE2,
		UNKOWNSOURCEKIND
	};
	// types of signal events
	public static enum Event_Type {
		SENDSIGNAL,RECIEVESIGNAL,DEFERSIGNAL,RECALLSIGNAL,CANCELLSIGNAL, // signal event
		METHODCALL,METHODCALLRECIEVE,METHODSTARTEXECUTE,METHODRETURN,METHODFAILED,METHODRETURNRECIEVED, // method event
		ACTIONSTART,ACTIONEND, // action code events
		TRANISTIONSTART,TRANISTIONEND ,// TRANSITION
		STATEENTRYSTART,STATEENTRYEND,STATEEXITSTART,STATEEXITEND,STATEIDLESTART,STATEIDLEEND, // state events
		CAPSULEINSTNSIATE,CAPSULEFREE, // capsule event
		ATTRIBUTEINSTNSIATE,ATTRIBUTEFREE,ATTRIBUTECHANGE, // attribute event
		TIMERSTART,TIMERRESET,TIMERCANCELL,TIMERTIMEDOUT, // Timer events
		RESOURCEASSIGNED,RESOURCERELEASED,RESOURCEPREEMPTED,RESOURCERESUMED,   // resource event
		CONNECTIONESTABLISHED,CONNECTIONFAILED, // connection event
		REGISTER,RESERVE3,RESERVE4,RESERVE5,RESERVE6, //resgister
		UNKOWNTYPE
	};
	
	private Event_Source_Kind eventSourceKind;
	private Event_Type eventType;
//	private IVariable[] variables;
	

	/**
	 * @param thread
	 */
	public CapsuleStackFrame(IThread thread, String name) {
		super(thread);
		this.name = name;
		this.capsuleThread = (CapsuleThread)thread;
	}
	
	@Override
	public IVariable[] getVariables() throws DebugException {
		if (this.variables == null)
			return new IVariable[0];
		
		
		return this.variables;
	}
	
	@Override
	public boolean hasVariables() throws DebugException {
		return this.variables != null;
	}
	
	public void setVariables(String[] variables) {
		
		int n = (variables.length == 1 && variables[0].equals("")) ? 0 : variables.length;
		int l = n + 4;
		this.variables = new MDebuggerVariable[l];
		
		ILaunch launch = this.getLaunch();
		IDebugTarget target = this.getDebugTarget();
		
		
		
		for (int j = 0; j < n; j++) {
			String[] v = variables[j].split(",");
			if (v.length != 3)
				continue;
			
			String name = v[0];
			String type = v[1];
			String value= v[2];
			this.variables[j] = new MDebuggerVariable(target, launch, this, name, type, value, true);
		}
		
		if (ElementKind.TRANSITION.equals(currentElementKind)) {
			this.variables[l-4] = new MDebuggerVariable(target, launch, this, "Current transition", "String", this.currentElementName, false);
		}
		else {
			this.variables[l-4] = new MDebuggerVariable(target, launch, this, "Current state", "String", this.currentElementName, false);
		}
		
		this.variables[l-3] = new MDebuggerVariable(target, launch, this, "Current position", "String", this.currentUserFriendlyStateName, false);
		this.variables[l-2] = new MDebuggerVariable(target, launch, this, "Event type", "String", this.getEventType().name(), false);
		this.variables[l-1] = new MDebuggerVariable(target, launch, this, "Event source kind", "String", this.getEventSourceKind().name(), false);
	}
	
	@Override
	public String getName() throws DebugException {
		return this.name;
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

	public int getTimestamp() {
		return timestamp;
	}

	public void setTimestamp(int timestamp) {
		this.timestamp = timestamp;
	}
	
	public int getWeirdNumber() {
		return weirdNumber;
	}

	public void setWeirdNumber(int weirdNumber) {
		this.weirdNumber = weirdNumber;
	}

	public int getTimestampNano() {
		return timestampNano;
	}

	public void setTimestampNano(int timestampNano) {
		this.timestampNano = timestampNano;
	}

	
	public Event_Source_Kind getEventSourceKind() {
		return eventSourceKind;
	}

	public void setEventSourceKind(String eventSourceKind) {
		this.eventSourceKind = Event_Source_Kind.values()[Integer.parseInt(eventSourceKind)];
	}

	public Event_Type getEventType() {
		return eventType;
	}

	public void setEventType(String eventType) {
		this.eventType = Event_Type.values()[Integer.parseInt(eventType)];
	}

	public void setName(String name) {
		this.name = name;
	}

	public void modifyValue(String name, String expression) {
		this.capsuleThread.modifyValue(name, expression);
	}

	public void compareToPreviousStackFrame(IStackFrame previousStackFrame) {
		
		IVariable[] previousVariables = new IVariable[0];
		Map<String, String> previousVariablesMap = new HashMap<String, String>();
		
		try {
			previousVariables = previousStackFrame.getVariables();
			for (int i = 0; i < previousVariables.length; i++) {
				if (previousVariables[i] == null) {
					continue;
				}
				previousVariablesMap.put(previousVariables[i].getName(), previousVariables[i].getValue().getValueString());
			}
		
			Set<String> keys = previousVariablesMap.keySet();
			
			for (int i = 0; i < this.variables.length; i++) {
				MDebuggerVariable variable = (MDebuggerVariable)this.variables[i];
				
				// the variable did not exist
				if (!keys.contains(variable.getName())) {
					variable.setDirty(true);
				}
				// the variable exist but the value was different
				if (previousVariablesMap.get(variable.getName()) == null) {
					variable.setDirty(true);
				}
				else if (previousVariablesMap.get(variable.getName()).equals(variable.getValue().getValueString())) {
					variable.setDirty(true);
				}
			}			
		} catch (DebugException e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public int hashCode() {
		final int prime = 31;
        int result = 1;
        result = prime * result + weirdNumber;
        result = prime * result + ((thread == null) ? 0 : thread.hashCode());
        return result;
	}
	
	@Override
    public boolean equals(Object obj) {
            if (this == obj)
                    return true;
            if (obj == null)
                    return false;
            if (getClass() != obj.getClass())
                    return false;
            CapsuleStackFrame other = (CapsuleStackFrame) obj;
            if (this.weirdNumber != other.getWeirdNumber())
            	return false;
            if (thread == null) {
                    if (other.thread != null)
                            return false;
            } else if (!thread.equals(other.thread))
                    return false;
            return true;
    }
	


}
