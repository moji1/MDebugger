package ca.queensu.cs.mdebugger.debugger.model;

import org.eclipse.debug.core.model.IValue;
import org.eclipse.debug.ui.IDebugModelPresentation;
import org.eclipse.debug.ui.IValueDetailListener;
import org.eclipse.jface.viewers.ILabelProviderListener;
import org.eclipse.swt.graphics.Image;
import org.eclipse.ui.IEditorInput;

import ca.queensu.cs.mdebugger.debugger.breakpoints.MDebuggerBreakpoint;

public class MDebuggerDebugModelPresentation implements IDebugModelPresentation {

	
	@Override
	public String getText(Object arg0) {
		if(arg0 instanceof MDebuggerBreakpoint) {
			MDebuggerBreakpoint breakpoint = (MDebuggerBreakpoint) arg0;
			String elementName = (String) breakpoint.getMarker().getAttribute("ca.queensu.cs.mdebugger.debugger.elementContext", "");
			String position = (String) breakpoint.getMarker().getAttribute("ca.queensu.cs.mdebugger.debugger.position", "");
			return elementName + " (" + position + ")";
		}
		return null;
	}

	
	@Override
	public void addListener(ILabelProviderListener arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void dispose() {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean isLabelProperty(Object arg0, String arg1) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void removeListener(ILabelProviderListener arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public String getEditorId(IEditorInput arg0, Object arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public IEditorInput getEditorInput(Object arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void computeDetail(IValue arg0, IValueDetailListener arg1) {
		// TODO Auto-generated method stub

	}

	@Override
	public Image getImage(Object arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void setAttribute(String arg0, Object arg1) {
		// TODO Auto-generated method stub

	}

}
