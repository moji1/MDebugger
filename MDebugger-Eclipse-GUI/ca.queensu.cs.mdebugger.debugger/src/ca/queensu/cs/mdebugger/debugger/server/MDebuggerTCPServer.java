/*******************************************************************************
 * Copyright (c) 2016 School of Computing -- Queen's University
 *
 * Description: no description currently
 * 
 * Contributors:
 *     Nicolas Hili <hili@cs.queensu.ca> - initial API and implementation
 ******************************************************************************/
package ca.queensu.cs.mdebugger.debugger.server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

import org.eclipse.debug.core.model.IDebugTarget;
import java.io.PrintStream;
import org.eclipse.ui.console.ConsolePlugin;
import org.eclipse.ui.console.IConsole;
import org.eclipse.ui.console.IConsoleManager;
import org.eclipse.ui.console.MessageConsole;
import org.eclipse.ui.console.MessageConsoleStream;

import ca.queensu.cs.mdebugger.debugger.model.MDebuggerDebugTarget;

/**
 * @author nicolas
 *
 */
public class MDebuggerTCPServer implements Runnable {

	ServerSocket serverSocket;
    Socket socket;
    IDebugTarget target;
    ArrayList<Thread> threads;
    int port;
    boolean isRunning;
    
	public MDebuggerTCPServer(int port, IDebugTarget target) {
		
	//	MessageConsole myConsole = findConsole("MDebugger Console");
	//    MessageConsoleStream out = myConsole.newMessageStream();
	//    System.setOut(new PrintStream(out));
	//    System.setErr(new PrintStream(out));

		serverSocket = null;
		socket = null;
		this.threads = new ArrayList<Thread>();
		this.port = port;
		this.target = target;
	}
	
	@Override
	public void run() {
		isRunning = true;
		try {
			System.out.println(this.port);
			serverSocket = new ServerSocket(this.port);
			System.out.println("socket communication created");
		} catch (IOException e) {
		}
		
		while (isRunning) {
            try {
            	System.out.println("now accepting new client");
                socket = serverSocket.accept();
                MDebuggerTCPSocket reader = new MDebuggerTCPSocket(socket, target);
                MDebuggerTCPWriter writer = new MDebuggerTCPWriter(socket, target, reader);
                ((MDebuggerDebugTarget)target).setReader(reader);
                ((MDebuggerDebugTarget)target).setWriter(writer);
                
                threads.add(reader);
                
                reader.start();
            } catch (IOException e) {
            	socket = null;
            	continue;
            }
        }
	}
	
	public void close() {
		try {
			isRunning = false;
			for (Thread reader: threads) {
				reader.interrupt();
			}
			if (serverSocket != null)
				serverSocket.close();
		} catch (IOException e) {}
	}
	
	private MessageConsole findConsole(String name) {
	      ConsolePlugin plugin = ConsolePlugin.getDefault();
	      IConsoleManager conMan = plugin.getConsoleManager();
	      IConsole[] existing = conMan.getConsoles();
	      for (int i = 0; i < existing.length; i++)
	         if (name.equals(existing[i].getName()))
	            return (MessageConsole) existing[i];
	      //no console found, so create a new one
	      MessageConsole myConsole = new MessageConsole(name, null);
	      conMan.addConsoles(new IConsole[]{myConsole});
	      return myConsole;
	   }

}
