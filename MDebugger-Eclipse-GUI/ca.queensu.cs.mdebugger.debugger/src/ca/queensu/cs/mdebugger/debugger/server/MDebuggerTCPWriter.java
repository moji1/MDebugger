/*******************************************************************************
 * Copyright (c) 2016 School of Computing -- Queen's University
 *
 * Description: no description currently
 * 
 * Contributors:
 *     Nicolas Hili <hili@cs.queensu.ca> - initial API and implementation
 ******************************************************************************/
package ca.queensu.cs.mdebugger.debugger.server;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

import org.eclipse.debug.core.model.IDebugTarget;
import org.eclipse.uml2.uml.Element;
import org.eclipse.uml2.uml.NamedElement;
import org.eclipse.uml2.uml.State;

import ca.queensu.cs.mdebugger.debugger.breakpoints.MDebuggerBreakpoint;
import ca.queensu.cs.mdebugger.debugger.breakpoints.MDebuggerBreakpointPosition;
import ca.queensu.cs.mdebugger.debugger.server.MDebuggerTCPSocket.Command;

/**
 * @author nicolas
 *
 */
public class MDebuggerTCPWriter {

	protected Socket socket;
	private IDebugTarget target;
	private DataOutputStream out;
	private MDebuggerTCPSocket reader;
	private static int commandId = 0;
	
	public MDebuggerTCPWriter(Socket clientSocket, IDebugTarget target, MDebuggerTCPSocket reader) {
		this.socket = clientSocket;
		this.target = target;
		this.reader = reader;
		commandId = 0;
    	
        this.out = null;
        try {
            out = new DataOutputStream(socket.getOutputStream());
        } catch (IOException e) {
            return;
        }
	}
	

	public void requestCapsuleList() {
		sendMessage("list Counter:Counter:0 -b",
				MDebuggerTCPSocket.Command.WAITING_FOR_BREAKPOINT_LIST);
	}
	
	public void requestEventList(String capsuleName, int n) {
		sendMessage("v -c "+ capsuleName +" -n " + String.valueOf(n) + " -e",
					MDebuggerTCPSocket.Command.WAITING_FOR_EVENT_LIST);
	}
	
	public void modifyValue(String capsuleName, String variableName, String value) {
		sendMessage("m -c " + capsuleName + " -n " + variableName + " -v " + value,
				MDebuggerTCPSocket.Command.WAITING_FOR_VALUE_CHANGE_ACK);
	}
	
	public void stepOver(String capsuleName) {
		sendMessage("n -c " + capsuleName,
				MDebuggerTCPSocket.Command.STEPPING);
	}
	
	public void requestLastEvent() {
	}
	
	public void resumeCapsule(String capsuleName) {
		sendMessage("c -c " + capsuleName,
				MDebuggerTCPSocket.Command.RESUME);
	}
	
	public void toggleBreakpoint(MDebuggerBreakpoint breakpoint, String capsuleName, boolean remove) {
		MDebuggerBreakpointPosition position = breakpoint.getPosition();
		Element element = breakpoint.getElement();
		String buf = "b -c " + capsuleName;
		NamedElement owner = (NamedElement)element.getOwner();
		buf += (owner instanceof State) ? " -s " : " -t ";
		buf += owner.getName();
		buf += (MDebuggerBreakpointPosition.AFTER.equals(position)) ? " -e " : " -b ";
		if (owner instanceof State) {
			buf += " -" + (element.eContainingFeature()).getName();
		}
		if (remove) {
			buf += " -r ";
		}
		System.out.println(buf);
		sendMessage(buf, Command.WAITING_FOR_ACK);
	}
	
	private void sendMessage(String message, Command cmd) {
		message = message + " -i " + ++commandId; 
		if (!message.startsWith("v")) {
			System.out.println(message);
		}
		String messageSize = String.valueOf(message.length());
		int length = messageSize.length();
		
		for (int i = 4; i > length; i--) {
			messageSize = "0" + messageSize;
		}
		
		message = messageSize + message;
	
		
		try {
//			System.out.println("sending message: '" + message + "'");
			this.reader.getCommandStack().put(commandId, cmd);
			if (commandId >= 1000) {
				commandId = 0;
			}
			out.write(message.getBytes());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}


}
