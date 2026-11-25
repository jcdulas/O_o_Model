"""Write the shared 200 by 100 shell patch for the snapshot benchmark."""
import sys

with open(sys.argv[1], "w", encoding="ascii") as deck:
    deck.write("[model]\nRectFrame2;7;;0.;0.;0.;0.;0.;1.;0.;1.;0.\n")
    deck.write("ShellProp;1;1;0.01\nIsoMat;1;7.E+4;;0.33\n")
    for j in range(101):
        for i in range(201):
            node = 1 + i + 201 * j
            cd = 7 if node % 100 == 1 else 0
            deck.write(f"Node;{node};;{i}.;{j}.;0.;{cd}\n")
    for j in range(100):
        for i in range(200):
            node = 1 + i + 201 * j
            deck.write(f"ShellQuad4;{1+i+200*j};1;{node};{node+1};{node+202};{node+201}\n")
