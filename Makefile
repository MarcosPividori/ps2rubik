
BINDIR = bin
OBJDIR = obj
SRCDIR = src

CC = ee-gcc
CFLAGS = -D_EE -O2 -G0 -Wall 
INCLUDES = -I$(PS2SDK)/ee/include -I$(PS2SDK)/common/include -I. -I$(PS2SDK)/samples/rpc/pad
LFLAGS = -mno-crt0 -T$(PS2SDK)/ee/startup/linkfile -L$(PS2SDK)/ee/lib -laudsrv -ldraw -lpad -lgraph -lmath3d -lmf -lpacket -ldma -lc -lc -lkernel 

SOURCESC = cubo.c cola.c visual.c audio.c joysticks.c generador.c rubik_solver.c beginner_solver.c run_rubik.c

OBJS = $(SOURCESC:%.c=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(BINDIR)/aud.adp $(BINDIR)/run_rubik.elf $(BINDIR)/audsrv.irx

$(BINDIR)/aud.adp: $(BINDIR)
	adpenc sound/aud.wav $(BINDIR)/aud.adp

$(BINDIR)/audsrv.irx: $(BINDIR)
	cp $(PS2SDK)/iop/irx/audsrv.irx $(BINDIR)/audsrv.irx

$(BINDIR)/run_rubik.elf: $(OBJS) $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/run_rubik.elf $(PS2SDK)/ee/startup/crt0.o $(OBJS) $(LFLAGS)

$(OBJDIR):
	mkdir $(OBJDIR)

$(BINDIR):
	mkdir $(BINDIR)

clean:
	rm -rf $(BINDIR) $(OBJDIR)

