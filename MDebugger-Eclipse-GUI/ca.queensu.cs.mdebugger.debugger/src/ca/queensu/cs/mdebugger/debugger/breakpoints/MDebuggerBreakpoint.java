/*******************************************************************************
 * Copyright (c) 2016 School of Computing -- Queen's University
 *
 * Description: no description currently
 * 
 * Contributors:
 *     Nicolas Hili <hili@cs.queensu.ca> - initial API and implementation
 ******************************************************************************/
package ca.queensu.cs.mdebugger.debugger.breakpoints;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IMarker;
import org.eclipse.core.resources.IWorkspaceRoot;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.Path;
import org.eclipse.core.runtime.jobs.ISchedulingRule;
import org.eclipse.debug.core.model.Breakpoint;
import org.eclipse.uml2.uml.Element;
import org.eclipse.uml2.uml.NamedElement;
import org.eclipse.uml2.uml.OpaqueBehavior;
import org.eclipse.uml2.uml.Region;

import ca.queensu.cs.mdebugger.debugger.Activator;

/**
 * @author nicolas
 *
 */
public class MDebuggerBreakpoint extends Breakpoint {
	
	private Element element;
	private MDebuggerBreakpointPosition position;
	
	/**
	 * @throws CoreException 
	 * 
	 */
	public MDebuggerBreakpoint(Element element, MDebuggerBreakpointPosition position) throws CoreException {
		this.position = position;
		this.element = element;
		
		
		String path = element.eResource().getURI().toPlatformString(true);
		IWorkspaceRoot root = ResourcesPlugin.getWorkspace().getRoot();
		IFile file = root.getFile(new Path(path));
		
		IMarker marker = file.createMarker("ca.queensu.cs.mdebugger.debugger.marker");
		setMarker(marker);
		ISchedulingRule rule = this.getMarkerRule();
		if (element instanceof OpaqueBehavior) {
			String elementName = ((NamedElement)((OpaqueBehavior)element).getOwner()).getName();
			NamedElement node = (NamedElement) element;
			List<String> parents = new ArrayList<String>();
			while(node != null) {
				if(!(node instanceof Region)) {
					parents.add(node.getName());
				}
				node = (NamedElement) node.getOwner();
			}
			Collections.reverse(parents);
			ensureMarker().setAttribute("ca.queensu.cs.mdebugger.debugger.elementContext", String.join("::", parents));
			ensureMarker().setAttribute("ca.queensu.cs.mdebugger.debugger.elementName", elementName);
			ensureMarker().setAttribute("ca.queensu.cs.mdebugger.debugger.position", MDebuggerBreakpointPosition.AFTER.equals(position) ? "after" : "before");
		}	
		setEnabled(true);
	}

	@Override
	public String getModelIdentifier() {
		return Activator.PLUGIN_ID;
	}

	public Element getElement() {
		return element;
	}
	
	public void setElement(Element element) {
		this.element = element;
	}
	
	public MDebuggerBreakpointPosition getPosition() {
		return position;
	}
	
	public void setPosition(MDebuggerBreakpointPosition position) {
		this.position = position;
	}
}
