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
reference design is also provided, for the sake of being unambiguous.
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

Documentation
-------------

Documentation is the bread and butter of this project!  Good
documentation has historically been pretty closely correlated with the
success of any computing platform.  I have several blog articles
written up on this subject, and I will be editing and merging them
down into more of a Wiki or book format.  The documentation will be
included in this repository alongside with the code that implements
the usable Bootstrap Personal Computer.

Maintenance?
------------

Finally, an important point is long-term maintenance.  This is perhaps
what makes this lucky that I pulled this out of useful application
software of my own.  Because I plan on using the related software for
quite a while, hopefully this project of its own will have a longer
term maintenance cycle than the ones that came before it.  I love the
ideas behind C-- and Microsoft Research's "software MMU" programming
language runtime, but those projects ultimately failed in the long run
due to their substantiated backing in research funding and failure to
gain a foothold in useful application software.  This project has a
secure foothold in a small application product, is based off of
already well-established standards, and should therefore be
interchangable to also be functional lower level component of other
small applications too.  We're not trying to build a new standard, but
rather a hopefully more future-resistant small scale implementation of
widely adopted ones.

License
-------

License?  No license, public domain, that is the goal.  The UNLICENSE
fills in the required legalese for jurisdictions that don't recognize
the concept of a public domain.

Why public domain?
..................

Well, if you're looking for similar free, libre, open-source projects,
chances are you can find one under every other such license: GPLv2,
GPLv3, MIT, BSD, Apache, and so on.  If someone else wrote the same
code under every other license, why reinvent the wheel where it is not
necessary?  Yeah, I can assure you that most of this code was also
already written in the public domain too, so really it all comes down
to maximizing portability of a single, integrated, public domain
system.

Thanks
------

In addition to direct contributors, many people have had major
influences on the concepts and implementations in Quorten's BPC.  See
THANKS.md for a list.
