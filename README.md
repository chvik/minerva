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

<dl>
  <dt>sing.</dt>
  <dd>singularis, singular</dd>

  <dt>plur.</dt>
  <dd>pluralis, plural</dd>

  <dt>nom.</dt>
  <dd>nominativus, nominative</dd>

  <dt>acc.</dt>
  <dd>accusativus, accusative</dd>

  <dt>gen.</dt>
  <dd>genitivus, genitive</dd>

  <dt>dat.</dt>
  <dd>dativus, dative</dd>

  <dt>abl.</dt>
  <dd>ablativus, ablative</dd>

  <dt>m</dt>
  <dd>masculinum, masculine</dd>

  <dt>f</dt>
  <dd>femininum, feminine</dd>

  <dt>n</dt>
  <dd>neutrum, neuter</dd>

  <dt>comparat.</dt>
  <dd>comparativus, comparative</dd>

  <dt>superlat.</dt>
  <dd>superlativus, superlative</dd>

  <dt>act.</dt>
  <dd>activum, active</dd>

  <dt>pass.</dt>
  <dd>passivum, passive</dd>

  <dt>ind.</dt>
  <dd>indicativus, indicative</dd>

  <dt>con.</dt>
  <dd>coniunctivus, conjunctive mode</dd>

  <dt>imperat1</dt>
  <dd>imperativus I., the first imperative</dd>

  <dt>imperat2</dt>
  <dd>imperativus II., the second imperative</dd>

  <dt>praes.</dt>
  <dd>praesens, present</dd>

  <dt>praet.</dt>
  <dd>praeteritum, past</dd>

  <dt>fut.</dt>
  <dd>futurum, future</dd>

  <dt>imp.</dt>
  <dd>imperfecta, imperfect</dd>

  <dt>perf.</dt>
  <dd>perfecta, perfect</dd>

  <dt>inst.</dt>
  <dd>instans, instant (future)</dd>

  <dt>adverbium</dt>
  <dd>adverb</dd>

  <dt>part.</dt>
  <dd>participium, participle</dd>

  <dt>inf.</dt>
  <dd>infinitivus, infinitive</dd>

  <dt>gerundium</dt>
  <dd>gerund</dd>

  <dt>sup.</dt>
  <dd>supinum, supine</dd>
</dl>
        

## License

   Copyright 1999 Viktor Nagy

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0
