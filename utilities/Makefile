RUMPOBJ?=${PWD}/../rumpobj
RUMPSRC?=../src
OUTDIR?=${PWD}/../rump
BINDIR?=$(OUTDIR)/bin
COMPILER?=$(BINDIR)/rumprun-cc
CC=$(COMPILER)
OBJDIR?=$(RUMPOBJ)/utilities
RUMPMAKE=$(RUMPOBJ)/tooldir/rumpmake

UTILS=$(BINDIR)/rump.pax $(BINDIR)/rump.mkdir $(BINDIR)/rump.ls $(BINDIR)/rump.rm $(BINDIR)/rump.ln $(BINDIR)/rump.dd \
	$(BINDIR)/rump.df $(BINDIR)/rump.rmdir $(BINDIR)/rump.chmod \
	$(BINDIR)/rump.mknod $(BINDIR)/rump.mount $(BINDIR)/rump.chown $(BINDIR)/rump.ifconfig $(BINDIR)/rump.route \
	$(BINDIR)/rump.newfs $(BINDIR)/rump.fsck_ffs $(BINDIR)/rump.ping $(BINDIR)/rump.ping6 $(BINDIR)/rump.rtadvd \
	$(BINDIR)/rump.tar $(BINDIR)/rump.cpio

default:			$(UTILS)

$(BINDIR)/rump.pax:		$(RUMPSRC)/bin/pax
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh pax $(RUMPSRC)/bin/pax $@ 

$(BINDIR)/rump.tar:		$(BINDIR)/rump.pax
				ln $(BINDIR)/rump.pax $@

$(BINDIR)/rump.cpio:		$(BINDIR)/rump.pax
				ln $(BINDIR)/rump.pax $@

$(BINDIR)/rump.mkdir:		$(RUMPSRC)/bin/mkdir
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh mkdir $(RUMPSRC)/bin/mkdir $@

$(BINDIR)/rump.ls:		$(RUMPSRC)/bin/ls
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh ls $(RUMPSRC)/bin/ls $@ 

$(BINDIR)/rump.rm:		$(RUMPSRC)/bin/rm
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh rm $(RUMPSRC)/bin/rm $@

$(BINDIR)/rump.ln:		$(RUMPSRC)/bin/ln
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh ln $(RUMPSRC)/bin/ln $@

$(BINDIR)/rump.dd:		$(RUMPSRC)/bin/dd
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh dd $(RUMPSRC)/bin/dd $@

$(BINDIR)/rump.df:		$(RUMPSRC)/bin/df
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh df $(RUMPSRC)/bin/df $@

$(BINDIR)/rump.rmdir:		$(RUMPSRC)/bin/rmdir
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh rmdir $(RUMPSRC)/bin/rmdir $@

$(BINDIR)/rump.chmod:		$(RUMPSRC)/bin/chmod
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh chmod $(RUMPSRC)/bin/chmod $@

$(BINDIR)/rump.mknod:		$(RUMPSRC)/sbin/mknod
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh mknod $(RUMPSRC)/sbin/mknod $@

$(BINDIR)/rump.mount:		$(RUMPSRC)/sbin/mount
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh mount $(RUMPSRC)/sbin/mount $@

$(BINDIR)/rump.chown:		$(RUMPSRC)/sbin/chown
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh chown $(RUMPSRC)/sbin/chown $@

$(BINDIR)/rump.ifconfig:	$(RUMPSRC)/sbin/ifconfig
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh ifconfig $(RUMPSRC)/sbin/ifconfig $@

$(BINDIR)/rump.route:		$(RUMPSRC)/sbin/route
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh route $(RUMPSRC)/sbin/route $@

$(BINDIR)/rump.newfs:		$(RUMPSRC)/sbin/newfs
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh newfs $(RUMPSRC)/sbin/newfs $@

$(BINDIR)/rump.fsck_ffs:	$(RUMPSRC)/sbin/fsck_ffs
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh fsck_ffs $(RUMPSRC)/sbin/fsck_ffs $@

$(BINDIR)/rump.ping:		$(RUMPSRC)/sbin/ping
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh ping $(RUMPSRC)/sbin/ping $@

$(BINDIR)/rump.ping6:		$(RUMPSRC)/sbin/ping6
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh ping6 $(RUMPSRC)/sbin/ping6 $@

$(BINDIR)/rump.rtadvd:		$(RUMPSRC)/usr.sbin/rtadvd
				RUMPMAKE=$(RUMPMAKE) CC=$(CC) OUTDIR=$(OUTDIR) RUMPSRC=$(RUMPSRC) OBJDIR=$(OBJDIR) ./util.sh rtadvd $(RUMPSRC)/usr.sbin/rtadvd $@

.PHONY:			clean 
clean:		
			rm -rf $(BINDIR)/rump.* $(OBJDIR)
