Quorten's Bootstrap Personal Computer (BPC)
===========================================

Welcome, and hello to newcomers.

Do you remember the days when you could press Control-Reset on a
computer and get brought right into a BASIC prompt?  No?  That's okay,
I didn't remember that either because I wasn't involved at the time.
However, even though I was never a member of the original 1980s 8-bit
home microcomputer community, I am indebted to their motivation to
make it very easy for newcomers to get started in and learn the
foreign world of the old art.  By all means, these early computer
systems have been a strong influencer in the design and implementation
of Quorten's BPC.

So, what is Quorten's BPC?  It is my version of a general-purpose
computer system that is small enough and simple enough to be built by
hand, ideally by only one person.  Once the bootstrap PC has been
built by hand, its goal is to be the shortest and fastest possible
path to build up more complicated hardware, software, and
telecommunications to reach the modern heavy-duty computing era.
Unlike many other modernizations of vintage computer projects, the
purpose of this project is **not** to be a replica copy of a historic
computer system.  Rather, it is meant to be a useful modern computer
platform in its own right, and therefore strives to be more
"culturally modern" when doing so does not compromise on
implementation simplicity.

Besides a useful implementation of low-level software, a hardware
reference design is also provided, for the sake of being disambiguous.
The following real-world (a.k.a. "historic") CPU architectures are
also either supported or planned to be supported.

* 6502 (current)
* Z80 (current)
* MC68000 (planned)
* MegaProcessor (planned)
* x86 (current)
* PowerPC (planned)
* Atmel AVR (planned)
* x86-64 (current)
* MIPS (current)
* ARM (current)
* RISC-V (planned)

As noted in previous discussion, in the meantime, I need to reorganize
the pertinent code.  Originally it was developed for application use,
but upon second look, I saw I could reorganize it to create a useful
general-purpose operating system and electronic hardware design
automation platform.
