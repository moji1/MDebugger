/*******************************************************************************
 * Copyright (c) 2016 School of Computing -- Queen's University
 *
 * Description: this code creates a shortcut for the launch configuration for MDebugger
 * 
 * Contributors:
 *     Nicolas Hili <hili@cs.queensu.ca> - initial API and implementation
 ******************************************************************************/

package ca.queensu.cs.mdebugger.launchconfiguration.shortcuts;

import org.eclipse.core.resources.IResource;
import org.eclipse.debug.core.ILaunchConfigurationType;
import org.eclipse.debug.internal.core.LaunchConfigurationType;
import org.eclipse.debug.internal.ui.launchConfigurations.LaunchConfigurationManager;
import org.eclipse.debug.internal.ui.launchConfigurations.LaunchConfigurationTypeFilter;
import org.eclipse.debug.ui.ILaunchShortcut;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.ui.IEditorPart;

import ca.queensu.cs.mdebugger.launchconfiguration.delegate.MDebuggerLaunchConfigurationDelegate;

public class MDebuggerLaunchShortcut implements ILaunchShortcut {

	@Override
	public void launch(ISelection selection, String mode) {
		IResource umlResource = (IResource) ((IStructuredSelection)selection).getFirstElement();
		System.out.println(umlResource.getFileExtension());
		System.out.println(umlResource);
		
		MDebuggerLaunchConfigurationDelegate delegate = new MDebuggerLaunchConfigurationDelegate();
		delegate.launch(selection, mode);
	}

	@Override
	public void launch(IEditorPart editor, String mode) {
		System.out.println("Editor: " + mode);
		System.out.println(editor);
	}
	
	
	

}
