package ca.queensu.cs.mdebugger.launchconfiguration.tabs;

import java.io.IOException;
import java.io.InputStream;
import java.net.URL;

import org.eclipse.core.resources.IResource;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.debug.core.ILaunchConfiguration;
import org.eclipse.debug.core.ILaunchConfigurationWorkingCopy;
import org.eclipse.debug.ui.AbstractLaunchConfigurationTab;
import org.eclipse.jface.layout.GridLayoutFactory;
import org.eclipse.jface.window.Window;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.layout.FillLayout;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.FileDialog;
import org.eclipse.swt.widgets.Group;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Text;
import org.eclipse.ui.dialogs.ElementTreeSelectionDialog;
import org.eclipse.ui.model.BaseWorkbenchContentProvider;
import org.eclipse.ui.model.WorkbenchLabelProvider;

import ca.queensu.cs.mdebugger.launchconfiguration.configurations.MDebuggerConfigurationAttributes;

public class MDebuggerTab extends AbstractLaunchConfigurationTab {
    private Text diText;
    private Text cppText;
    private Button btnBrowseWorkspace;
    private Button btnBrowseExternalFiles;
	

    /**
     * @wbp.parser.entryPoint
     */
    @Override
    public void createControl(Composite parent) {

            Composite comp = new Group(parent, SWT.NONE);
            setControl(comp);

            GridLayoutFactory.swtDefaults().numColumns(2).applyTo(comp);
            comp.setLayout(new FillLayout(SWT.VERTICAL));
            
            Group grpModelConfiguration = new Group(comp, SWT.NONE);
            grpModelConfiguration.setText("Model Configuration");
            grpModelConfiguration.setLayout(new GridLayout(3, false));
                                                            
	        Label diLabel = new Label(grpModelConfiguration, SWT.NONE);
	        diLabel.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));
	        diLabel.setText("UML file");
	        
	        diText = new Text(grpModelConfiguration, SWT.BORDER);
	        diText.setMessage("UML file");
	        diText.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
	        
	        btnBrowseWorkspace = new Button(grpModelConfiguration, SWT.NONE);
	        btnBrowseWorkspace.setText("Browse workspace...");
	        new Label(grpModelConfiguration, SWT.NONE);
	        new Label(grpModelConfiguration, SWT.NONE);
	        
	        btnBrowseExternalFiles = new Button(grpModelConfiguration, SWT.NONE);
	        btnBrowseExternalFiles.setText("Browse external files...");
	        
	        btnBrowseWorkspace.addSelectionListener(new SelectionListener() {
				
				@Override
				public void widgetSelected(SelectionEvent e) {
					String path = promptWorkspacePath("Select a Papyrus-RT UML file", new String[] {"*.uml"});
					if (path != "")
						diText.setText(path);
				}
				
				@Override
				public void widgetDefaultSelected(SelectionEvent e) {}
			});
	        
	        btnBrowseExternalFiles.addSelectionListener(new SelectionListener() {
				
				@Override
				public void widgetSelected(SelectionEvent e) {
					
					String path = promptDirectoryPath("Select a Papyrus-RT UML file", new String[] {"*.uml"});
					if (path != "")
						diText.setText(path);
				}
				
				@Override
				public void widgetDefaultSelected(SelectionEvent e) {}
			});
	        
	        Group grpCConfiguration = new Group(comp, SWT.NONE);
	        grpCConfiguration.setText("C++ Configuration");
	        grpCConfiguration.setLayout(new GridLayout(3, false));
	        
	        Label cppLabel = new Label(grpCConfiguration, SWT.NONE);
	        cppLabel.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));
	        cppLabel.setText("Main script");
	        
	        cppText = new Text(grpCConfiguration, SWT.BORDER);
	        cppText.setMessage("TopMain");
	        cppText.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
	        
	        btnBrowseWorkspace = new Button(grpCConfiguration, SWT.NONE);
	        btnBrowseWorkspace.setText("Browse worskpace...");
	        new Label(grpCConfiguration, SWT.NONE);
	        new Label(grpCConfiguration, SWT.NONE);
	        
	        btnBrowseExternalFiles = new Button(grpCConfiguration, SWT.NONE);
	        btnBrowseExternalFiles.setText("Browse external files...");
	        
	        btnBrowseExternalFiles.addSelectionListener(new SelectionListener() {
				
				@Override
				public void widgetSelected(SelectionEvent e) {
					
					String path = promptDirectoryPath("Set main script", new String[0]);
					if (path != "")
						cppText.setText(path);
				}
				
				@Override
				public void widgetDefaultSelected(SelectionEvent e) {}
			});
	        
	        btnBrowseWorkspace.addSelectionListener(new SelectionListener() {
				
				@Override
				public void widgetSelected(SelectionEvent e) {
					String path = promptWorkspacePath("Set main script", null);
					if (path != "")
						cppText.setText(path);
				}
				
				@Override
				public void widgetDefaultSelected(SelectionEvent e) {}
			});
	        
	        
    }
    
    private String promptDirectoryPath(String text, String[] extensions) {
    	
    	FileDialog dialog = new FileDialog(Display.getCurrent().getActiveShell());
		dialog.setText(text);
		
		if (extensions != null && extensions.length > 0)
			dialog.setFilterExtensions(extensions);
		
		String result = dialog.open();
		
		setDirty(true);
		updateLaunchConfigurationDialog();
		return result;
    }
    
    private String promptWorkspacePath(String text, String[] extensions) {
    	ElementTreeSelectionDialog dialog = new ElementTreeSelectionDialog(
			Display.getCurrent().getActiveShell(),
		    new WorkbenchLabelProvider(),
		    new BaseWorkbenchContentProvider()
		);

		dialog.setInput( ResourcesPlugin.getWorkspace().getRoot() );
		dialog.setAllowMultiple(false);
		if( dialog.open() == Window.OK ) {
		    IResource resource = (IResource) dialog.getFirstResult();
		    setDirty(true);
		    updateLaunchConfigurationDialog();
		    return resource.getFullPath().toString();
		}
		return "";
    }

    @Override
    public void setDefaults(ILaunchConfigurationWorkingCopy configuration) {
    }

    @Override
    public void initializeFrom(ILaunchConfiguration configuration) {
            try {
            	String diTextConfig = configuration.getAttribute(MDebuggerConfigurationAttributes.DI_PATH, "");
            	String cppTextConfig = configuration.getAttribute(MDebuggerConfigurationAttributes.CPP_PATH, "");

            	diText.setText(diTextConfig);
                cppText.setText(cppTextConfig);
                
            } catch (CoreException e) {
                    // ignore here
            }
    }

    @Override
    public void performApply(ILaunchConfigurationWorkingCopy configuration) {
    	configuration.setAttribute(MDebuggerConfigurationAttributes.DI_PATH, diText.getText());
    	configuration.setAttribute(MDebuggerConfigurationAttributes.CPP_PATH, cppText.getText());
    }

    @Override
    public String getName() {
            return "Mdebugger";
    }
    
    @Override
    protected void setDirty(boolean dirty) {
    	super.setDirty(dirty);
    }
    
    @Override
    public Image getImage() {
    	URL url = getClass().getResource("/icons/bug.png");
    	InputStream is;
		try {
			is = url.openStream();
			Image image = new Image(Display.getCurrent(), is);
			return image;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return super.getImage();
    }
    
    
    
}
