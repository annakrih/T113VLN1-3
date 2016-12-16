Verklegt námskeið 1, 2016-3 - Hópur 8:
    Anna Kristín Halldórsdóttir
    Björn Þórsson
    Friðrik Snær Tómasson
    Ísak Grétarson
    Margrét Finnbogadóttir
    Sólveig Sara Samúelsdóttir

Til að keyra forritið þarf að byrja að niðurhala forritunarkerfinu Qt, það er hægt að sækja hér: https://www.qt.io/download-open-source/

Þegar Qt er komið í tölvuna, er hægt að opna verkefnið með því að velja „open project” og velja T113VLN1-3.pro skránna. Þá er hægt að smíða (e. build) forritið og svo keyra það. 

Verkefnið sýnir þá default database sem fylgir með. Þar eru upplýsingar um ýmsa einstaklinga sem hafa verið mikilvægir í sögu tölvu og forrita og svo upplýsingar um frægar tölvur. 

Til að láta forritið lesa úr gagnagrunni skal notandi vera viss um að mappan sem heldur utan um forritsskrárnar hafi nafnið „T113VLN-3” eða setja „shadow build” stillingu á, en það er hægt að gera í project flipanum til vinstri á Qt forritinu. 

Hægt er að skrá og breyta báðum listunum með virknunum:
	add person / add computer
	edit person / edit computer
	delete	- hægt að velja fleiri en einn úr lista til að eyða mörgum í einu.
	delete all: persons/computers/relations

Þegar valin er persóna eða talva birtist til hægri nánari upplýsingar, og mynd ef til er af persónu, og svo þær persónur eða tölvur sem tengjast valdri persónu eða tölvu. 

Hægt er að leita aðeins eftir nafni, eða velja „advanced search” sem sýnir fleiri leitarmöguleika. Þá er hægt að leita eftir persónum eftir:
	kyni 
	dánarári og fæðingarári:
		Hægt að fylla í bara „from” eða „to” og sýnir hann þá öll ár frá 
		eða að því ári, að árinu sjálfu meðtöldu. 
	upprunalandi
og hægt að leita eftir tölvu eftir:
	týpu tölvunnar
	hönnunarári og byggingarári tölvunnar:
		Hægt að fylla í bara „from” eða „to” og sýnir hann þá öll ár frá 
		eða að því ári, að árinu sjálfu meðtöldu.
*Advanced search hreinsast ef því er lokað

Hægt er að vista breytingar í gagnagrunninn með því að velja „file” í menu-bar og þar „Save Changes”, en einnig er notandi spurður hvort hann vilji vista breytingar ef einhverjar óvistaðar breytingar eru þegar notandi ætlar að loka forritinu.

Ef notandi hefur gert breytingar getur hann einnig valið „revert all changes” með því að ýta á takka í toolbar. Þá eru kallaðar aftur allar óvistaðar breytingar.  

Þar að auki er hægt að ná í „default gagnagrunn” sem fylgir með forritinu, og eyðir það þá öllum öðrum gögnum í gagnagrunninnum sem notandi kann að hafa sett þar. Þetta er gert með því að velja „File” í menu bar og velja þar „Reset to default database”

Helsta bónusvirkni í forritinu er:
1. Default mynd í add person.
2. Revert takki
3. Mynd fyrir persónu
4. Myndir fyrir persónur geymdar í gagnagrunni
5. Advanced search, þar sem er hægt að leita eftir mörgum parametrum í einu
6. Endursetning gagnagrunns (Reset to default database)
7. Tooltip fyrir takka sem hafa icon.
8. Multi select í tölfum:
	annars vegar hægt að draga yfir nokkrar raðir, en einnig hægt að halda inni 
	ctrl á PC og cmd á Mac til að velja raðir sem liggja ekki saman. 
9. Hægt er að bæta við mörgum relatiom með því að nota multi select í add relation glugga. 
10. Right click
11. Lönd sýnd í drop down menu með lista yfir allflest lönd. 
12. Hægt að eyða hverri töflu fyrir sig (Delete all virkni) (vensl eyðast einnig ef öllum persónum eða öllum tölvum er eytt. 
13. Multi delete: Hægt að eyða mörgum í einu með því að nota multi select og velja svo delete.

