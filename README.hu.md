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

```make install
```

It will install minerva into /usr/local/minerva and a symlink to the executable into
/usr/local/bin.  If you want to install it elsewhere, run

```make install MINERVA_ROOT=```_directory_ ```BINDIR=```_directory_

## Használat

```$ minerva
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
? ```_<ENTER>_
```$ ```

## Szakkifejezések és rövidítések

 * sing.
        singularis, egyes szám

 * plur.
        pluralis, többes szám

 * nom.
        nominativus, alany eset

 * acc.
        accusativus, tárgy eset

 * gen.
        genitivus, birtokos eset

 * dat.
        dativus, részeshatározó eset

 * abl.
        ablativus, általános határozó eset

 * m        masculinum, hímnem

 * f
        femininum, nőnem

 * n
        neutrum, semlegesnem

 * comparat.
        comparativus, középfok

 * superlat.
        superlativus, felsőfok

 * act.
        activum, cselekvő igenem

 * pass.
        passivum, szenvedő igenem

 * ind.
        indicativus, kijelentő mód

 * con.        coniunctivus, kötőmód

 * imperat1
        imperativus I., I. parancsoló mód

 * imperat2
        imperativus II., II. parancsoló mód

 * praes.
        praesens, jelen idő

 * praet.
        praeteritum, múlt idő

 * fut.
        futurum, jövő idő

 * imp.
        imperfecta, folyamatos

 * perf.
        perfecta, befejezett

 * inst.        instans, beálló

 * adverbium
        határozószó

 * part.
        participium, melléknévi igenév

 * inf.
        infinitivus, főnévi igenév

 * gerundium

 * sup.
        supinum
