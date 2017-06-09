/*******************************************************************************
 * Copyright (c) 2016 School of Computing -- Queen's University
 *
 * Description: no description currently
 * 
 * Contributors:
 *     Nicolas Hili <hili@cs.queensu.ca> - initial API and implementation
 ******************************************************************************/
package ca.queensu.cs.mdebugger.debugger.stackframes;

import org.eclipse.debug.core.DebugException;
import org.eclipse.debug.core.model.IRegisterGroup;
import org.eclipse.debug.core.model.IStackFrame;
import org.eclipse.debug.core.model.IThread;
import org.eclipse.debug.core.model.IVariable;

import ca.queensu.cs.mdebugger.debugger.model.MDebuggerDebugElement;
import ca.queensu.cs.mdebugger.debugger.variables.MDebuggerVariable;

/**
 * @author nicolas
 *
 */
public class MDebuggerStackFrame extends MDebuggerDebugElement implements IStackFrame {

	protected IThread thread;

    public MDebuggerStackFrame(IThread thread) {
            super(thread.getDebugTarget());
            this.thread = thread;
    }

    @Override
    public boolean canStepInto() {
            return thread.canStepInto();
    }

    @Override
    public boolean canStepOver() {
            return thread.canStepOver();
    }

    @Override
    public boolean canStepReturn() {
            return thread.canStepReturn();
    }

    @Override
    public boolean isStepping() {
            return thread.isStepping();
    }

    @Override
    public void stepInto() throws DebugException {
            thread.stepInto();
    }

    @Override
    public void stepOver() throws DebugException {
            thread.stepOver();
    }

    @Override
    public void stepReturn() throws DebugException {
            thread.stepReturn();
    }

    @Override
    public boolean canResume() {
            return thread.canResume();
    }

    @Override
    public boolean canSuspend() {
            return thread.canSuspend();
    }

    @Override
    public boolean isSuspended() {
            return thread.isSuspended();
    }

    @Override
    public void resume() throws DebugException {
            thread.resume();
    }

    @Override
    public void suspend() throws DebugException {
            thread.suspend();
    }

    @Override
    public boolean canTerminate() {
            return thread.canTerminate();
    }

    @Override
    public boolean isTerminated() {
            return thread.isTerminated();
    }

    @Override
    public void terminate() throws DebugException {
     //       thread.terminate();
    }

    @Override
    public IThread getThread() {
            return thread;
    }

    @Override
    public IVariable[] getVariables() throws DebugException {
    	return new IVariable[0];
    }

    @Override
    public boolean hasVariables() throws DebugException {
            return true;
    }

    @Override
    public int getLineNumber() throws DebugException {
            return -1;
    }

    @Override
    public int getCharStart() throws DebugException {
            return -1;
    }

    @Override
    public int getCharEnd() throws DebugException {
            return -1;
    }

    @Override
    public String getName() throws DebugException {
            return "My stack frame";
    }

    @Override
    public IRegisterGroup[] getRegisterGroups() throws DebugException {
            return new IRegisterGroup[0];
    }

    @Override
    public boolean hasRegisterGroups() throws DebugException {
            return false;
    }

    @Override
    public boolean equals(Object obj) {
            if (this == obj)
                    return true;
            if (obj == null)
                    return false;
            if (getClass() != obj.getClass())
                    return false;
            return true;
    }

}
