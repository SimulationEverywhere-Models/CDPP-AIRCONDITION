.SUFFIXES : .cpp .o .c .y

include Makefile.common

#Basic models
export EXAMPLESOBJS=queue.o main.o generat.o cpu.o transduc.o constgenerat.o distri.o com.o linpack.o register.o ufc.o gentemp.o ucontrol.o proptemp.o

UTILOBJS = ntupla.o cellstate.o strutil.o ini.o $(COMMON)/src/VTime.o \
	real.o impresion.o tbool.o realprec.o except.o macroexp.o
 
#DRAWOBJS= drawlog.o logparser.o	 $(UTILOBJS)

LOGBUFFEROBJS= logbuffer.o logparser.o $(UTILOBJS)

PARLOGOBJS= parlog.o logparser.o pini.o $(UTILOBJS)


LIBNAME=simu
LIBS += -lsimu
ALLOBJS=${EXAMPLESOBJS}
INIOBJS=initest.o ini.o strutil.o
PINIOBJS=pinitest.o pini.o strutil.o
ALLSRCS=${ALLOBJS:.o=.cpp} gram.y 

all: libs cd++

libs: libsimu.a

cd++: ${ALLOBJS} libsimu.a $(TWOBJ)/$(TWLIB) $(MODELLIBS)
	${CPP} ${LDFLAGS} -o $@  ${EXAMPLESOBJS} ${LIBS} ${PLIBS}

$(TWOBJ)/$(TWLIB):
	$(MAKE) -j6 -l5 -C $(TWDIR)

initest: ${INIOBJS}  
	${CPP} ${LDFLAGS} -o $@ ${INIOBJS}

pinitest: ${PINIOBJS}
	${CPP} ${LDFLAGS} -o $@ ${PINIOBJS}

#drawlog: ${DRAWOBJS}
#	g++ ${CPPFLAGS} ${LDFLAGS} -o $@ ${DRAWOBJS}

logbuffer: ${LOGBUFFEROBJS}
	g++ ${CPPLAGS} ${LDFLAGS} -o $@ ${LOGBUFFEROBJS}

parlog: ${PARLOGOBJS}
	g++ ${CPPFLAGS }${LDFLAGS} -o $@ ${PARLOGOBJS}
	
makerand: makerand.o $(UTILOBJS)
	g++ ${CPPFLAGS} ${LDFLAGS} -o $@ makerand.o ${UTILOBJS}

toMap: toMap.o $(UTILOBJS)
	g++ ${CPPFLAGS} ${LDFLAGS} -o $@ toMap.o ${UTILOBJS}

toCDPP: toCDPP.o $(UTILOBJS)
	g++ ${CPPFLAGS} ${LDFLAGS} -o $@ toCDPP.o ${UTILOBJS}

randEvent: randEvent.o $(UTILOBJS)
	g++ ${CPPFLAGS} ${LDFLAGS} -o $@ randEvent.o ${EXAMPLESOBJS} ${UTILOBJS}

exptest: synnode.o
	g++ ${LDFLAGS} -o $@ synnode.o
	
parser: parser.o gram.o
	g++ ${LDFLAGS} -o $@ parser.o gram.o

#libsimu.a:  ${AR} crs lib${LIBNAME}.a

depend:
	makedepend -Y ${ALLSRCS}
	make -C ./warped/TimeWarp/src depend
	make -C ./warped/NoTime/src depend
	make -C ./warped/common depend
	make -C ./models/airport depend
	make -C ./models/net depend

backup:
	tar -cvzf simu.tar.gz *.cpp *.h *.c *.y Makefile* makefile* *.ma *.ev *.vpj *.bat *.txt *.val *.inc *.map 


##############
MODELS:

./models/libnet.a:
	make -C ./models/net

./models/libairport.a:
	make -C ./models/airport
	
########################
# Without Optimization
proptemp.o: proptemp.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

ucontrol.o: ucontrol.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

gentemp.o: gentemp.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

ufc.o: ufc.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

generat.o: generat.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

queue.o: queue.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

cpu.o: cpu.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

transduc.o: transduc.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

trafico.o: trafico.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

register.o: register.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

msgadm.o: msgadm.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

root.o: root.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

parser.o: parser.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

main.o: main.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

#drawlog.o: drawlog.cpp
#	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

toMap.o: toMap.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

toCDPP.o: toCDPP.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

makerand.o: makerand.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

mainsimu.o: mainsimu.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

stdasimu.o: stdasimu.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<

parsimu.o: parsimu.cpp
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<


# Uncomment these lines only for Windows
#macroexp.o: macroexp.cpp
#	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<
#
#flatcoup.o: flatcoup.cpp
#	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} $<
########################

.cpp.o:
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} ${OPTCPPFLAGS} $<

.c.o:
	${CC} -c ${INCLUDES_C} ${DEFINES_C}  ${DEBUGFLAGS} ${CFLAGS} ${OPTCPPFLAGS} $<

