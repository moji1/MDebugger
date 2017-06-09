/*******************************************************************************
 * Copyright (c) 2016 School of Computing -- Queen's University
 *
 * Description: no description currently
 * 
 * Contributors:
 *     Nicolas Hili <hili@cs.queensu.ca> - initial API and implementation
 ******************************************************************************/
package ca.queensu.cs.mdebugger.debugger.variables;

import org.eclipse.debug.core.DebugException;
import org.eclipse.debug.core.ILaunch;
import org.eclipse.debug.core.model.IDebugTarget;
import org.eclipse.debug.core.model.IStackFrame;
import org.eclipse.debug.core.model.IValue;
import org.eclipse.debug.core.model.IVariable;

import ca.queensu.cs.mdebugger.debugger.model.MDebuggerDebugElement;
import ca.queensu.cs.mdebugger.debugger.stackframes.CapsuleStackFrame;

/**
 * @author nicolas
 *
 */
public class MDebuggerVariable extends MDebuggerDebugElement implements IVariable {

	private IDebugTarget target;
	private ILaunch launch;
	private IValue value;
	private String name;
	private String type;
	private boolean isMutable;
	private CapsuleStackFrame stackFrame;
	private boolean dirty = false;
	
	/**
	 * 
	 */
	public MDebuggerVariable(IDebugTarget target, ILaunch launch, IStackFrame stackFrame, String name, String type, String value, boolean isMutable) {
		super(target);
		this.target = target;
		this.launch = launch;
		this.name = name;
		this.type = type;
		this.isMutable = isMutable;
		this.stackFrame = (CapsuleStackFrame)stackFrame;
		this.value = new MDebuggerValue(target, type, value);
		this.dirty = false;
	}
	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IDebugElement#getDebugTarget()
	 */
	@Override
	public IDebugTarget getDebugTarget() {
		return target;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IDebugElement#getLaunch()
	 */
	@Override
	public ILaunch getLaunch() {
		return launch;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IValueModification#setValue(java.lang.String)
	 */
	@Override
	public void setValue(String expression) throws DebugException {
		this.value = new MDebuggerValue(target, "String", expression);

	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IValueModification#setValue(org.eclipse.debug.core.model.IValue)
	 */
	@Override
	public void setValue(IValue value) throws DebugException {
		this.value = value;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IValueModification#supportsValueModification()
	 */
	@Override
	public boolean supportsValueModification() {
		return isMutable;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IValueModification#verifyValue(java.lang.String)
	 */
	@Override
	public boolean verifyValue(String expression) throws DebugException {
		// TODO check with type
		this.stackFrame.modifyValue(this.name, expression);
		return true;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IValueModification#verifyValue(org.eclipse.debug.core.model.IValue)
	 */
	@Override
	public boolean verifyValue(IValue value) throws DebugException {
		// TODO check with type
		return true;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IVariable#getValue()
	 */
	@Override
	public IValue getValue() throws DebugException {
		return value;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IVariable#getName()
	 */
	@Override
	public String getName() throws DebugException {
		return name;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IVariable#getReferenceTypeName()
	 */
	@Override
	public String getReferenceTypeName() throws DebugException {
		return this.type;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.debug.core.model.IVariable#hasValueChanged()
	 */
	@Override
	public boolean hasValueChanged() throws DebugException {
		return this.isDirty();
	}
	
	public void setDirty(boolean dirty) {
		this.dirty = dirty;
	}
	
	public boolean isDirty() {
		return this.dirty;
	}
	
	

}
