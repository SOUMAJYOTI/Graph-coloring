/* ============================================================
 *
 * This file is developed as part of the Dev-wars contest in Instruo 2014
 * held by Indian Institute of Engineering Science and Technology Shibpur.
 *
 * Date        : 2014-23-04
 * Description : creates frame for decryption and creating coloured graph.
 *
 * Copyright (C) 2014 by Sibashis Chatterjee 
 * Copyright (C) 2014 by Soumajyoti Sarkar
 * Copyright (C) 2014 by Anurag Chatterjee
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */


import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

import java.util.Scanner;

import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;


public class Plot_graph extends JFrame {
    private JButton jButton1 = new JButton();
    private JTextField jTextField1 = new JTextField("input File");
    private JButton jButton2 = new JButton();
    private JButton jButton3 = new JButton();
    private JScrollPane jScrollPane1 = new JScrollPane();
    private JScrollPane jScrollPane2 = new JScrollPane();
    private JLabel jLabel1 = new JLabel();
    private JTextArea jTextArea1 = new JTextArea();

    public Plot_graph() {
        try {
            jbInit();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void jbInit() throws Exception {
        this.getContentPane().setLayout( null );
        this.setSize(new Dimension(757, 509));
        this.setTitle("Imperial Forces");
        this.setResizable(false);
        jButton1.setText("Plot the Graph");
        jButton1.setBounds(new Rectangle(585, 25, 150, 25));
        jButton1.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    jButton1_actionPerformed(e);
                }
            });
        jTextField1.setBounds(new Rectangle(15, 25, 255, 25));
        jButton2.setText("Browse");
        jButton2.setBounds(new Rectangle(295, 25, 80, 25));
        jButton2.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    jButton2_actionPerformed(e);
                }
            });
        jButton3.setText("Decrypt File");
        jButton3.setBounds(new Rectangle(405, 25, 150, 25));
        jButton3.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    jButton3_actionPerformed(e);
                }
            });
        jScrollPane2.setBounds(new Rectangle(15, 70, 720, 380));
        jLabel1.setText("designed by: SSH (team ID 007), IIESTS for dev-wars, Instruo 2014");
        jLabel1.setBounds(new Rectangle(110, 460, 625, 15));
        jScrollPane2.getViewport().add(jTextArea1, null);
        jButton1.setEnabled(false);
        jButton3.setEnabled(false);
        this.getContentPane().add(jLabel1, null);
        this.getContentPane().add(jScrollPane2, null);
        this.getContentPane().add(jScrollPane1, null);
        this.getContentPane().add(jButton3, null);
        this.getContentPane().add(jButton2, null);
        this.getContentPane().add(jTextField1, null);
        this.getContentPane().add(jButton1, null);
    }

    private void jButton1_actionPerformed(ActionEvent e) {
        System.out.println ("opening: " + this.jTextField1.getText());
        Scanner scanner;
        int numberOfNodes, numberOfEdges;
        int [] nodeNumber = new int[50];
        String [] nodeNames = new String[50];
        int [] nodeColor = new int[50];
        int [] startOfEdge = new int [500];
        int [] endOfEdge = new int [500];
        try {
            //String decryptionExecutableLocation = "/home/anurag/Desktop/DevContest/Parsefile";
            String graphExecutableLocation = "./objects/Graphcolor";
            String decryptedFileLocation = "./files/decryptedFile.txt";
            String graphFileLocation = "./files/graphFile.txt";
            //String sourceFileLocation = "./objects/Parsefile.cpp";
            File executableFile = new File(graphExecutableLocation);
            if(executableFile.exists()) {
                ProcessBuilder pb = new ProcessBuilder(graphExecutableLocation, decryptedFileLocation, graphFileLocation);
                Process p = pb.start();
                try {
                    p.waitFor();
                } catch (InterruptedException f) {
                    System.out.println ("process error: " + f.toString());
                }
            }
        } catch(IOException f) {
            System.out.println ("exception found: " + e.toString());
        }
        File inFile = new File ("./files/graphFile.txt");
        try {
            scanner = new Scanner (inFile);
            numberOfNodes = scanner.nextInt();
            if (numberOfNodes > 50) {
                System.out.println ("input too big, can handle max 50 nodes");
                numberOfNodes = 50;
            }
            for (int i=0; i<numberOfNodes; i++) {
                nodeNumber[i] = scanner.nextInt();
                nodeNames[i] = scanner.next();
                nodeColor[i] = scanner.nextInt();
                //System.out.println (i + ": " + nodeNames[i] + "(" + nodeNumber[i] + ") has color " + nodeColor[i]);
            }
            numberOfEdges = scanner.nextInt();
            if (numberOfEdges > 500) {
                System.out.println ("input too big, can handle max 500 edges");
                numberOfEdges = 500;
            }
            for (int i=0; i<numberOfEdges; i++) {
                startOfEdge[i] = scanner.nextInt();
                endOfEdge[i] = scanner.nextInt();
                //System.out.println ("edge #" + i + ": from " + startOfEdge[i] + " to " + endOfEdge[i]);
            }
            //System.out.println ("create graph");
            JFrame gFrame = new JFrame();
            gFrame.setTitle("Coloured Graph");
            Graph myGraph = new Graph(numberOfNodes, numberOfEdges, nodeNumber, nodeNames, nodeColor, startOfEdge, endOfEdge);
            myGraph.setPreferredSize(new Dimension(600, 600));
            gFrame.getContentPane().add (myGraph,BorderLayout.CENTER);
            gFrame.pack ();
            //myGraph.paintComponent(gFrame.getGraphics());
            gFrame.setVisible(true);
        } catch (FileNotFoundException f) {
            System.out.println ("Scanner cannot be opened");
        } catch (Exception g) {
            System.out.println ("exception caught: " + g.toString());    
        }
    }

    private void jButton2_actionPerformed(ActionEvent e) {
        //System.out.println ("button clicked");
        JFileChooser fc;
        fc = new JFileChooser ();
        int returnVal = fc.showOpenDialog(this);
        if (returnVal == JFileChooser.APPROVE_OPTION) {
            File file = fc.getSelectedFile();
            this.jTextField1.setText(file.getPath());
        }
        this.jButton1.setEnabled (false);
        this.jButton3.setEnabled (true);
    }

  void GenerateDecryptedFile(String encryptedFilePath) {
        File encryptedFile = new File(encryptedFilePath);
        //if the file exists generate the decrypted file
        if(encryptedFile.exists()) {
            try {
                //String decryptionExecutableLocation = "/home/anurag/Desktop/DevContest/Parsefile";
                String decryptionExecutableLocation = "./objects/Parsefile";
                String decryptedFileLocation = "./files/decryptedFile.txt";
                //String sourceFileLocation = "./objects/Parsefile.cpp";
                File executableFile = new File(decryptionExecutableLocation);
                if(executableFile.exists()) {
                    /*ProcessBuilder pb1 = new ProcessBuilder ("/usr/bin/g++", "-o", "Parsefile", sourceFileLocation);
                    Process p1 = pb1.start();
                    try {
                        p1.waitFor();
                    } catch (InterruptedException e) {
                        System.out.println ("process handling error" + e.toString());
                    }*/
                    ProcessBuilder pb = new ProcessBuilder(decryptionExecutableLocation,encryptedFilePath,decryptedFileLocation);
                    Process p = pb.start();
                    try {
                        p.waitFor();
                    } catch (InterruptedException e) {
                        System.out.println ("process error: " + e.toString());
                    }
                }
            } catch(IOException e) {
                System.out.println ("exception found: " + e.toString());
            }            
        }
    }

    private void jButton3_actionPerformed(ActionEvent e) {
        String filename = this.jTextField1.getText();
        if (filename != "" && filename != "input File") {
            this.GenerateDecryptedFile(filename);
            /*try {
                this.wait(10);
            } catch (InterruptedException f) {
                System.out.println ("process error:" + e.toString());
            }*/
            File inFile = new File ("./files/decryptedFile.txt");
            Scanner scanner;
            try {
                scanner = new Scanner (inFile);
                //String text;
                while (scanner.hasNextLine()) {
                    String line = scanner.nextLine();
                    //text += line + "\n";
                    this.jTextArea1.append (line + "\n");
                }
                //this.jTextArea1.setText(text);
                int length;
                length = this.jTextArea1.getText().length();
                this.jTextArea1.setCaretPosition(length);
                this.jButton1.setEnabled(true);
            } catch (FileNotFoundException f) {
                System.out.println ("scanner error for decrypted file:" + e.toString());
            }
        } else {
        }
    }
}
