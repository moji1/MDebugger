/*******************************************************************************
 * Copyright (c) 2016 School of Computing -- Queen's University
 *
 * Description: no description currently
 * 
 * Contributors:
 *     Nicolas Hili <hili@cs.queensu.ca> - initial API and implementation
 ******************************************************************************/
package ca.queensu.cs.mdebugger.debugger.model;

import org.eclipse.debug.core.DebugException;
import org.eclipse.debug.core.model.IBreakpoint;
import org.eclipse.debug.core.model.IDebugTarget;
import org.eclipse.debug.core.model.IStackFrame;
import org.eclipse.debug.core.model.IThread;
import ca.queensu.cs.mdebugger.debugger.server.MDebuggerTCPServer;
import ca.queensu.cs.mdebugger.debugger.stackframes.CapsuleStackFrame;
import ca.queensu.cs.mdebugger.debugger.stackframes.RegionStackFrame;
import ca.queensu.cs.mdebugger.debugger.stackframes.StatemachineStackFrame;
import ca.queensu.cs.mdebugger.debugger.stackframes.TransitionStackFrame;

/**
 * @author nicolas
 *
 */
public class MDebuggerThread extends MDebuggerDebugElement implements IThread {

	private Thread thread;
	
	// The different states, which this IThread can have
    private enum State {
            RUNNING, STEPPING, SUSPENDED, TERMINATED
    }
    
    private State currentState;

	public MDebuggerThread(IDebugTarget target) {
		super(target);
		thread = new Thread(new MDebuggerTCPServer(8001, this.getDebugTarget()));
		thread.start();
		fireCreationEvent();
	}

	@Override
    public boolean canResume() {
            return isSuspended();
    }

    @Override
    public boolean canSuspend() {
            return !isTerminated() && !isSuspended();
    }

    @Override
    public boolean isSuspended() {
            return State.SUSPENDED.equals(currentState);
    }

    @Override
    public void resume() throws DebugException {
            synchronized (this) {
                    currentState = State.RUNNING;
            }
    }

    @Override
    public void suspend() throws DebugException {
    //	synchronized (this) {
    		currentState = State.SUSPENDED;
    		System.out.println("something happened");
    //	}
    }

	@Override
	public boolean canStepInto() {
		return false;
	}

	@Override
	public boolean canStepOver() {
		return false;
	}

	@Override
	public boolean canStepReturn() {
		return false;
	}

	@Override
	public boolean isStepping() {
		return false;
	}

	@Override
	public void stepInto() throws DebugException {
	}

	@Override
	public void stepOver() throws DebugException {
	}

	@Override
	public void stepReturn() throws DebugException {
	}

	@Override
	public boolean canTerminate() {
		return !isTerminated();
	}

	@Override
	public boolean isTerminated() {
		return State.TERMINATED.equals(currentState);
	}

	@Override
	public void terminate() throws DebugException {
	//	synchronized (this) {
//            requestedState = State.TERMINATED;
//            if (isSuspended()) {
                    // run to termination
//                    thread = new Thread();
//                    thread.start();
//            } else {
                    thread.interrupt();
                    fireTerminateEvent();
                    MDebuggerDebugTarget target = (MDebuggerDebugTarget) getDebugTarget();
                    target.dispose();
//            }
	//	}
	}

    @Override
    public IStackFrame getTopStackFrame() throws DebugException {
    //        synchronized (this) {
    //                if (isSuspended()) {
                            return new TransitionStackFrame(this);
     //               }
    //        }
    //        return null;
    }

    @Override
    public IStackFrame[] getStackFrames() throws DebugException {
     //       synchronized (this) {
     //               if (isSuspended()) {
                    	return new IStackFrame[] {
                    		new TransitionStackFrame(this),
                    		new RegionStackFrame(this),
                    		new StatemachineStackFrame(this),
                    		new CapsuleStackFrame(this, "")
                    	};
     //               }
    //        }
     //       return new IStackFrame[0];
    }
    
    @Override
    public boolean hasStackFrames() throws DebugException {
    	// An IThread only has stack frames when it is suspended.
     //   return isSuspended();
    	return true;
    }

	@Override
	public int getPriority() throws DebugException {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public String getName() throws DebugException {
		return "MDebugger thread";
	}

	@Override
	public IBreakpoint[] getBreakpoints() {
		// TODO Auto-generated method stub
		return null;
	}
	
	
}
