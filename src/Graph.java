/* ============================================================
 *
 * This file is developed as part of the Dev-wars contest in Instruo 2014
 * held by Indian Institute of Engineering Science and Technology Shibpur.
 *
 * Date        : 2014-23-04
 * Description : creates a frame and displays the coloured graph
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


import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;

import java.awt.Point;

import java.awt.Rectangle;

import java.util.Collection;
import java.util.Random;

import javax.swing.BorderFactory;
import javax.swing.JEditorPane;
import javax.swing.JFrame;

import javax.swing.JButton;
import javax.swing.JMenuBar;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSplitPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextArea;
import javax.swing.JToolBar;
import javax.swing.border.Border;

public class Graph extends JPanel{

    private int numberOfNodes, numberOfEdges;
    private int [] nodeNumber = new int[50];
    private String [] nodeName = new String[50];
    private int [] nodeColor = new int[50];
    private int [] edgeSource = new int[500];
    private int [] edgeDest = new int[500];

    public Graph (int non, int noe, int[] num, String[] name, int[] color, int[] from, int[] to) {
      //System.out.println ("creating a graph");
      this.setBackground(Color.white);
      this.setBorder(BorderFactory.createLineBorder(Color.black));
      numberOfNodes = non;
      numberOfEdges = noe;
      int colorCounter = 0;
      for (int i=0; i<numberOfNodes; i++) {
          nodeNumber[i] = num[i];
          nodeName[i] = name[i];
          nodeColor[i] = color[i];
          if (color[i] > colorCounter)  colorCounter = color[i];
      }
      for (int i=0; i<numberOfEdges; i++) {
          edgeSource[i] = from[i];
          edgeDest[i] = to[i];
      }
      JOptionPane.showMessageDialog(null, "number of messages sent to rebel bases: " + colorCounter);
    }

    public void draw () {
        System.out.println ("Graph (" + numberOfNodes + " nodes, " + numberOfEdges + " edges):");
        for (int i=0; i<numberOfNodes; i++) {
            System.out.println ("node #" + nodeNumber[i] + " name:" + nodeName[i] + " color:" + nodeColor[i]);    
        }
        for (int i=0; i<numberOfEdges; i++) {
            System.out.println ("edge #" + i + " from:" + edgeSource[i] + " to: " + edgeDest[i]);    
        }
    }
    
    public void paintComponent (Graphics g) {
        super.paintComponent(g);
        System.out.println ("paint");
        int ht = this.getHeight();
        int wd = this.getWidth();
        int [] centerX = new int[50];
        int [] centerY = new int[50];
        int side;
        side = (ht < wd)?ht:wd;
        side /= 20;
        g.setColor (Color.black);
        for (int i=0; i<numberOfNodes; i++) {
            centerX[nodeNumber[i]] = ((int)(Math.random()*(wd-2*side)) / side + 1) * side;
            centerY[nodeNumber[i]] = ((int)(Math.random()*(ht-2*side)) / side + 1) * side;
            System.out.println ("placing at: " + centerX[i] + "," + centerY[i]);
        }
        for (int i=0; i<numberOfEdges; i++) {
            g.drawLine(centerX[edgeSource[i]], centerY[edgeSource[i]], centerX[edgeDest[i]], centerY[edgeDest[i]]);   
        }
        for (int i=1; i<=numberOfNodes; i++) {
            System.out.println ("color " + i + " " + nodeColor[i-1]);
            g.setColor (Color.getHSBColor((float)nodeColor[i-1]/5, (float)nodeColor[i-1]/5, (float)nodeColor[i-1]/5));
            g.fillOval(centerX[i]-side/2, centerY[i]-side/2, side, side);
            g.drawString(nodeName[i-1], centerX[i]-side/2, centerY[i] + 1*side);
            System.out.println ("draws string: " + nodeName[i-1]);
        }
    }
}
