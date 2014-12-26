minerva
=======

[Magyar leírás](README.hu.md)

Latin-Hungarian dictionary and morphological analyser. The lexicon contains about 700 entries.
This was my BSc thesis project in 1999.

The analyser recognizes the following grammatical phenomena:

 * declension of nouns and adjectives from first to fifth,
 * regular comparison of adjectives, irregular comparison of -er and -ilis adjectives,
 * regular derivation of adverbs,
 * conjugation from first to fourth with participles,
 * conjugation of _sum_ and _fero_,
 * deponens and semideponens verbs.


## Installation

```
make install
```

It will install minerva into /usr/local/minerva and a symlink to the executable into
/usr/local/bin.  If you want to install it elsewhere, run

`make install MINERVA_ROOT=`_directory_ `BINDIR=`_directory_

## Usage

```
$ minerva
? Minervae
Minerva, -ae f : Minerva
  sing. gen.
  sing. dat.
  plur. nom.
? narrare
narro 1, narravi, narratum : mesél, elbeszél
  pass. imperat1 sing. 2
  inf. imp. act.
? ember
vir, -i m férfi, hõs; ember, férj
homo, hominis m ember
? <ENTER>
$ 
```

## Terms and abbreviations

 * sing.
        singularis, singular

 * plur.
        pluralis, plural

 * nom.
        nominativus, nominative

 * acc.
        accusativus, accusative

 * gen.
        genitivus, genitive

 * dat.
        dativus, dative

 * abl.
        ablativus, ablative

 * m
        masculinum, masculine

 * f
        femininum, feminine

 * n
        neutrum, neuter

 * comparat.
        comparativus, comparative

 * superlat.
        superlativus, superlative

 * act.
        activum, active

 * pass.
        passivum, passive

 * ind.
        indicativus, indicative

 * con.
        coniunctivus, conjunctive mode

 * imperat1
        imperativus I., the first imperative

 * imperat2
        imperativus II., the second imperative

 * praes.
        praesens, present

 * praet.
        praeteritum, past

 * fut.
        futurum, future

 * imp.
        imperfecta, imperfect

 * perf.
        perfecta, perfect

 * inst.
        instans, instant (future)

 * adverbium
        adverb

 * part.
        participium, participle

 * inf.
        infinitivus, infinitive

 * gerundium
        gerund

 * sup.
        supinum, supine
        

## License

   Copyright 1999 Viktor Nagy

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0
