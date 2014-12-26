# Latin-magyar szótár és morfológiai elemző

A szótár kb. 700 szócikket tartalmaz. A morfológiai elemző a
következő nyelvtani jelenségeket ismeri:

 * főnevek és melléknevek I-V. declinatiója;
 * III. declinatiós i-tövű névszók;
 * melléknevek szabályos fokozása, -er végű melléknevek és
  hat -ilis végű melléknév rendhagyó fokozása;
 * határozószók (adverbiumok) szabályos képzése;
 * igék I-IV. coniugatiója az igenévképzéssel együtt;
 * a létige és a fero coniugatiója;
 * álszenvedő (deponens) és félig álszenvedő (semi deponens) igék.

## Telepítés

```
make install
```

It will install minerva into /usr/local/minerva and a symlink to the executable into
/usr/local/bin.  If you want to install it elsewhere, run

```
make install MINERVA_ROOT=directory BINDIR=directory
```

## Használat

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

## Szakkifejezések és rövidítések

<dl>
  <dt>sing.</dt>
  <dd>singularis, egyes szám</dd>

  <dt>plur.</dt>
  <dd>pluralis, többes szám</dd>

  <dt>nom.</dt>
  <dd>nominativus, alany eset</dd>

  <dt>acc.</dt>
  <dd>accusativus, tárgy eset</dd>

  <dt>gen.</dt>
  <dd>genitivus, birtokos eset</dd>

  <dt>dat.</dt>
  <dd>dativus, részeshatározó eset</dd>

  <dt>abl.</dt>
  <dd>ablativus, általános határozó eset</dd>

  <dt>m</dt>
  <dd>masculinum, hímnem</dd>

  <dt>f</dt>
  <dd>femininum, nőnem</dd>

  <dt>n</dt>
  <dd>neutrum, semlegesnem</dd>

  <dt>comparat.</dt>
  <dd>comparativus, középfok</dd>

  <dt>superlat.</dt>
  <dd>superlativus, felsőfok</dd>

  <dt>act.</dt>
  <dd>activum, cselekvő igenem</dd>

  <dt>pass.</dt>
  <dd>passivum, szenvedő igenem</dd>

  <dt>ind.</dt>
  <dd>indicativus, kijelentő mód</dd>

  <dt>con.</dt>
  <dd>coniunctivus, kötőmód</dd>

  <dt>imperat1</dt>
  <dd>imperativus I., I. parancsoló mód</dd>

  <dt>imperat2</dt>
  <dd>imperativus II., II. parancsoló mód</dd>

  <dt>praes.</dt>
  <dd>praesens, jelen idő</dd>

  <dt>praet.</dt>
  <dd>praeteritum, múlt idő</dd>

  <dt>fut.</dt>
  <dd>futurum, jövő idő</dd>

  <dt>imp.</dt>
  <dd>imperfecta, folyamatos</dd>

  <dt>perf.</dt>
  <dd>perfecta, befejezett</dd>

  <dt>inst.</dt>
  <dd>instans, beálló</dd>

  <dt>adverbium</dt>
  <dd>határozószó</dd>

  <dt>part.</dt>
  <dd>participium, melléknévi igenév</dd>

  <dt>inf.</dt>
  <dd>infinitivus, főnévi igenév</dd>

  <dt>gerundium</dt>

  <dt>sup.</dt>
  <dd>supinum</dd>
</dl>
