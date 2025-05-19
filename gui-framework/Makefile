objects2 = main.o CuWindow.o FlowPanel.o AbsolutePanel.o TextArea.o Button.o Tester.o RGB.o Component.o ComponentList.o TestControl.o Panel.o View.o
#objects1 = tests1.o CuWindow.o FlowPanel.o AbsolutePanel.o TextArea.o Button.o Tester.o RGB.o Component.o ComponentList.o Panel.o 
libs = -std=c++11 -lX11

all: a3

a3: $(objects2)
	g++ -o a3 $(objects2) $(libs) -std=c++11 -lX11

main.o: main.cc defs.h
	g++ -c main.cc -I /opt/X11/include

RGB.o: RGB.h RGB.cc defs.h
	g++ -c RGB.cc -I /opt/X11/include

Panel.o: Panel.h Panel.cc defs.h
	g++ -c Panel.cc -I /opt/X11/include

FlowPanel.o: FlowPanel.h FlowPanel.cc defs.h
	g++ -c FlowPanel.cc -I /opt/X11/include

AbsolutePanel.o: AbsolutePanel.h AbsolutePanel.cc defs.h
	g++ -c AbsolutePanel.cc -I /opt/X11/include

TextArea.o: TextArea.h TextArea.cc defs.h
	g++ -c TextArea.cc -I /opt/X11/include

Button.o: Button.h Button.cc defs.h
	g++ -c Button.cc -I /opt/X11/include

CuWindow.o: CuWindow.h CuWindow.cc defs.h
	g++ -c CuWindow.cc -I /opt/X11/include

Tester.o: Tester.h Tester.cc defs.h
	g++ -c Tester.cc -I /opt/X11/include

Component.o: Component.h Component.cc defs.h
	g++ -c Component.cc -I /opt/X11/include

ComponentList.o: ComponentList.h ComponentList.cc defs.h
	g++ -c ComponentList.cc -I /opt/X11/include

TestControl.o: TestControl.h TestControl.cc defs.h
	g++ -c TestControl.cc -I /opt/X11/include

View.o: View.h View.cc defs.h
	g++ -c View.cc -I /opt/X11/include

clean:
	rm a3 *.o