.y.o:
	bison -d -v -o gram.c gram.y
	${CPP} -c ${INCLUDES_CPP} ${DEFINES_CPP} ${DEBUGFLAGS} ${CPPFLAGS} ${OPTCPPFLAGS} ${@:.o=.c} 
	rm $*.c
	
# DO NOT DELETE
queue.o: queue.h atomic.h model.h machineid.h port.h modelid.h pmodeladm.h
queue.o: strutil.h real.h undefd.h impresion.h tbool.h except.h stringp.h
queue.o: value.h evaldeb.h cellpos.h ntupla.h portlist.h pprocadm.h
queue.o: pprocess.h pProcessorState.h msgbag.h modelstate.h atomicstate.h
queue.o: pSimulatorState.h message.h parsimu.h proot.h event.h eventlist.h
queue.o: prootmodel.h pRootState.h ini.h pini.h loader.h ltranadm.h log.h
queue.o: process.h
main.o: strutil.h real.h undefd.h impresion.h tbool.h except.h stringp.h
main.o: value.h evaldeb.h stdaload.h loader.h macroexp.h netload.h parsimu.h
main.o: proot.h event.h port.h modelid.h pmodeladm.h cellpos.h ntupla.h
main.o: eventlist.h prootmodel.h model.h machineid.h portlist.h pprocadm.h
main.o: pprocess.h pProcessorState.h msgbag.h modelstate.h pRootState.h ini.h
main.o: pini.h ltranadm.h log.h
generat.o: generat.h atomic.h model.h machineid.h port.h modelid.h
generat.o: pmodeladm.h strutil.h real.h undefd.h impresion.h tbool.h except.h
generat.o: stringp.h value.h evaldeb.h cellpos.h ntupla.h portlist.h
generat.o: pprocadm.h pprocess.h pProcessorState.h msgbag.h modelstate.h
generat.o: atomicstate.h pSimulatorState.h message.h parsimu.h proot.h
generat.o: event.h eventlist.h prootmodel.h pRootState.h ini.h pini.h
generat.o: loader.h ltranadm.h log.h process.h distri.h
cpu.o: cpu.h atomic.h model.h machineid.h port.h modelid.h pmodeladm.h
cpu.o: strutil.h real.h undefd.h impresion.h tbool.h except.h stringp.h
cpu.o: value.h evaldeb.h cellpos.h ntupla.h portlist.h pprocadm.h pprocess.h
cpu.o: pProcessorState.h msgbag.h modelstate.h atomicstate.h
cpu.o: pSimulatorState.h message.h parsimu.h proot.h event.h eventlist.h
cpu.o: prootmodel.h pRootState.h ini.h pini.h loader.h ltranadm.h log.h
cpu.o: process.h distri.h
transduc.o: transduc.h atomic.h model.h machineid.h port.h modelid.h
transduc.o: pmodeladm.h strutil.h real.h undefd.h impresion.h tbool.h
transduc.o: except.h stringp.h value.h evaldeb.h cellpos.h ntupla.h
transduc.o: portlist.h pprocadm.h pprocess.h pProcessorState.h msgbag.h
transduc.o: modelstate.h atomicstate.h pSimulatorState.h message.h parsimu.h
transduc.o: proot.h event.h eventlist.h prootmodel.h pRootState.h ini.h
transduc.o: pini.h loader.h ltranadm.h log.h process.h
constgenerat.o: constgenerat.h atomic.h model.h machineid.h port.h modelid.h
constgenerat.o: pmodeladm.h strutil.h real.h undefd.h impresion.h tbool.h
constgenerat.o: except.h stringp.h value.h evaldeb.h cellpos.h ntupla.h
constgenerat.o: portlist.h pprocadm.h pprocess.h pProcessorState.h msgbag.h
constgenerat.o: modelstate.h atomicstate.h pSimulatorState.h message.h
constgenerat.o: parsimu.h proot.h event.h eventlist.h prootmodel.h
constgenerat.o: pRootState.h ini.h pini.h loader.h ltranadm.h log.h process.h
distri.o: distri.h except.h stringp.h strutil.h real.h undefd.h impresion.h
distri.o: tbool.h value.h evaldeb.h randlib.h
register.o: pmodeladm.h strutil.h real.h undefd.h impresion.h tbool.h
register.o: except.h stringp.h value.h evaldeb.h modelid.h cellpos.h ntupla.h
register.o: parsimu.h proot.h event.h port.h eventlist.h prootmodel.h model.h
register.o: machineid.h portlist.h pprocadm.h pprocess.h pProcessorState.h
register.o: msgbag.h modelstate.h pRootState.h ini.h pini.h loader.h
register.o: ltranadm.h log.h queue.h atomic.h atomicstate.h pSimulatorState.h
register.o: message.h process.h generat.h cpu.h transduc.h constgenerat.h
gram.o: synnode.h tbool.h except.h stringp.h real.h undefd.h impresion.h
gram.o: value.h evaldeb.h realfunc.h ltranadm.h cellpos.h ntupla.h portlist.h
gram.o: port.h modelid.h pmodeladm.h strutil.h model.h machineid.h pprocadm.h
gram.o: pprocess.h pProcessorState.h msgbag.h modelstate.h parser.h
