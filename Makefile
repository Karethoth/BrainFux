CC     = g++
TGT    = brainfux
SRCDIR = src

CFLAGS = -Ofast

all: $(TGT)

$(TGT):
	$(CC) $(CFLAGS) -o $(TGT) $(SRCDIR)/*.cc

clean:
	rm -f $(TGT)

