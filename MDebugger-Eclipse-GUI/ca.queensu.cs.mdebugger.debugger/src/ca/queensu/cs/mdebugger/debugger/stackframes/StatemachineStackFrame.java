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
import org.eclipse.debug.core.model.IThread;
import org.eclipse.debug.core.model.IVariable;

import ca.queensu.cs.mdebugger.debugger.variables.MDebuggerVariable;

/**
 * @author nicolas
 *
 */
public class StatemachineStackFrame extends MDebuggerStackFrame {

	/**
	 * @param thread
	 */
	public StatemachineStackFrame(IThread thread) {
		super(thread);
	}
	
	@Override
	public IVariable[] getVariables() throws DebugException {
		return new IVariable[] {
				new MDebuggerVariable(getDebugTarget(), getLaunch(), this, "name", "String", "statemachineName", false),
				new MDebuggerVariable(getDebugTarget(), getLaunch(), this, "region", "String", "regionName", false)
		};
	}
	
	@Override
	public String getName() throws DebugException {
		return "statemachineName";
	}

}
