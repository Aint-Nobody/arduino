// =====================================================================
// wifi_monitor.ino
// Version: 2.30.81      Generiert: 2026-10-05 (BUGFIX/ERWEITERUNG: Hintergrundverkehrsstatistik, Dateikopf-/Versionskennzeichnung, sichere Navigation und Speicherschutz. Die Anzeige 'Geraete gelistet' verwendet jetzt die tatsaechlich in der Statistik-Tabelle gefuehrte Client-Anzahl statt clients_known_count. Die beiden Menue-3a-Hinweise fuer TimeWatch und Hintergrundverkehr wurden auf die gewuenschte Einrueckung zurueckgesetzt. Erzeugte textbasierte Nutzdateien erhalten im Header neben einem Erzeugungs-Zeitstempel die Programmversion; dies gilt auch fuer direkt fuer ntfy erzeugte Anhaenge. ESC aus der Detailverkehrsansicht beendet die uebergeordnete Hintergrundverkehrsaufzeichnung nicht mehr. Menue 6 wartet nach der Dateianzeige auf einen beliebigen Tastendruck, bevor die Dateiliste neu gezeichnet wird. Die Dateischutz-Texte verwenden jetzt 'Geschuetzte Dateien' einschliesslich des gewuenschten fuehrenden Leerzeichens im Ausblendhinweis. Der aktive b-Menuepunkt steht im Hauptmenue oberhalb der Registrierungszahlen. Offene SSIDs in Menue 3 werden mit einer 0 anstelle der rechten runden Klammer abgeschlossen. Ein neuer Start einer laufenden Hintergrundverkehrsaufzeichnung verlangt eine Bestaetigung. Bei einem bestaetigten Akku-Unterspannungsalarm wird eine aktive Hintergrundverkehrsaufzeichnung zusaetzlich als eigene Datei gesichert.
// -----------------------------------------------------------------------
// Version: 2.30.78      Generiert: 2026-10-04 (Menue 6: Jahresdarstellung im Zeitstempel korrekt als 20x6 statt 2026.)
// -----------------------------------------------------------------------
// Version: 2.30.77      Generiert: 2026-10-04 (Korrektur der dekodierten Jahreszahl im Menue 6: 2026 statt 206; Changelog der letzten Versionen im Header ergaenzt).
// -----------------------------------------------------------------------
// Version: 2.30.76      Generiert: 2026-10-04 (Statistik-Datei mit Bildschirm-Kopfblock;
//                        Menue 6: Dateiname ohne .txt, Byte-Ausrichtung und
//                        Zeitstempel-Zweitzeile).
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// Version: 2.30.75      Generiert: 2026-10-04 (Dateiversand per ntfy aus Menue 6;
//                        YMDHms-Zeitstempel-/Kollisionshelfer; Paketanzahl-
//                        Kurzformat NkNNN in der Hintergrundverkehr-Statistik).
// -----------------------------------------------------------------------
// Version: 2.30.74      Generiert: 2026-10-04 (Hintergrundverkehr laeuft
//                        nach Verlassen der Ansicht weiter; Kanal-Lock wird
//                        beim Verlassen freigegeben und bei Rueckkehr mit b
//                        erneut gesetzt. Taste e beendet die Aufzeichnung;
//                        Statusanzeige im Hauptmenue und anderen Ansichten.)
// -----------------------------------------------------------------------
// Version: 2.30.73      Generiert: 2026-10-03 (Detailverkehr: Datenzeilen exakt an Tabellenkopf ausgerichtet; gleiche Formatierung fuer Konsole und Datei.
//                        Keine Aenderung an Erfassung, Speicherung oder Netzwerklogik.)
// -----------------------------------------------------------------------
// Version: 2.30.69      Generiert: 2026-10-03 (NEU: TX/RX-Trennung der Hintergrundverkehr-Statistik, kompakte/erweiterte Ansicht und vollstaendige Datei-Ausgabe. Bestehende Erweiterungen unveraendert. 
// -----------------------------------------------------------------------
// Version: 2.30.67      Generiert: 2026-10-02 (NEU: Bulk-Cleanup fuer alte
//                        0/0-APs und TimeWatch fuer ausgewaehlte MAC-Adressen.
//                        Cleanup-Taste 'o' loescht im Cleanup-Menue alle APs
//                        mit Age > 99999 s und Geraetezaehler 0/0. TimeWatch
//                        wird ueber 'tw'+Index+Enter in Menue 3 bzw. 'wt'+Index+Enter
//                        in Menue 3a eingerichtet, fragt eine Beschreibung ab
//                        und markiert den Watchlist-Eintrag mit ' (TW)'. Nach
//                        mehr als 3600 s Abwesenheit wird beim Wiederauftauchen
//                        ein Zeitstempel in einer MAC-spezifischen TW-Datei
//                        protokolliert; zwischen zwei Protokollierungen liegen
//                        mindestens 60 s. TimeWatch laeuft unabhaengig von der
//                        Rueckkehr-Signalisierung. Die Bedienhinweise wurden
//                        in die jeweiligen Menueheader aufgenommen: Menue 3
//                        zeigt "tw+Zahl+Enter = TimeWatch", Menue 3a zeigt
//                        "wt+Zahl+Enter = TimeWatch". Die TimeWatch-Zustandsdaten
//                        werden beim Factory-Reset und beim Laden eines
//                        Szenarios zurueckgesetzt. Alle neuen globalen
//                        Deklarationen und Funktionsprototypen stehen vor den
//                        jeweiligen Verwendungen, um Arduino-Auto-Prototyping
//                        und Reihenfolgefehler zu vermeiden.
// -----------------------------------------------------------------------
// Version: 2.30.66      Generiert: 2026-10-01 (ERWEITERUNG: Hintergrundverkehr-
//                        Statistik und Detailstatistik. Neue Startzeit-/Laufzeit-
//                        Anzeige mit NTP-Zeit bzw. Boot-Uptime, Tausenderpunkt-
//                        Notation fuer Statistikwerte und kompaktere Spalten-
//                        aufteilung der Detailanzeige. Mit Taste 's' koennen
//                        Hintergrundverkehr-Statistiken als TR_<SSID>.txt und
//                        Detailstatistiken als TR_<MAC>.txt in LittleFS
//                        gespeichert werden. Die Tabellenausgabe wurde dafuer
//                        in gemeinsame Print&-Funktionen ausgelagert. Kein
//                        automatisches Speichern und keine Kompression der
//                        Statistikdateien; Speichern nur bei ausreichendem
//                        Heap. Zusaetzlich wird waehrend einer aktiven
//                        Statistik-Sitzung der Kanal-Scan auf die relevanten
//                        AP-Kanaele begrenzt und beim Verlassen automatisch
//                        auf den vorherigen Kanalfilter zurueckgesetzt.
//                        Die Detailansicht verwendet den bestehenden Lock der
//                        uebergeordneten Statistik und setzt keinen eigenen.
// -----------------------------------------------------------------------
// Version: 2.30.65      Generiert: 2026-09-30 (Vereinheitlichung der
//                        Dateinamen-Schemata, nach Entwicklerdokumentation).
//                        Neue Hilfsfunktion format_uptime_ddhhmmss()
//                        (Laufzeit als 8-stelliger Code ddhhmmss) ersetzt den
//                        rohen millis()-Wert in allen Ohne-NTP-Dateinamen.
//                        GPIO0-, ADC- und Ueberlauf-Auto-Save: "offline_<ms>"
//                        -> "NoNtp_<ddhhmmss>". Zyklischer Auto-Save ohne NTP:
//                        nur Zahlenformat -> "autosave_<Cl>_<AP>_<ddhhmmss>"
//                        (kein "NoNtp_"). Auto-Save mit NTP: Datum jetzt
//                        6-stellig (autosave_YYMMDD_HHMMSS). ntfy-Anhang:
//                        modusabhaengiges Schema "<Zeitstempel|ddhhmmss>_
//                        <Name>[_ssid|_Xssid|_APs].txt" (Modus 0 ohne Suffix,
//                        ohne NTP kein "NoNtp_"-Tag). notif_filename-Puffer
//                        in notif_send_now() von 56 auf 60 Byte. Dateiinhalt,
//                        Ladepfad und Kompression unveraendert.
// -----------------------------------------------------------------------
// Version: 2.30.64      Generiert: 2026-09-29 (Korrektur/Ergaenzung zu
//                        2.30.63, nach Rueckmeldung). 1) Der "Von: ... |
//                        Zeitstempel: ..."-Header samt "="-Trennzeile wird
//                        in build_notif_attachment() wieder fuer ALLE Modi
//                        geschrieben, auch Modus 0 (die Einschraenkung auf
//                        die Modi 1/2/3 aus 2.30.63 ist damit zurueck-
//                        genommen). Das war unnoetig vorsichtig: load_
//                        scenario_file() liest ausschliesslich nach
//                        Zeilenpraefix ("DEVICE: "/"BEACON: "/"# SETTINGS"/
//                        "key=val") und ueberspringt jede andere Zeile
//                        folgenlos - der Header steht dem erneuten Laden
//                        ueber Menue 6 "l+Zahl" also nicht im Weg. 2)
//                        build_notif_filename() liefert jetzt statt
//                        "[Name]_[Typ].txt" das Schema
//                        "[Zeitstempel]_[Name].txt" (Beispiel:
//                        "260929_133114_Testschwein.txt", YYMMDD_HHMMSS),
//                        der bisherige Listentyp-Suffix (Liste/SSID/SSIDs/
//                        APs) entfaellt dabei fuer alle Modi. Ohne NTP-Sync
//                        wird "000000_000000_" als Platzhalter-Praefix
//                        verwendet, damit das Dateinamensschema einheitlich
//                        bleibt. Der Zielpuffer fuer den Dateinamen in
//                        notif_send_now() wurde dafuer von 48 auf 56 Byte
//                        vergroessert (der laengere Zeitstempel-Praefix
//                        passt bei einem voll ausgeschoepften 32-Zeichen-
//                        Namen sonst nicht mehr hinein). write_scenario_
//                        plaintext() und der uebrige Refactoring-Teil aus
//                        2.30.63 unveraendert.
// -----------------------------------------------------------------------
// Version: 2.30.63      Generiert: 2026-09-29 (ntfy-Anhang Modus 0 "ganze
//                        Liste" liefert jetzt dasselbe Format wie eine
//                        reguläre Sicherung, nach eigener Entwickler-
//                        Dokumentation umgesetzt). Neue Hilfsfunktion
//                        write_scenario_plaintext(File&, uint64_t) buendelt
//                        den bisher doppelt vorhandenen Schreibcode aus dem
//                        unkomprimierten Zweig von save_current_lists() -
//                        wird jetzt sowohl dort (Zieldatei im Flash) als
//                        auch von build_notif_attachment() (ntfy-Anhang,
//                        Modus 0) aufgerufen. save_current_lists() ruft die
//                        Funktion innerhalb des bestehenden RETURN_SAVE-
//                        Guards (2.30.62) auf - die Sniffing-Wiederaufnahme
//                        bleibt dadurch unangetastet garantiert. In
//                        build_notif_attachment() wird der "Von:"-/
//                        Zeitstempel-Header jetzt nur noch fuer die Anzeige-
//                        Modi 1/2/3 geschrieben (in if(notif_content_mode!=0)
//                        eingefasst); Modus 0 verzichtet bewusst darauf,
//                        damit die Datei Zeichen fuer Zeichen einer
//                        regulaeren Sicherung entspricht und ueber Menue 6
//                        "l+Zahl" wieder als Arbeitsliste ladbar ist. Der
//                        bisherige Modus-0-Zweig (2000-Byte-malloc() fuer
//                        die Client-Sortierung vor dem Versand) entfaellt
//                        komplett - die Sortierung steht bereits im
//                        # SETTINGS-Block und wird beim Laden angewendet,
//                        das RAM ist beim ntfy-Versand also 2000 Byte
//                        entlastet. Kompressionszweig, Modi 1/2/3 und
//                        load_scenario_file() unveraendert.
// -----------------------------------------------------------------------
// Version: 2.30.62      Generiert: 2026-09-28 (Kompressionsfenster wieder
//                        auf 2048 angehoben + Hash-Suche + Live-RAM-Check +
//                        Sniffing-Pause waehrend des Speicherns; nach
//                        Absprache aus dem Kompressions-Test entstanden).
//                        1) Neue Hash-gestuetzte Match-Suche fuer den
//                        Encoder (scenario_find_match_hash(),
//                        scenario_hash_insert()): 512 Buckets a 2 Kandidaten
//                        (2048 Byte) statt linearem Scan durch das ganze
//                        Fenster - macht das inzwischen wieder auf 2048
//                        angehobene SCENARIO_LZSS_WINDOW (siehe Historie
//                        dort, war zwischenzeitlich auf 512 reduziert)
//                        vergleichbar schnell wie zuvor 512 linear, bei
//                        besserer Kompressionsrate. Bytestrom-Format
//                        unveraendert (Distanzfeld war immer 11 Bit breit).
//                        2) save_current_lists() prueft vor der Allokation
//                        per ESP.getMaxFreeBlockSize() live, ob Fenster+Hash
//                        (4096 Byte) inkl. Reserve fuer den WLAN-Stack
//                        (3072 Byte) in einen zusammenhaengenden Block
//                        passen; wenn nicht, faellt der Encoder auf reinen
//                        Fensterspeicher (2048 Byte) mit der alten linearen
//                        Suche zurueck (e.hash==NULL) - selbes Dateiformat,
//                        nur langsamer. Debug-Zeile zeigt jetzt zusaetzlich
//                        Hash an/aus und den vorab gemessenen freien Block.
//                        3) save_current_lists() pausiert fuer die gesamte
//                        Dauer (Klartext wie komprimiert) das Sniffing
//                        (go_offline()/go_online(), nur falls zuvor online) -
//                        laeuft dadurch unterbrechungsfrei, ohne dass
//                        register_client()/register_beacon() nebenlaeufig
//                        an denselben Listen aendern; go_online()
//                        kompensiert last_heard automatisch um die
//                        Pausendauer (bestehender Mechanismus, kein neuer
//                        Code), kein sichtbarer Age-Sprung.
//                        Decoder (Laden/Anzeigen) unveraendert - er kam
//                        schon vorher ohne Hash aus und braucht nur das
//                        (jetzt wieder 2048 Byte grosse) Fenster.
// -----------------------------------------------------------------------
// Version: 2.30.61      Generiert: 2026-09-28 (BUGFIX: Versorgungsbereich-
//                        Erkennung zeigte nach AP-Slot-Wiederverwendung
//                        falsche/wirre Gruppen an. Ursache: roaming_pairs[]
//                        speichert AP-INDIZES, nicht BSSIDs. Sobald ein Index
//                        einem anderen AP zugewiesen wurde - automatisch bei
//                        AP-Ueberlauf ohne freien 0/0-Kandidaten-Slot
//                        (ap_slot_mark_free() in der Ueberlauf-Behandlung),
//                        beim Cleanup-Menue (delete_old_aps(),
//                        delete_ap_by_index()) oder beim kompletten Leeren
//                        der Arbeitsliste (Auto-Save-Ueberlauf-Reset,
//                        load_scenario_file()) - blieben alte Roaming-Paare
//                        mit diesem Index bestehen und wurden dem NEUEN AP an
//                        derselben Stelle faelschlich zugeordnet. Fix: neue
//                        Funktion roaming_purge_ap() entfernt beim Freigeben
//                        eines einzelnen Slots (ap_slot_mark_free()) alle
//                        Paare mit diesem Index; die beiden Vollstaendig-
//                        Reset-Stellen setzen roaming_pair_count zusaetzlich
//                        direkt auf 0. Betroffen waren alle drei Aufrufer von
//                        ap_slot_mark_free() sowie beide direkten
//                        aps_known_count=0-Stellen.
// -----------------------------------------------------------------------
// Version: 2.30.60      Generiert: 2026-09-28 (NEUES FEATURE: Hauptmenue-Punkt
//                        v - Versorgungsbereiche (Roaming-Gruppen). Gruppiert
//                        Access Points, die denselben Funkbereich abdecken,
//                        anhand beobachteter Client-Roamings (gleiche Client-
//                        MAC an verschiedenen APs). Ereignisbasiert: der Hook
//                        in register_client() (Zweig "gleiche MAC, anderer
//                        ap_idx") ruft roaming_record() auf, das das AP-Paar
//                        in einer festen 64er-Paarliste (dedupliziert, 129
//                        Byte) ablegt. Der Menuepunkt fasst die Paare per
//                        Union-Find (200 Byte) zu Gruppen zusammen und gibt nur
//                        Gruppen mit mindestens 2 APs aus. Neuer MenuState
//                        STATE_ROAMING_GROUPS = 46. Angepasst wurden: enum,
//                        menu_draw(), menu_handle_serial() (Taste v im
//                        Hauptmenue), menu_go_back(), refresh_current_screen(),
//                        menu_enter_help(). Ansonsten keine Aenderung an
//                        bestehenden Pfaden. Bekannte Grenze: nach manuellem
//                        Loeschen von APs (Menue m / Menue 3 + d) koennen alte
//                        Paare auf einen wiederverwendeten Slot zeigen - dann
//                        ESP neu starten.
// -----------------------------------------------------------------------
// Version: 2.30.59      Generiert: 2026-09-27 (Age-Touch fuer assoziierte
//                        Clients, promisc_cb(): Ruhezustands-Frames
//                        (Null Data, QoS Null, PS-Poll/RTS etc.) fielen
//                        bisher durch den if (len < 48) return;-Filter in
//                        parse_data() und aktualisierten last_heard nicht -
//                        Age-Werte stationaerer Clients stiegen deshalb
//                        monoton an, sobald kein aktives Geraet (Smartphone)
//                        mehr Discovery-Verkehr anregte, obwohl die Clients
//                        weiterhin ununterbrochen Keep-Alive-Frames sendeten.
//                        Neuer 9-zeiliger Vorab-Lookup direkt in promisc_cb()
//                        (nach dem CallChainGuard, vor dem len==12-Zweig):
//                        prueft bei jedem Frame mit len>=28 (Mindestlaenge
//                        fuer ein lesbares Addr2/TA-Feld) per memcmp, ob
//                        Addr2 (buf+22) einer bereits bekannten Client-MAC
//                        in clients_known[] entspricht, und aktualisiert
//                        nur deren last_heard - unabhaengig von Frametyp/
//                        -subtyp. Kein neuer Eintrag moeglich (reiner
//                        Lookup gegen bestehende Eintraege), AP- und
//                        Fremdgeraete-Frames loesen daher nichts aus.
//                        parse_data()/register_client() und der 48-Byte-
//                        Filter dort bleiben unveraendert - der Touch-Pfad
//                        umgeht diesen Filter nur fuer die Age-Aktualisierung,
//                        nicht fuer die Client-Neuregistrierung.
// -----------------------------------------------------------------------
// Version: 2.30.58      Generiert: 2026-09-26 (AENDERUNGSAUFTRAG Hintergrund-
//                        verkehr-Statistik, Menue 3 / Multi-AP-Variante,
//                        Taste b: Statistikschluessel von clients_known[]-
//                        Index auf die physische MAC-Adresse umgestellt.
//                        Vorher legte register_client() pro AP, an dem ein
//                        roamender Client gesehen wurde, einen eigenen
//                        clients_known[]-Eintrag an - dieselbe MAC belegte
//                        dadurch bei einem Geraet, das zwischen APs
//                        wechselt, bis zu einen Statistik-Slot pro AP
//                        (Dubletten in der Anzeige, Pufferueberlauf schon
//                        bei rechnerisch ~16 physischen Geraeten). Jetzt:
//                        struct traffic_client_stat traegt mac[6] als Sortier-/
//                        Suchschluessel (memcmp) statt client_idx, plus
//                        last_client_idx (nur fuer Anzeige/Taste 'd', wird bei
//                        jedem traffic_stats_record()-Aufruf aktualisiert) -
//                        10 auf 16 Byte pro Eintrag gewachsen. Puffergroesse
//                        TRAFFIC_STATS_MAX_CLIENTS von 64 auf 128 erhoeht
//                        (Speicherzuwachs nur waehrend aktiver Statistik:
//                        640 auf 2048 Byte). traffic_stats_find_client()
//                        und traffic_stats_record() bekommen dafuer einen
//                        mac-Parameter statt/zusaetzlich zu client_idx; der
//                        Last-Hit-Cache (traffic_stats_last_client_idx) wurde
//                        durch traffic_stats_last_mac[6]/-_valid ersetzt. Die
//                        Verlustzaehler-Meldung war zudem irrefuehrend
//                        beschriftet ("neue Clients nicht aufgenommen"),
//                        zaehlte aber tatsaechlich einzelne verworfene Frames
//                        - Text auf "Frames von nicht erfassten MACs"
//                        korrigiert. Kein Einfluss auf Modus 1 (Einzel-AP,
//                        dort kann eine MAC durch Roaming ohnehin nicht
//                        mehrfach auftreten), auf traffic_ap_stat, oder auf
//                        die Detailstatistik (Taste d), die weiterhin einen
//                        gueltigen clients_known[]-Index erwartet (jetzt eben
//                        den zuletzt bekannten der jeweiligen MAC-Zeile).
// -----------------------------------------------------------------------
// Version: 2.30.57      Generiert: 2026-09-26 (KOMPILIERUNGSFIX zu v2.30.56:
//                        "duplicate 'const'" bei allen vier PGM_P-Stellen aus
//                        Block 2.1 (FSN_MGMT/FSN_CTRL/FSN_DATA-Tabellendekl.
//                        sowie "table"-Zeigervariable in ie_frame_subtype_
//                        name()). Ursache: PGM_P ist auf diesem ESP8266-Core
//                        (3.1.2) ein Macro fuer "const char *", nicht ein
//                        typedef - "const PGM_P" expandiert dadurch woertlich
//                        zu "const const char *", was der Compiler direkt
//                        geschrieben (anders als ueber ein typedef) als
//                        doppeltes const ablehnt. Bereits vorhandener Code
//                        (RAM_DEBUG_POINT_NAMES) umging genau dieses Problem,
//                        indem er von Anfang an "const char* const" statt
//                        PGM_P schrieb - diesem etablierten Stil jetzt auch
//                        fuer die vier betroffenen Stellen gefolgt. Reiner
//                        Kompilierungsfix, keine Verhaltensaenderung.
// -----------------------------------------------------------------------
// Version: 2.30.56      Generiert: 2026-09-26 (FLASH-/RAM-BEREINIGUNG nach
//                        externem Umbauauftrag, wegen "dangerous relocation:
//                        j: cannot encode"-Linkerfehler auf ESP8266-Arduino-
//                        Core 3.1.2: Block 1 - kompletter Debug-Pfad entfernt
//                        (PRINT_RAW_HEADER, debug-Variable, g_debugFlag/
//                        debugLog()/debugLogImpl(), toggle_debug_mode(),
//                        print_pkt_header(), Strg+D-Handler, alle drei
//                        case STATE_DEBUG_LIVE:-Bloecke; Enum-Eintrag bewusst
//                        als reserviert stehengelassen, um die nachfolgenden
//                        State-Nummern nicht zu verschieben). Block 2.1 -
//                        ie_frame_subtype_name() (48 Eintraege) von drei
//                        switch-Bloecken auf PROGMEM-Tabellen (FSN_MGMT/
//                        FSN_CTRL/FSN_DATA) umgestellt, Ausgabetexte 1:1
//                        identisch. ie_element_name()/rsn_cipher_suite_name()/
//                        rsn_akm_suite_name()/action_category_name()/
//                        action_specific_name() bewusst NICHT umgestellt
//                        (laut Auftrag zu geringer Nutzen fuer das Risiko).
//                        Block 3 - saemtliche verbleibenden Serial.printf()/
//                        snprintf()/sprintf() mit Literal-Formatstring auf
//                        die _P-Varianten (PSTR()) umgestellt, bedingte
//                        Formatstrings (BEACON/DEVICE-Klammern, print_ap_cell)
//                        dafuer in je zwei Zweige aufgeteilt. Block 4 -
//                        Rueckgabe-Literale auf PROGMEM/F() umgestellt:
//                        VendorLookup::getManufacturer()/getVendorByLineNumber()/
//                        binarySearchMacFile()/readVendorLineAtOffset()/
//                        vendorCache_lookup_or_search() (F("---")),
//                        notif_mode_name()/http_content_type_for()/
//                        sort_field_name()/ap_sort_field_name() (PROGMEM-
//                        Tabelle + statischer Puffer). Keine Verhaltens-
//                        aenderung, keine Aenderung an Dateiformaten/
//                        Kompressionslogik. NICHT kompiliert (kein Arduino-
//                        Toolchain in dieser Umgebung verfuegbar) - vor dem
//                        Flashen unbedingt selbst kompilieren und testen.
// -----------------------------------------------------------------------
// Version: 2.30.55      Generiert: 2026-09-25 (Nutzerentscheidung nach dem
//                        2.30.54-Testbuild: Fenster 512 wird dauerhaft
//                        beibehalten (guter Kompromiss aus Geschwindigkeit
//                        und Groesse, siehe Analyse unten) - Kommentar von
//                        "nur Test" auf "endgueltig" umgestellt, sonst keine
//                        Aenderung an der Fenstergroesse selbst. Zusaetzlich
//                        SCENARIO_LZSS_MAX_MATCH von 18 auf 34 erhoeht
//                        (Nutzeraenderung, hier uebernommen): 34 ist exakt
//                        der groesstmoegliche Wert, den das bestehende 5-Bit-
//                        Laengenfeld im Match-Token hergibt (Bits 11-15 =
//                        Laenge-MIN_MATCH, 0..31 -> 3+31=34) - keine
//                        Formataenderung, keine Kompatibilitaetsauswirkung,
//                        nutzt lediglich bisher ungenutzten Spielraum im
//                        bereits vorhandenen Bit-Layout. Format-Dokumentation
//                        (Kommentar "0..15") entsprechend auf "0..31"
//                        korrigiert. Bringt laut Nutzertest bei einer 45-KB-
//                        Datei zusaetzlich ca. 700 Byte Einsparung.
// -----------------------------------------------------------------------
// Version: 2.30.54-TEST Generiert: 2026-09-25 (NUR DIAGNOSE-TESTBUILD,
//                        NICHT fuer den Dauerbetrieb: SCENARIO_LZSS_WINDOW
//                        versuchsweise von 2048 auf 512 reduziert, um zu
//                        pruefen, ob/wie stark die lineare Fenstersuche in
//                        scenario_find_match() fuer die ca. 8s-Kompressions-
//                        zeit verantwortlich ist (siehe v2.30.53-Analyse
//                        unten: RLE schnell+nuetzlich, LZSS-Suche vermutet
//                        als Flaschenhals). Achtung: mit diesem Testbuild
//                        gespeicherte CSZ1-Dateien sind NICHT kompatibel zu
//                        vorher mit Fenster 2048 gespeicherten Dateien (die
//                        Fenstergroesse steht nicht im Dateiheader, Encoder
//                        und Decoder nutzen dieselbe Compile-Konstante) -
//                        deshalb mit diesem Build keine alten komprimierten
//                        Dateien laden, nur neu speichern und die
//                        Debug-Zeile auswerten. Nach dem Test wieder auf
//                        2048 zuruecksetzen (Versionsnummer entsprechend
//                        zurueckdrehen). Sonst keine Code-Aenderung.
// -----------------------------------------------------------------------
// Version: 2.30.53      Generiert: 2026-09-25 (KOMPRESSIONS-DEBUG, testweise,
//                        auf Nutzerwunsch, KEIN vorhandener Code entfernt/
//                        deaktiviert: zwei schlanke globale Zaehler
//                        (g_scenario_dbg_raw_bytes/g_scenario_dbg_rle_bytes)
//                        zaehlen Rohbytes vor RLE bzw. tatsaechlich an die
//                        LZSS-Stufe uebergebene Bytes nach RLE. In
//                        save_current_lists() wird zusaetzlich die
//                        Kompressionszeit per millis() gemessen und nach
//                        jedem komprimierten Speichern eine Debug-Zeile
//                        ausgegeben: Original-, Nach-RLE- und Nach-LZSS-
//                        Groesse (jeweils in Byte und Prozent) sowie Zeit
//                        in ms. Ziel: klaeren, ob RLE oder LZSS die
//                        magere Kompressionsrate (40 KB -> 10 KB statt der
//                        erwarteten 4-8 KB) verursacht - siehe Analyse
//                        weiter oben in diesem Changelog. Falls dieser
//                        Test die Sprunggrenze doch ueberschreitet, muessten
//                        stattdessen ungenutzte Programmteile testweise per
//                        dokumentiertem #ifdef-Guard deaktiviert werden
//                        (noch nicht umgesetzt). BUGFIX 2.30.53b: die beiden
//                        Zaehler standen zunaechst direkt vor
//                        scenario_hist_put() - hinter save_current_lists(),
//                        wo sie zuerst benutzt werden. Anders als bei
//                        Funktionen generiert Arduino fuer Variablen KEINEN
//                        Auto-Prototypen ("was not declared in this scope").
//                        Nach vorne verschoben in den Konstanten-Block
//                        (gleiche Fehlerklasse wie beim v2.30.51-Fix oben).
// -----------------------------------------------------------------------
// Version: 2.30.52      Generiert: 2026-09-25 (CODE-GROESSE REDUZIERT:
//                        auf Nutzerwunsch die komplette serielle
//                        Datei-Upload-Funktion (Menue 6, Taste 'u',
//                        PC -> ESP per roher serieller Uebertragung)
//                        entfernt, um den "dangerous relocation: j:
//                        cannot encode"-Linkerfehler (zu grosses Sketch-
//                        Binary) zu beheben. Entfernt: States
//                        STATE_UPLOAD_FILENAME/STATE_UPLOAD_RECEIVING,
//                        die Funktionen menu_enter_upload_filename(),
//                        menu_enter_upload_receiving(), handle_upload_byte(),
//                        finish_upload(), cancel_upload(), alle zugehoerigen
//                        globalen Variablen/Defines (upload_filename_buf,
//                        upload_path, upload_file, upload_started,
//                        upload_finished, upload_wait_start,
//                        upload_last_byte_time, upload_bytes,
//                        UPLOAD_WAIT_TIMEOUT_MS, UPLOAD_IDLE_TIMEOUT_MS)
//                        sowie alle Aufrufstellen (Taste 'u' in Menue 6,
//                        Backspace/ESC-Handler, Timeout-Behandlung in
//                        menu_periodic(), Vorab-Byte-Abfang in
//                        menu_handle_serial(), input_field_active(),
//                        LED-Sonderfall, Hilfetexte). Der davon unabhaengige
//                        HTTP-Datei-Upload (Menue 7, Browser -> ESP) ist
//                        nicht betroffen.
// -----------------------------------------------------------------------
// Version: 2.30.51      Generiert: 2026-09-18 (KOMPILIERUNGSFIX zu 2.30.50:
//                        "ScenarioEncoder was not declared in this scope"
//                        (Folgefehler: "redeclared as different kind of
//                        entity" an mehreren Stellen). Gleiche Fehlerklasse
//                        wie schon mehrfach zuvor in diesem Sketch (siehe
//                        z.B. watchlist_sighting-Fix 2.30.22, filter_has_mac
//                        2.30.25, selected_ap_indices 2.30.49) - diesmal
//                        aber nicht beim Rueckgabetyp, sondern beim
//                        PARAMETERTYP: Arduino generiert fuer jede im Sketch
//                        gefundene Funktions-DEFINITION (nicht nur
//                        Deklaration) automatisch einen Prototypen ganz
//                        oben in der Datei - das gilt genauso fuer
//                        Parametertypen wie "ScenarioEncoder&"/
//                        "ScenarioDecoder&". Solange die scenario_*-
//                        Funktionen in 2.30.49 nur deklariert waren (kein
//                        Koerper), fand der Scanner keine Definitionen und
//                        gab Ruhe - seit sie in 2.30.50 implementiert
//                        wurden, versuchte Arduino automatisch Prototypen
//                        mit diesen Struct-Referenzen zu erzeugen, weit vor
//                        der bisherigen Struct-Definition weiter unten im
//                        Sketch. Fix: ScenarioEncoder/ScenarioDecoder/
//                        ScenarioLineReader (und die Konstanten, von denen
//                        sie abhaengen) direkt hinter mac_lookup_result ganz
//                        an den Anfang des Sketches verschoben, noch vor
//                        promisc_cb() und allem anderen. Zusaetzlich
//                        explizite Prototypen fuer die beiden bisher nur
//                        implizit ueber Arduinos Auto-Prototyping
//                        abgedeckten internen Helfer scenario_lzss_step()/
//                        scenario_dec_hist_put() ergaenzt. Reiner
//                        Kompilierungsfix, keine Verhaltensaenderung - die
//                        in 2.30.50 per Testharness verifizierte Codec-Logik
//                        selbst bleibt unveraendert.
// -----------------------------------------------------------------------
// Version: 2.30.50      Generiert: 2026-09-18 (Szenario-Kompression
//                        FERTIGGESTELLT: Die von ChatGPT hochgeladene
//                        Version deklarierte 17 der 20 scenario_*-
//                        Funktionen nur (Forward-Declaration, kein
//                        Funktionskoerper) - das war die alleinige Ursache
//                        aller "undefined reference to scenario_..."-
//                        Linkerfehler, nichts mit dem fruehreren "dangerous
//                        relocation"-Flash-Groessenproblem zu tun. Alle 17
//                        fehlenden Funktionen jetzt implementiert: RLE-
//                        Vorstufe (Laeufe >=4 gleicher Bytes bzw. jedes
//                        0xFF-Byte werden als 3-Byte-Escape-Sequenz kodiert)
//                        gefolgt von klassischem LZSS mit 2-KB-Schiebefenster
//                        (Flags-Byte + bis zu 8 Tokens pro Gruppe, Literal=
//                        1 Byte, Match=2 Byte gepackt aus 11 Bit Distanz +
//                        5 Bit Laenge). Match-Suche bewusst auf back>=len
//                        begrenzt (keine ueberlappenden Matches) - vermeidet
//                        jedes Korrektheitsrisiko bei Selbstreferenzen,
//                        kostet praktisch nichts, da lange Gleichlaeufe
//                        ohnehin schon die RLE-Vorstufe abdeckt. Vor dem
//                        Einbau per eigenstaendigem Test-Harness (g++,
//                        Datei-Klasse durch In-Memory-Mock ersetzt, hier
//                        NICHT Teil des Sketches) verifiziert: Rundweg
//                        Original->Komprimiert->Dekomprimiert bytegleich
//                        auf Leerstring, Einzelzeichen, lange Gleichlaeufe,
//                        0x00/0xFF-Grenzfaelle, einer realistischen 200-
//                        Zeilen-Sicherungsdatei (19.371 -> 3.057 Byte,
//                        15,8%), einer 2000-Zeilen-Datei groesser als das
//                        2-KB-Fenster (192.890 -> 25.751 Byte, 13,4%),
//                        Zufallsdaten (Kompressions-Worst-Case) und allen
//                        256 Bytewerten mehrfach - ausnahmslos bestanden.
//                        Ausserdem FIRMWARE_VERSION/-BUILD_DATE-Define und
//                        Header-Kommentar bisher inkonsistent (Define stand
//                        weiter auf "2.30.49", Kommentar sprang direkt auf
//                        "2.31.00") - hiermit wieder synchron, Nummerierung
//                        bewusst in der bisherigen 2.30.x-Zaehlweise
//                        fortgesetzt statt des Sprungs auf 2.31.00.
// -----------------------------------------------------------------------
// Version: 2.31.00      Generiert: 2026-09-21
// NEU: Szenario-Kompression RLE + LZSS, 2-KB-Fenster, CSZ1, abwaertskompatibler Klartext-Lader.
// -----------------------------------------------------------------------
// Version: 2.30.49      Generiert: 2026-09-17 (AUFTRAG 2: Hintergrundverkehr-
//                        Statistik ("Funktion b" aus Menue 3a Variante 1,
//                        siehe v2.30.39) jetzt auch in Variante 2 (SSID-
//                        Buendelung) und Variante 3 (Multi-AP) verfuegbar,
//                        statt bisher nur bei einem einzelnen AP. Kern-
//                        aenderung: der bisherige feste Guard "ap_idx ==
//                        traffic_stats_ap_idx" wurde durch die neue Funktion
//                        traffic_stats_ap_included() ersetzt, die je nach
//                        Modus (Snapshot von current_list_mode bei Start)
//                        prueft: Modus 1 weiterhin exakt ein AP-Index,
//                        Modus 2 SSID-Gleichheit mit einem bei Start
//                        kopierten SSID-Snapshot, Modus 3 Mitgliedschaft in
//                        der bereits bestehenden globalen selected_ap_
//                        indices[]/selected_ap_count-Liste (bewusst nicht
//                        dupliziert, um keinen zusaetzlichen RAM-Verbrauch
//                        zu erzeugen). "AP gesamt" ist jetzt implizit die
//                        Summe ueber alle eingeschlossenen APs; die Client-
//                        Zeile bekommt bei Modus 2/3 eine zusaetzliche AP-
//                        Spalte, da dort (anders als bei Modus 1) mehrere
//                        APs im Spiel sind. Das nie gelesene ap_idx-Feld in
//                        traffic_ap_stat wurde bei der Gelegenheit gestrichen
//                        (spart 1 Byte je Statistiklauf). BUGFIX dabei
//                        entdeckt: menu_go_back() sprang aus STATE_TRAFFIC_
//                        STATS bisher IMMER zurueck in die Einzel-AP-Ansicht
//                        (Modus 1), unabhaengig vom tatsaechlichen current_
//                        list_mode - waere seit dieser Erweiterung bei Modus
//                        2/3 falsch gewesen; jetzt derselbe Dispatch wie in
//                        redraw_ssid_list(). Technisch: selected_ap_indices[]/
//                        selected_ap_count mussten von ihrer bisherigen
//                        Deklarationsstelle (nach promisc_cb()) nach VORNE
//                        verschoben werden (gleiche Fehlerklasse wie schon
//                        mehrfach zuvor, z.B. watchlist_sighting/filter_has_
//                        mac) - traffic_stats_ap_included() wird pro Paket
//                        aus promisc_cb() heraus aufgerufen und braucht fuer
//                        Modus 3 lesenden Zugriff darauf.
//                        AUSSERDEM (Flash-Platz fuer obige Erweiterung
//                        geschaffen): die beiden versteckten Testfunktionen
//                        Umschalt+C/Umschalt+P (Hidden Settings, simulierten
//                        einen Client-/AP-Listenueberlauf zum Life-Test der
//                        Auto-Offline/Auto-Save-Funktionalitaet, siehe
//                        v2.29.1) komplett entfernt - Tests abgeschlossen,
//                        Funktionalitaet bestaetigt funktionsfaehig, nicht
//                        mehr benoetigt.
// -----------------------------------------------------------------------
// Version: 2.30.72      Generiert: 2026-10-03
//                        Statistik-Kompaktkopf und Dateistatistik-Spalten
//                        ausgerichtet; Detailverkehr-Ausgabe auf Start/AP/
//                        Client/MAC sowie Pakete/kB/Bezeichnung umgestellt.
// -----------------------------------------------------------------------
// Version: 2.30.48      Generiert: 2026-09-16 (weitere Codegroesse
//                        gespart, siehe "dangerous relocation"-Linker-
//                        fehler - kein Zugriff auf die ESP8266-Core-Datei
//                        moeglich, daher weiter ueber die Sketch-Groesse):
//                        die urspruengliche Debug-Instrumentierung der
//                        VendorLookup-Klasse (Ablauf-/Timing-Verfolgung,
//                        seinerzeit zur Fehlersuche eingebaut, siehe
//                        Versionsgeschichte 2.23.1/2.28.4) komplett
//                        entfernt: 32 debugLog()-Aufrufe (jeweils mit
//                        String-Verkettung) sowie die ausschliesslich
//                        dafuer verwendeten Hilfsfunktionen debugPause()
//                        und debugBytesToHex(). g_debugFlag/debugLog()/
//                        debugLogImpl() selbst bleiben unveraendert
//                        bestehen, da sie weiterhin fuer die HTTP-Upload-
//                        Debugausgabe (Strg+D) gebraucht werden. Keine
//                        Funktionsaenderung an der eigentlichen Vendor-
//                        Lookup-Logik.
// -----------------------------------------------------------------------
// Version: 2.30.47      Generiert: 2026-09-16 (Kompilierfehler nach
//                        ArduinoDroid-App-Update behoben):
//                        1) BUGFIX: nach dem App-Update scheiterte die
//                        Kompilierung mit einer Fehlerkaskade ("SortField
//                        was not declared in this scope", "RamDebugPoint
//                        was not declared in this scope", "redeclared as
//                        different kind of entity" usw.). Ursache: die
//                        Funktionen ram_debug_sample(), default_ascending_
//                        for(), set_sort_field(), sort_field_name() und
//                        default_ap_ascending_for() hatten - anders als die
//                        meisten uebrigen Funktionen im Programm - KEINE
//                        eigene, fruehe Vorwaertsdeklaration. Die
//                        automatische Arduino-Prototyperzeugung generierte
//                        deshalb selbst eine, offenbar an einer Stelle VOR
//                        den Definitionen von RamDebugPoint/SortField/
//                        ApSortField - mit dem App-Update hat sich
//                        entweder die Version dieses Generators geaendert
//                        oder er verhaelt sich seitdem strenger (siehe
//                        bereits vorhandener Kommentar zu genau diesem
//                        Phaenomen bei traffic_detail_address_match(), Punkt
//                        2.30.42). Fix: fuer alle fuenf betroffenen
//                        Funktionen jetzt eine explizite Deklaration direkt
//                        NACH der jeweiligen Enum-Definition ergaenzt -
//                        analog zum bereits fuer set_ap_sort_field()/
//                        ap_sort_field_name() bestehenden Muster, das davon
//                        nicht betroffen war. Keine Funktionsaenderung.
//                        2) Aufraeumen zur Reduzierung der Programmgroesse
//                        (siehe der vom Anwender gemeldete "dangerous
//                        relocation: j: cannot encode"-Linkerfehler, verur-
//                        sacht durch einen bekannten Bug in ESP8266-Arduino-
//                        Core 3.1.2, kein neuerer Core in ArduinoDroid
//                        verfuegbar): die SP-Adressvergleichsdiagnose aus
//                        2.30.38 (Registerauslesung + Anzeige in der Call-
//                        Chain-Ansicht) entfernt. Sie war ausdruecklich nur
//                        eine einmalige Untersuchungshilfe, um zu klaeren,
//                        ob Hauptprogramm und Promiscuous Callback denselben
//                        physischen Stack nutzen - das ist laengst
//                        beantwortet (2.30.46-Testbericht: 26592 Byte
//                        Differenz, zwei verschiedene Stacks bestaetigt)
//                        und wird fuer den laufenden Betrieb nicht mehr
//                        gebraucht. Alle uebrigen Call-Chain-/RAM-Debug-
//                        Funktionen bleiben unveraendert.
// -----------------------------------------------------------------------
// Version: 2.30.46      Generiert: 2026-09-15 (zwei vom Anwender gemeldete
//                        Maengel am neuen Beacon-FrameTrap aus 2.30.45):
//                        1) BUGFIX: Byte 24-31 (Timestamp/TSF) fehlte
//                        komplett in der gespeicherten FrameTrap-Datei -
//                        ergaenzt, mit identischer Darstellung (64-Bit-Wert
//                        in Mikrosekunden + "ca. X Tage HH:MM:SS.mmm") wie
//                        in der Live-Anzeige (Menue 3, "w"+Zahl).
//                        2) Ein scharf gemachter Beacon-FrameTrap wurde
//                        bisher nur in einer eigenen, nicht sichtbaren und
//                        nicht persistenten Liste gefuehrt - anders als der
//                        Client-FrameTrap, der ueber die Watchlist laeuft
//                        und dort markiert erscheint. Umgestellt: der
//                        Beacon-FrameTrap nutzt jetzt ebenfalls die
//                        Watchlist (eigener Marker " (wait BC)" statt
//                        " (wait PR)" beim Client-FrameTrap) - erscheint
//                        dadurch in Menue 4 und uebersteht wie der Client-
//                        FrameTrap einen Neustart. Die Watchlist speichert
//                        dabei weiterhin nur MAC-Adressen ganz allgemein;
//                        ob Client oder AP/BSSID, ergibt sich ausschliesslich
//                        aus dem jeweiligen Marker.
// -----------------------------------------------------------------------
// Version: 2.30.45      Generiert: 2026-09-15 (Anwenderwuensche):
//                        1) Begriff "Mausefalle" durchgaengig ersetzt durch
//                        "FrameTrap" - sowohl alle internen Bezeichner
//                        (z.B. MOUSETRAP_MAX_PENDING -> FRAMETRAP_CLIENT_
//                        MAX_PENDING, mousetrap_arm() -> frametrap_client_
//                        arm()) als auch alle sichtbaren Meldungen ("Falle
//                        scharf" -> "FrameTrap scharf" usw.). Funktion/
//                        Ablauf des bestehenden Client-FrameTrap (Menue 3a,
//                        "wp"+Zahl+Enter) unveraendert.
//                        2) NEU: FrameTrap jetzt auch fuer Beacons in Menue
//                        3 ("wt"+Zahl+Enter, max. 5 gleichzeitig) - z.B. fuer
//                        selten sendende APs, die man sonst im "w"+Zahl-
//                        Wartebildschirm verpasst. Gleicher Aktivierungs-/
//                        Ablaufmechanismus wie beim Client-FrameTrap (eigene
//                        kleine feste Liste statt Watchlist, da es keine
//                        "AP-Watchlist" gibt), gleiche Datei-Syntax beim
//                        Speichern des Ergebnisses (/BC_<mac>_<ssid>.txt,
//                        analog zu /PR_... beim Client-FrameTrap). Taste 't'
//                        statt 'p', weil 'p' in Menue 3 bereits als "nach
//                        RSSI sortieren" belegt ist.
//                        3) Menuepunkte 5 und 6: RAM/Speicher-Anzeige zeigt
//                        jetzt den absoluten freien Speicher in Byte (mit
//                        Tausenderpunkten) statt einer Prozentanzeige
//                        (zentral in print_fs_info(), betrifft damit auch
//                        den seriellen Datei-Empfang, der dieselbe Funktion
//                        nutzt).
//                        4) Menuepunkt 6 ("Gespeicherte Dateien"): Kopfzeile
//                        zeigt jetzt zusaetzlich die Gesamtzahl ALLER
//                        tatsaechlich vorhandenen Dateien (inkl. geschuetzter/
//                        aktuell ausgeblendeter), unabhaengig von der auf 20
//                        Zeilen begrenzten Anzeige und vom "h"-Sichtbarkeits-
//                        Toggle.
// -----------------------------------------------------------------------
// Version: 2.30.44      Generiert: 2026-09-15 (Sammelkorrektur aus einem
//                        Testbericht des Anwenders):
//                        1) BUGFIX: "Detailverkehr Client" liess sich mit
//                        Backspace nicht mehr verlassen (auch Strg+O danach
//                        wirkungslos, nur ESC half). Ursache: menu_go_back()
//                        rief bei STATE_TRAFFIC_DETAIL zwar traffic_stats_
//                        redraw() auf, setzte menu_state aber vorher nie auf
//                        STATE_TRAFFIC_STATS zurueck - diese Funktion bricht
//                        jedoch sofort ab, wenn menu_state nicht bereits
//                        diesen Wert hat. menu_state blieb dadurch dauerhaft
//                        auf STATE_TRAFFIC_DETAIL haengen.
//                        2) Tabellenformat in "Detailverkehr Client" neu
//                        ausgerichtet (bisher zu breit, Beschriftung nicht
//                        spaltengenau ueber den Werten) - Spaltenbreiten
//                        jetzt exakt auf die Kopfzeile abgestimmt, rohe
//                        Subtyp-Nummer entfernt (Klartextname reicht).
//                        3) BUGFIX: OFFLINE-/Channel-Warnung landete auf
//                        Bildschirmen, die bewusst ohne Zeilenumbruch auf
//                        einem Eingabe-Prompt enden (z.B. " Auswahl: "),
//                        direkt hinter dem Prompt auf derselben Zeile statt
//                        darunter (der seit 2.30.32 verwendete Offline-
//                        BannerGuard feuert unveraendert am Funktionsende).
//                        Neue Hilfsfunktion offline_banner_will_print()
//                        klaert vorab, ob gleich etwas ausgegeben wird - nur
//                        dann wird ein Zeilenumbruch nach dem Prompt
//                        eingefuegt. An 14 betroffenen Stellen angewendet
//                        (SSID-Uebersicht, Dateiliste, diverse MAC-/Text-
//                        Eingaben, Watchlist).
//                        4) BUGFIX (aus einem gemeldeten Phaenomen
//                        hergeleitet): die MAC-Nachschlagefunktion (Punkt
//                        2.3) zeigte bei manchen Clients "Angemeldet an:
//                        unbekannt", obwohl derselbe Client in der
//                        Geraeteuebersicht seiner SSID korrekt gelistet war.
//                        Ursache in register_client(): ein Client, der ZUERST
//                        gesehen wird, BEVOR sein AP registriert ist, bekommt
//                        ap_idx = AP_IDX_NONE. Wird er SPAETER mit bekanntem
//                        ap_idx erneut gesehen, griff die bisherige "bereits
//                        bekannt"-Pruefung (gleiche MAC UND gleicher ap_idx)
//                        nicht mehr - es entstand ein ZWEITER, dauerhafter
//                        Eintrag mit korrektem ap_idx, waehrend der alte
//                        "unbekannt"-Eintrag bestehen blieb. Die MAC-Nach-
//                        schlagefunktion (einfache lineare Suche nach der
//                        ERSTEN passenden MAC) fand meist den aelteren,
//                        veralteten Eintrag. Fix: ein solcher "Platzhalter"-
//                        Eintrag (gleiche MAC, noch AP_IDX_NONE) wird jetzt
//                        erkannt und bei Bekanntwerden des AP nachtraeglich
//                        aktualisiert statt dupliziert.
//                        5) Neu: Zeitstempel-Praefix ("+NNNNNNms") in Punkt
//                        2.1/2.2 (Live-Ausgabe), analog zum bereits
//                        vorhandenen Zeitstempel in Punkt 2.4 - gezaehlt ab
//                        dem Betreten dieses Live-Filters, bleibt bei einem
//                        Refresh (z.B. Strg+O) erhalten.
//                        6) Call-Chain-Anzeige (Debug RAM Memory > Call-Chain
//                        anzeigen) listet jetzt AUSNAHMSLOS ALLE Messpunkte
//                        auf (Anwenderwunsch), auch mit 0 Aufrufen ("--
//                        noch nicht erreicht --") - vorher wurden unbenutzte
//                        Punkte stillschweigend weggelassen, wodurch nicht
//                        erkennbar war, welcher Codepfad im laufenden Test
//                        noch gar nicht durchlaufen wurde.
//                        7) SP-Adressvergleich vom Anwender getestet: 26592
//                        Byte Differenz zwischen Hauptprogramm- und
//                        Promiscuous-Callback-Kontext - bestaetigt damit die
//                        in 2.30.38 aufgestellte Vermutung, dass der
//                        Callback auf einem ANDEREN physischen Stack laeuft.
//                        Die Call-Chain-Anzeige weist bei jeder Kette im
//                        PROMISCUOUS-CALLBACK-Kontext jetzt entsprechend
//                        darauf hin, dass deren Stack-Werte vermutlich nicht
//                        aussagekraeftig sind (Heap/Block/Fragmentierung
//                        bleiben davon unberuehrt). Noch nicht geloest: eine
//                        verlaessliche Methode, den tatsaechlichen Stack-
//                        verbrauch des Callbacks selbst zu messen (keine
//                        offizielle ESP8266-Arduino-API dafuer vorhanden).
//                        8) Versionsnummer im Code (FIRMWARE_VERSION) war
//                        seit mehreren Versionen nicht mehr mit dem
//                        tatsaechlichen Stand/Dateinamen synchron (stand
//                        noch auf "2.30.39") - korrigiert.
//                        Noch offen (keine Codeaenderung, zu wenig
//                        Diagnosedaten): das gemeldete Phaenomen, dass ein
//                        bestimmter, nicht verstecker AP in der SSID-
//                        Uebersicht mit aktueller Age-Zeit gesehen wird,
//                        aber weder ueber "w"+Zahl noch ueber einen MAC-
//                        Filter (Punkt 2.1) auf Beacons dieses AP je ein
//                        Beacon zeigt, obwohl andere Frametypen von/zu
//                        diesem AP durchaus erfasst werden.
// -----------------------------------------------------------------------
// Version: 2.30.43      Generiert: 2026-09-15 (KORREKTUR: Arduino-IDE-
// 2.30.43: Korrektur eines Syntaxfehlers in der MenuState-Enumeration:
//                        fehlendes Komma nach STATE_TRAFFIC_STATS. Vor Ausgabe
//                        der Version wurden die neu erzeugten Deklarationen und
//                        die Enum-/Block-Struktur erneut auf Reihenfolge und
//                        Klammerbalance geprueft. Keine Funktionsaenderung.
// 2.30.42: Auftrag 2 ergaenzt: Detailverkehrsstatistik fuer genau einen
//                        ausgewaehlten Client. Gezahlt werden Gesamtpakete/
//                        Gesamtbytes sowie Management-, Control- und Data-
//                        Subtypen. Die Detailstatistik wird nur fuer den
//                        ausgewaehlten Client im laufenden Betrieb erfasst.
//                        Keine Paketdaten werden gespeichert. Auswahl und
//                        Anzeige verwenden neutrale Bezeichnungen; die
//                        Begriffe "Auftrag 1"/"Auftrag 2" erscheinen nicht
//                        auf der seriellen Konsole.
//                        Prototyp-Reihenfolge systematisch bereinigt): Die
//                        neu erzeugten frei stehenden Call-Chain-Hilfsfunktionen
//                        verwenden keine spaeter deklarierten enum/struct-Typen
//                        mehr in ihren Funktionsparametern. Dadurch koennen die
//                        von der Arduino-IDE automatisch erzeugten Prototypen
//                        nicht vor CallChainContext/CallChainSnapshot auf einen
//                        noch unbekannten Typ treffen. Konkret: 
//                        call_chain_note_stack() verwendet uint8_t statt
//                        CallChainContext; call_chain_print_snapshot() verwendet
//                        primitive Snapshot-Parameter statt CallChainSnapshot&.
//                        Vor Ausgabe dieser Version wurde der Quelltext gezielt
//                        auf weitere frei stehende Funktionen mit diesen
//                        spaeter deklarierten Call-Chain-Typen geprueft.
//                        Die Funktionalitaet bleibt unveraendert.
// -----------------------------------------------------------------------

//                        Ursache: Die Arduino-Prototyperzeugung konnte die
//                        Hilfsfunktion call_chain_copy_active() mit einem
//                        Parameter vom Typ CallChainSnapshot & vor der
//                        Struct-Deklaration nicht korrekt verarbeiten. Die
//                        Funktion verwendet jetzt ausschliesslich primitive
//                        Pointer/uint8_t-Parameter; die Logik bleibt unveraendert.
// -----------------------------------------------------------------------
// Version: 2.30.39      Generiert: 2026-09-15 (AUFTRAG 1: Hintergrundverkehr-
//                        Statistik fuer einen ausgewaehlten Access Point):
//                        Neue, nur waehrend der Statistik aktive, kompakte
//                        Verkehrserfassung. Fuer den aktuell in Menue 3b
//                        ausgewaehlten einzelnen AP werden echte Data-Frames
//                        gezaehlt und deren Frame-Laenge summiert. Der AP
//                        erhaelt einen 9-Byte-Datensatz (AP-Index 1 Byte,
//                        Pakete 4 Byte, Bytes 4 Byte), Clients je einen
//                        10-Byte-Datensatz (clients_known[]-Index 2 Byte,
//                        Pakete 4 Byte, Bytes 4 Byte). Maximal 64 Client-
//                        Datensaetze; der Speicher wird erst beim Start der
//                        Statistik per malloc() reserviert und beim Verlassen
//                        wieder freigegeben. Die Client-Suche erfolgt sortiert
//                        nach dem echten clients_known[]-Index per Binaersuche
//                        plus Last-Hit-Cache. Die bestehende Client-Erkennung
//                        wird nicht doppelt durchsucht: register_client()
//                        liefert zusaetzlich den gerade verwendeten
//                        clients_known[]-Index. Keine Paketdaten werden
//                        gespeichert. Auftrag 1 ist bewusst auf den einzelnen
//                        AP (nicht SSID-Buendel/Multi-AP) begrenzt, damit die
//                        Zuordnung eindeutig bleibt und der RAM-Verbrauch
//                        klein bleibt. Erfassung laeuft im Promiscuous-Callback,
//                        Anzeige/Refresh im Hauptloop. Bestehende Funktionen
//                        bleiben ausserhalb der beauftragten Erweiterung
//                        unveraendert.
// -----------------------------------------------------------------------
// Version: 2.30.38      Generiert: 2026-09-14 (Anwenderfrage: "AKTUELL
//                        Free Stack" bleibt dauerhaft auf dem MINIMUM-Wert
//                        stehen - ist das ein Fehler?):
//                        1) Geklaert (kein Programmfehler, sondern
//                        Eigenschaft der zugrunde liegenden ESP8266-Core-
//                        Funktion): ESP.getFreeContStack() liefert laut
//                        Core-Quellcode (cont_util.cpp, Kommentar "high
//                        water mark") einen Tiefpunkt-Wert, der beim Boot
//                        per Canary-Muster ermittelt wird und sich NUR
//                        verschlechtern kann, nie erholt (bis zum Neustart
//                        oder einem expliziten ESP.resetFreeContStack()) -
//                        es ist also kein Live-Wert im Sinne von "aktuell
//                        genutzter Stack", sondern dasselbe monoton
//                        fallende Wasserzeichen, das auch die MINIMUM-
//                        Anzeige verwendet. Kein Code wurde dafuer
//                        geaendert - reine Klarstellung, siehe Kommentar
//                        bei der AKTUELL-Ausgabe in menu_enter_ram_debug().
//                        2) Neue, bisher ungeklaerte Vermutung aufgeworfen
//                        und dafuer ein risikofreier Diagnosewert ergaenzt:
//                        der ESP8266 (NONOS-SDK) fuehrt setup()/loop() ueber
//                        einen eigenen "cont"-Stack aus; SDK-Callbacks wie
//                        der Promiscuous-Callback koennten dagegen auf
//                        einem ANDEREN physischen Stack laufen - dann wuerde
//                        ESP.getFreeContStack() innerhalb von promisc_cb()
//                        moeglicherweise gar nicht dessen eigenen
//                        Stackverbrauch messen, sondern zufaellig den Stand
//                        des pausierten Hauptprogramm-Stacks. Um das
//                        empirisch (statt spekulativ) zu klaeren, wird jetzt
//                        je Kontext (CTX_MAIN/CTX_PROMISC) die rohe Stack-
//                        Pointer-Adresse (Register a1) beim Guard-Eintritt
//                        mitgefuehrt und in "Call-Chain anzeigen" einander
//                        gegenuebergestellt (grosse Differenz = zwei
//                        verschiedene Stacks, kleine Differenz = derselbe).
//                        Bewusst NUR ein Registerzugriff (kein
//                        cont_repaint_stack()/resetFreeContStack() aus dem
//                        Callback heraus - das waere riskant, falls die
//                        Vermutung zutrifft und dabei versehentlich der
//                        pausierte Hauptprogramm-Stack ueberschrieben
//                        wuerde). Noch keine abschliessende Bewertung der
//                        bisherigen AP_CAPTURE/CLIENT_CAPTURE-Callback-
//                        Messwerte - das haengt vom Testergebnis dieser
//                        Gegenueberstellung ab.
// -----------------------------------------------------------------------
// Version: 2.30.37      Generiert: 2026-09-14 (Entwickleranweisung:
//                        Call-Chain-Diagnose grundlegend korrigiert -
//                        die v2.30.35-Umsetzung fuehrte eine einzige
//                        globale aktive Kette, wodurch beim Promiscuous
//                        Callback (asynchron, unterbricht das Hauptprogramm
//                        jederzeit) faelschlich Ketten wie "INPUT ->
//                        AP_LIST -> VENDOR_LOOKUP -> AP_CAPTURE" entstehen
//                        konnten, die KEINE echte synchrone Caller->Callee-
//                        Beziehung darstellen, sondern zwei unabhaengige,
//                        zufaellig ueberlagerte Ausfuehrungskontexte waren.
//                        Fix: zwei strikt getrennte Ketten-Kontexte
//                        (CTX_MAIN fuer Hauptprogramm/Menue, CTX_PROMISC
//                        fuer den Promiscuous Callback) mit jeweils eigenem
//                        Tiefen-/Array-Zustand - eine im Callback begonnene
//                        Kette beginnt IMMER bei Tiefe 0 und kann sich
//                        niemals an eine im Hauptprogramm aktive Kette
//                        anhaengen. Der Kontext wird an jeder Aufrufstelle
//                        des CallChainGuard explizit angegeben (Default
//                        CTX_MAIN), nie automatisch geerbt. Zusaetzlich
//                        tiefere Instrumentierung entlang des tatsaechlichen
//                        Verarbeitungswegs: neue Messpunkte CALLBACK (Wurzel
//                        des Promiscuous-Callback-Kontexts), PARSE_BEACON,
//                        REGISTER_BEACON, PARSE_DATA und REGISTER_CLIENT an
//                        den echten Funktionsgrenzen (statt wie bisher nur
//                        ein einzelner Punkt kurz vor register_beacon()
//                        bzw. register_client(), der die Vorverarbeitung in
//                        parse_beacon()/parse_data() nicht abdeckte). Neu:
//                        CallChainGuard::probe() fuer gezielte Zwischen-
//                        Messungen waehrend einer Funktion (in
//                        register_beacon()/register_client() jeweils nach
//                        der Listen-Suchschleife) - erfasst den tatsaechlichen
//                        Tiefpunkt waehrend der Ausfuehrung, nicht nur den
//                        Eintrittswert. Die Anzeige (Call-Chain anzeigen)
//                        nennt bei jeder Kette jetzt explizit den Kontext
//                        ("PROMISCUOUS CALLBACK" bzw. "Hauptprogramm/
//                        Menue"). Die bestehende Basis-RAM-Diagnose
//                        (ram_debug_sample(), RamDebugState, die vorhandenen
//                        AP_CAPTURE/CLIENT_CAPTURE-Messpunkte fuer die
//                        Basiswerte) bleibt unveraendert, ebenso die
//                        vorhandenen Aufrufzaehler. Zusaetzlich verifiziert:
//                        die AKTUELL-Anzeige (Free Stack) fragt bereits bei
//                        jedem Aufruf frisch ESP.getFreeContStack() ab und
//                        verwechselt dies nicht mit dem gespeicherten
//                        Minimum - kein Code-Fehler; ein zufaelliges
//                        Zusammentreffen von AKTUELL und MINIMUM ist durch
//                        die eigene Verschachtelungstiefe dieses Menuebild-
//                        schirms plausibel. Noch keine Optimierung am
//                        eigentlichen Programmcode (Vorgabe Pkt.20) -
//                        ausschliesslich Diagnose/Messung.
// -----------------------------------------------------------------------
// Version: 2.30.36      Generiert: 2026-09-14 (Fehlerkorrektur, gemeldet
//                        vom Anwender: RAM-Referenzwert stand zwar korrekt
//                        auf 49.024 Byte, wurde aber in der Anzeige nicht
//                        korrekt dargestellt). Ursache: format_number_
//                        with_dots() liefert einen Zeiger auf einen
//                        EINZIGEN statischen Puffer, der bei jedem Aufruf
//                        ueberschrieben wird. In der RAM-Zeile (Punkt i)
//                        wurde diese Funktion seit v2.30.33 zweimal
//                        innerhalb DESSELBEN printf_P()-Aufrufs verwendet
//                        (Referenzwert UND aktuell freier Heap) - die
//                        Auswertungsreihenfolge der Funktionsargumente ist
//                        in C/C++ nicht garantiert, wodurch beide %s-Stellen
//                        je nach Compiler/Optimierung denselben (falschen)
//                        Text zeigen konnten. Fix: der formatierte
//                        Referenzwert-String wird jetzt vor dem eigentlichen
//                        printf_P()-Aufruf in einen eigenen, unabhaengigen
//                        Puffer kopiert. Am Referenzwert selbst (49.024
//                        Byte), an der Berechnung oder an sonstigen
//                        Anzeigen wurde nichts veraendert; alle uebrigen
//                        Aufrufstellen von format_number_with_dots() im
//                        Programm verwenden die Funktion je Statement nur
//                        einmal und waren von diesem Bug nicht betroffen.
// -----------------------------------------------------------------------
// Version: 2.30.35      Generiert: 2026-09-14 (zwei unabhaengige
//                        Entwickleraufträge):
//                        1) RAM-/Stack-Diagnose um optionale Call-Chain-
//                        Analyse erweitert (Debug RAM Memory > Taste '3'/'4').
//                        Rein additiv - die bestehende Diagnose (Free Heap/
//                        Max Free Block/Fragmentation/Free Stack samt
//                        Minimum-/Maximum-Messpunkt, ram_debug_sample(),
//                        RamDebugState) bleibt unveraendert. Eigener
//                        Schalter (Standard AUS, NICHT automatisch mit der
//                        RAM-Analyse gekoppelt - laeuft aber nur, wenn
//                        BEIDE Schalter EIN sind). Ein neuer RAII-Guard
//                        (CallChainGuard, gleiches Prinzip wie
//                        OfflineBannerGuard) traegt sich beim Eintritt in
//                        eine der bereits instrumentierten Funktionen in
//                        eine aktive Kette (active_chain_*, feste
//                        Obergrenze CALL_CHAIN_MAX_DEPTH=8) ein und beim
//                        Verlassen automatisch wieder aus - dadurch ist zu
//                        jedem Zeitpunkt exakt bekannt, welche Funktionen
//                        gerade ineinander verschachtelt aktiv sind, ohne
//                        eine vollstaendige Ereignishistorie zu fuehren.
//                        Gespeichert werden ausschliesslich: ein kompakter
//                        Aufrufzaehler je Funktions-ID (kein volles
//                        Caller->Callee-Array), die maximale beobachtete
//                        Verschachtelungstiefe samt zugehoeriger Kette, und
//                        die Kette zum bisher niedrigsten waehrend aktiver
//                        Call-Chain-Analyse gemessenen freien Stack (jeweils
//                        nur Funktions-ID + Eintritts-Stack pro Ebene - keine
//                        Strings, kein dynamischer Speicher). Instrumentiert
//                        an denselben bereits vorhandenen Messpunkten wie
//                        die Basis-Diagnose (Hauptloop/Kanalwechsel bewusst
//                        ausgenommen, da dort keine echte, klar abgrenzbare
//                        Verschachtelung vorliegt). Keine Serial-Ausgabe bei
//                        Aufruf/Verlassen einer Funktion, keine Aenderung an
//                        Timing/Netzwerk/Scan/ntfy/HTTP - die Anzeige
//                        erfolgt ausschliesslich auf Anforderung im Menue.
//                        2) Erweiterte Akku-Unterspannungswarnung: beim
//                        bereits bestehenden, unveraenderten dreifach
//                        bestaetigten ADC-Unterspannungsereignis werden
//                        zusaetzlich (a) ueber den vorhandenen Signalpin
//                        (inkl. dessen Aktiv-Low-Konfiguration) eine
//                        einmalige, nicht blockierende Folge von 5 Impulsen
//                        á 100ms ein/100ms aus ausgegeben, (b) die
//                        vorhandene Status-LED unabhaengig vom aktuellen
//                        Menue-/Betriebszustand in ein deutlich hektischeres
//                        Blinkmuster (100ms) versetzt, bis das bestehende
//                        Unterspannungs-Latch bei Spannungserholung wieder
//                        freigegeben wird, und (c) eine rote VT100-
//                        Warnmeldung mit gemessener Spannung und Schwelle
//                        einmalig auf der seriellen Konsole ausgegeben. Die
//                        bestehende ADC-Messung/-Kalibrierung/-Schwelle/
//                        3-fach-Bestaetigung/Listen-Speicherung bleibt
//                        vollstaendig unveraendert. Ausserdem verifiziert:
//                        der RAM-Referenzwert (49.024 Byte, siehe v2.30.33)
//                        war weiterhin korrekt gesetzt - keine Korrektur
//                        noetig.
// -----------------------------------------------------------------------
// Version: 2.30.34      Generiert: 2026-09-14 (letzter noch offener Punkt
//                        aus der v2.30.33-Sammel-Änderungsliste: passive
//                        RAM-/Stack-Diagnose, "Hidden Settings > Debug RAM
//                        Memory", Taste 'r'). Kernprinzip: MESSEN -> mit
//                        bisherigem Extremwert VERGLEICHEN -> ggf. neuen
//                        Extremwert SPEICHERN - rein beobachtend, greift nie
//                        in den normalen Programmablauf ein (kein Abbruch,
//                        kein Uebernspringen/Deaktivieren von Funktionen,
//                        keine Speicherfreigabe, keine "Test"-Allokation,
//                        keine Aenderung an Timing/Netzwerk/Scan/ntfy/HTTP/
//                        Dateizugriffen, keine automatische Reaktion/
//                        Bewertung, kein Neustart). Standardzustand nach
//                        jedem Neustart: AUS - dann kostet jeder Messpunkt
//                        nur einen einzigen if-Vergleich, es wird nichts
//                        aufgezeichnet. Gemessen werden ESP.getFreeHeap(),
//                        ESP.getMaxFreeBlockSize(), ESP.getHeapFragmentation()
//                        und ESP.getFreeContStack(); gespeichert werden
//                        ausschliesslich die aktuellen Extremwerte (Minimum
//                        bei Heap/Block/Stack, Maximum bei Fragmentierung)
//                        je mit kompakter numerischer Messpunkt-ID (RamDebug-
//                        Point, PROGMEM-Klartextnamen) sowie ein Mess-
//                        zaehler - keine Flash-Speicherung, keine Historie,
//                        insgesamt nur eine kleine RamDebugState-Struktur
//                        (kein grosses Array, kein dynamischer Puffer, keine
//                        String-Objekte fuer Messpunktnamen). Einschalten
//                        der Analyse startet laut Vorgabe automatisch eine
//                        neue Messperiode (alte Extremwerte verworfen);
//                        Menuepunkt "Messwerte loeschen" setzt ausschliesslich
//                        die Debug-Werte zurueck. Messpunkte liegen u.a. in
//                        Hauptloop, Menue-/Eingabeverarbeitung, WiFi-Scan/
//                        Kanalwechsel, AP-/Client-Erfassung (promisc_cb),
//                        AP-/Client-Listenausgabe, Vendor-Lookup/-Cache,
//                        LittleFS-Zugriff, Dateiliste, HTTP-Datei-Server/
//                        -Upload, Beacon-/Client-Rohanalyse, Watchlist sowie
//                        sieben dedizierten Punkten im ntfy-Versand (Start,
//                        Datei geoeffnet, Datei gelesen, Request aufgebaut,
//                        vor WiFi.begin(), Antwort erwartet, Ende). Keine
//                        kuenstlichen Speicher-Stresstests (kein malloc-
//                        Sondieren) - ausschliesslich reale Werte waehrend
//                        des normalen Betriebs, ueber vorhandene Core-
//                        Funktionen. Am uebrigen Programm wurde nichts
//                        veraendert.
// -----------------------------------------------------------------------
// Version: 2.30.33      Generiert: 2026-09-14 (mehrere unabhaengige
//                        Entwickleraufträge aus einer Sammel-Änderungsliste
//                        umgesetzt - jeweils rein darstellerisch/strukturell,
//                        keine Aenderung an Scanner/Parsing/Speicherlayout):
//                        1) Beacon-Timestamp/TSF: die bisherige High/Low-
//                        Zerlegung ("<high>*2^32 + <low>") ist entfallen,
//                        stattdessen "Timestamp/TSF : <64-Bit-Wert> µs" plus
//                        zweite Zeile "ca. <Tage> Tage HH:MM:SS.mmm". Die
//                        Byte-24-31-Auswertung/Little-Endian-Zusammensetzung
//                        ist unveraendert; die Umrechnung erfolgt komplett in
//                        uint64_t (neue Hilfsfunktion format_uint64_dec(),
//                        da printf("%llu") auf manchen ESP8266-Core-Versionen
//                        unzuverlaessig ist) - keine 32-Bit-Zwischenwerte, die
//                        ueberlaufen koennten.
//                        2) RAM-Referenzwert fuer die RAM%-Anzeige (Punkt i)
//                        von 80.000 auf empirisch ermittelte 49.024 Byte
//                        korrigiert (neues #define RAM_REFERENCE_BYTES,
//                        zentral verwendet) - Format/Text/Reihenfolge der
//                        RAM-Zeile selbst unveraendert.
//                        3) OFFLINE-/Channel-Scan-Warnzeilen stehen jetzt
//                        immer GANZ UNTEN in der jeweiligen Bildschirm-
//                        ausgabe statt oben, ohne die bisher dafuer
//                        verwendeten Leerzeilen. Technisch geloest ueber
//                        einen neuen RAII-Guard (OfflineBannerGuard): eine an
//                        der bisherigen Aufrufstelle (direkt nach
//                        vt_clear_screen()) deklarierte Instanz gibt die
//                        Warnung(en) erst in ihrem Destruktor aus - also
//                        automatisch beim Verlassen der jeweiligen Bild-
//                        schirmfunktion, auch bei vorzeitigem return. Die
//                        beiden States STATE_LIVE/STATE_DEBUG_LIVE (kein
//                        eigener Funktionsscope, sondern switch-case) wurden
//                        stattdessen manuell ans Ende ihres Case-Blocks
//                        verschoben. Inhalt/rote Darstellung beider Meldungen
//                        unveraendert.
//                        4) ADC-Einstellungen aus dem normalen Einstellungs-
//                        menue (bisher Taste 'b') entfernt und unter Hidden
//                        Settings (neue Taste 'd') verschoben - Funktion,
//                        Ausgabe und Bedienlogik der ADC-Einstellungen selbst
//                        unveraendert, nur der Menueort inkl. Backspace-
//                        Ruecksprung angepasst.
//                        5) In den Filterkriterien (Punkt 2.1/2.2) zeigen die
//                        uebergeordneten Punkte 4 (Probes/p), 5 (Management/
//                        m), 6 (Control/c) und 7 (Data/d) jetzt "[~]" statt
//                        "[x]", wenn im jeweiligen Unterauswahlmenue nur ein
//                        TEIL der Checkboxen aktiv ist (neue Tri-State-
//                        Hilfsfunktion chk_tri(), ergaenzt chk()). "[x]" (alle
//                        aktiv) und "[ ]" (keine aktiv) bleiben wie bisher.
//                        Noch NICHT umgesetzt aus derselben Änderungsliste:
//                        die passive RAM-/Stack-Diagnose (Hidden Settings >
//                        "Debug RAM Memory") - folgt in einer eigenen Version.
// -----------------------------------------------------------------------
// Version: 2.30.32      Generiert: 2026-09-09 (NEUES FEATURE: Punkt 2.4
//                        "Diagnose: scharfer Timing-Test" (Debug) - zur
//                        Klaerung des Probe-Request/Response-Raetsels bei
//                        einem Tasmota-Range-Extender-Client. MAC eingeben,
//                        dann X Sekunden lang (Vorgabe 60s) OHNE jegliche
//                        Ausgabe/Verarbeitung waehrend der Messung selbst -
//                        promisc_cb() springt bei aktivem Test ALS ALLER-
//                        ERSTES (noch vor dem online_mode-Guard) in
//                        timing_test_process_packet(), die komplett
//                        eigenstaendig dupliziert ist (kein find_ap_index_
//                        by_bssid(), kein AP-Cache, kein Serial.print() pro
//                        Paket) und nur Zeitstempel/Richtung/Subtyp/RSSI/
//                        Kanal in einen kleinen RAM-Ringpuffer (40 Eintraege)
//                        schreibt. Zweck: ausschliessen, dass die normale
//                        Programmlogik selbst an einem verpassten Empfang
//                        mitschuld sein kann. Bewusst KEIN Timer-Interrupt
//                        (Serial aus einer echten ISR ist riskant) - simpler
//                        millis()-Vergleich reicht fuer eine sekundengenaue
//                        Begrenzung, zusaetzlich abgesichert durch einen
//                        Fallback-Check in menu_handle_serial() (greift auch
//                        dann, wenn waehrend des gesamten Testfensters kein
//                        einziges Paket eintrifft). Abbruch per Backspace/
//                        ESC jederzeit moeglich (einzige Ausnahme vom
//                        "nichts stoert diese Routine"-Prinzip, bewusst in
//                        Kauf genommen). Ergebnis wird erst NACH Testende
//                        auf einen Schlag ausgegeben.
// -----------------------------------------------------------------------
// Version: 2.30.31      Generiert: 2026-09-09 (BUGFIX: Nutzer meldete
//                        kryptische Zeichen wie "[0H`l]" statt der echten
//                        SSID bei Probe Requests in Punkt 2. Ursache: die
//                        Positionswerte 37 (Probe Request) und 49 (Beacon/
//                        Probe Response) stammen aus print_pkt_header(),
//                        wo sie auf den KOMPLETTEN Rohpuffer INKLUSIVE der
//                        12 Byte langen RxControl-Kopfzeile kalibriert sind
//                        (12 RxControl + 24 MAC-Header + 1 = 37; +12 Beacon/
//                        ProbeResp-Fixfelder = 49). print_filtered_frame()
//                        bekommt aber "frame" = sniffer->buf, das schon OHNE
//                        die 12 RxControl-Byte beginnt (Frame Control direkt
//                        @ frame+0) - dieselben Positionswerte lasen dadurch
//                        systematisch 12 Byte zu weit und landeten mitten in
//                        nachfolgenden IEs (z.B. Supported Rates) statt in
//                        der SSID. Betraf nicht nur Probe Request, sondern
//                        ebenso Beacon/Probe-Response-SSIDs in Punkt 2. Fix:
//                        um die 12 Byte RxControl-Versatz korrigiert (25 fuer
//                        Probe Request, 37 fuer Beacon/Probe Response).
// -----------------------------------------------------------------------
// Version: 2.30.30      Generiert: 2026-09-09 (BUGFIX: Nutzer meldete, dass
//                        der Kanal-Lock aus v2.30.29 beim Verlassen des
//                        Menues nicht zurueckgesetzt wurde. Ursache: der
//                        Flood-Fix aus v2.30.28 (apply_live_filter() faengt
//                        Backspace/ESC bei hoher Paketrate selbst per
//                        Serial.peek()/Serial.read() ab, um trotz Paketflut
//                        reaktionsfaehig zu bleiben) ruft menu_enter_filter_
//                        criteria() DIREKT auf und konsumiert die Taste dabei
//                        schon - der normale Weg ueber menu_go_back() bzw.
//                        den ESC-Handler in menu_handle_serial() (wo die
//                        Kanal-Lock-Wiederherstellung liegt) wurde dadurch nie
//                        erreicht. channel_filter blieb dauerhaft auf den
//                        gesperrten Einzelkanal gesetzt, sobald das Verlassen
//                        waehrend einer Paketflut erfolgte (der Normalfall,
//                        da Punkt 2.1 mit aktivierten Datenrahmen ja genau
//                        dafuer gedacht ist). Fix: filter_channel_unlock_if_
//                        active() zusaetzlich direkt in diesem Schnellweg
//                        aufgerufen.
// -----------------------------------------------------------------------
// Version: 2.30.29      Generiert: 2026-09-09 (Nutzerwuensche: (1) NEUER
//                        Punkt 2.3 "MAC-Adresse nachschlagen" - MAC eingeben,
//                        Ergebnis zeigt ob bekannt, Rolle (AP/Client), bei
//                        AP die SSID, bei Client den AP, an dem er
//                        angemeldet ist (neue Funktion lookup_mac(), neue
//                        Struct mac_lookup_result, neue States STATE_MAC_
//                        LOOKUP_INPUT/_RESULT). (2) Kanal-Lock fuer Punkt 2.1:
//                        ist die eingegebene MAC bekannt, sperrt menu_enter_
//                        filter_live() den Scan automatisch auf deren Kanal
//                        (wiederverwendet die vorhandene channel_filter-
//                        Einstellung aus Punkt e/3) und stellt beim
//                        Verlassen (Backspace UND ESC) den vorherigen Wert
//                        wieder her - inkl. Schutz gegen Ueberschreiben der
//                        Sicherung bei einem Strg+O-Refresh waehrend der
//                        Lock schon aktiv ist. (3) RAM-FIX: ie_frame_subtype_
//                        name()/action_category_name()/action_specific_name()
//                        gaben ihre ca. 70 Klartextnamen bisher als rohe
//                        String-Literale zurueck - auf dem ESP8266-Arduino-
//                        Core landet das im RAM statt im Flash. Umgestellt
//                        auf das im Sketch bereits etablierte strcpy_P()-
//                        aus-PROGMEM-Muster (wie ie_element_name()), macht
//                        die ueber die letzten Versionen aufgelaufene ca.
//                        1KB RAM-Mehrbelegung rueckgaengig (Nutzer-Feedback
//                        anhand des Compiler-Reports).
// -----------------------------------------------------------------------
// Version: 2.30.28      Generiert: 2026-09-09 (Nutzer-Feedback zu Punkt 2:
//                        (1) Action-Frames werden jetzt nach Category/Action
//                        aufgeschluesselt (z.B. "Action (Block Ack: ADDBA
//                        Request)" statt nur "Action") - Category @
//                        frame+24, Action @ frame+25, direkt hinter dem
//                        24-Byte-MAC-Header, bereits im Management-Puffer
//                        vorhanden. Vollstaendige IEEE-802.11-Kategorien-
//                        Tabelle, Action-Namen bisher nur fuer Block Ack
//                        (ADDBA Request/Response, DELBA) - Grundlage fuer
//                        die Klaerung der "chattenden" Tuya-Steckdose.
//                        (2) Ausgabeformat verdichtet: keine feste 24-Zeichen-
//                        Auffuellung mehr vor dem Label (verschwendete auf
//                        einem Handybildschirm massiv Platz), Einheit "dBm"
//                        entfaellt (Zahlenwert ist selbsterklaerend).
//                        (3) SSID wird jetzt bei JEDEM Rahmen angezeigt, auch
//                        wenn er selbst keine SSID mitfuehrt (Data/Action/
//                        Null etc.) - Nachschlag im bereits vorhandenen AP-
//                        Cache (find_ap_index_by_bssid()) anhand TA/RA.
//                        Bewusst in Kauf genommen, dass Zeilen dadurch laenger
//                        werden (expliziter Nutzerwunsch).
//                        (4) BUGFIX: bei sehr hoher Paketrate (aktivierte
//                        Datenrahmen) kam loop()/menu_handle_serial() kaum
//                        noch zum Zug - Backspace/ESC/Strg+O liefen ins Leere,
//                        die Ausgabe liess sich nicht mehr stoppen. Fix:
//                        apply_live_filter() (laeuft bei einer Paketflut am
//                        haeufigsten) schaut jetzt selbst zuerst auf
//                        Serial.available() und reagiert sofort, statt auf
//                        die naechste loop()-Iteration zu warten.
// -----------------------------------------------------------------------
// Version: 2.30.27      Generiert: 2026-09-07 (BUGFIX: Nutzer meldete anhand
//                        einer OpenBK-geflashten Tuya-Steckdosen-Aufzeichnung
//                        (Punkt 2.1-Live-Ausgabe), dass "Null (kein Payload)"-
//                        Datenrahmen faelschlich mit "[offen/versteckt]"
//                        (der SSID-Kennzeichnung fuer Beacon/Probe) markiert
//                        wurden. Ursache: Subtyp-ZAHLEN ueberschneiden sich
//                        zwischen den drei Frametypen (Data-Subtyp 4 "Null"
//                        = derselbe Zahlenwert wie Management-Subtyp 4
//                        "Probe Request", Data-Subtyp 8 "QoS Data" = derselbe
//                        wie Management-Subtyp 8 "Beacon"). print_filtered_
//                        frame() prüfte bisher nur frame_subtype, nicht
//                        zusaetzlich frame_type == 0 (Management) - dadurch
//                        wurde bei jedem Null-Data-Frame faelschlich versucht,
//                        an der SSID-Byteposition eine SSID zu lesen. Fix:
//                        frame_type als zusaetzlicher Parameter, Bedingung
//                        jetzt "frame_type == 0 && (frame_subtype==4||5||8)".
// -----------------------------------------------------------------------
// Version: 2.30.26      Generiert: 2026-09-07 (KOMPILIERUNGSFIX zu 2.30.25:
//                        "expected ')' before ';' token" in
//                        draw_filter_criteria_screen(). Reiner Tippfehler,
//                        keine strukturelle Fehlerklasse wie die letzten
//                        beiden Fixes: bei den Checkbox-Zeilen fuer
//                        Management/Control/Data (Punkte 5/6/7) fehlte
//                        jeweils die schliessende Klammer von printf_P() -
//                        "chk(filter_mgmt_mask != 0);" statt korrekt
//                        "chk(filter_mgmt_mask != 0));" (eine Klammer fuer
//                        chk(), eine fuer printf_P(), siehe die
//                        unmittelbar davorstehende, korrekte Zeile fuer
//                        Beacons als Vorlage). Alle uebrigen chk()-Aufrufe
//                        im Sketch automatisiert auf Klammernbalance
//                        geprueft - nur diese drei Zeilen betroffen.
// -----------------------------------------------------------------------
// Version: 2.30.25      Generiert: 2026-09-07 (KOMPILIERUNGSFIX zu 2.30.24:
//                        "filter_has_mac was not declared in this scope".
//                        Gleiche Fehlerklasse wie der watchlist_sighting-Fix
//                        in v2.30.22, nur bei einer Variable statt einem Typ:
//                        die filter_*-Variablen standen im Watchlist-UI-
//                        Abschnitt weiter UNTEN im Sketch, apply_live_filter()/
//                        print_filtered_frame() (direkt vor promisc_cb(),
//                        weiter OBEN im Sketch) griffen aber schon vorher
//                        darauf zu. Anders als bei Funktionen generiert
//                        Arduino keine automatischen Vorab-Deklarationen fuer
//                        globale Variablen - die muessen von sich aus vor
//                        ihrer ersten Verwendung in der Datei stehen. Fix:
//                        kompletter Filter-UI-Zustand-Block (Variablen +
//                        FILTER_*_MASK-Defines) nach ganz oben verschoben
//                        (direkt hinter #define ETH_MAC_LEN, vor watchlist_
//                        sighting/beaconinfo). Reiner Kompilierungsfix, keine
//                        Verhaltensaenderung.
// -----------------------------------------------------------------------
// Version: 2.30.24      Generiert: 2026-09-07 (FEATURE: Punkt 2 im
//                        Hauptmenue komplett neu - "Funkverkehr gezielt
//                        untersuchen" statt bisherigem reinen Rohdaten-
//                        Debug-Modus. Fuehrt jetzt in ein Untermenue mit
//                        zwei Zweigen: 2.1 Filter nach einer einzelnen
//                        MAC-Adresse (AP oder Client, Richtung abgehend/
//                        ankommend waehlbar) und 2.2 Filter nach Pakettyp
//                        ueber alle Geraete hinweg. Beide teilen sich einen
//                        gemeinsamen Checkbox-Kriterien-Bildschirm: Beacons,
//                        Probes (Request/Response einzeln waehlbar),
//                        Management/Control/Data (je mit Unterauswahl aller
//                        einzeln benannten Subtypen + einer "Sonstige/
//                        selten"-Sammel-Checkbox fuer PCF-Exoten/Reserved -
//                        die Live-Ausgabe nennt trotz Sammel-Checkbox immer
//                        den echten, spezifischen Subtyp-Namen). Kriterien
//                        bleiben nach Nutzerwunsch dauerhaft im RAM erhalten
//                        (auch nach Verlassen des Menues). Start per 's',
//                        laufende gefilterte Ausgabe zeigt TA -> RA, SSID
//                        (wo zuverlaessig lokalisierbar: Beacon/Probe
//                        Request/Probe Response), Kanal, RSSI. Backspace aus
//                        der laufenden Ausgabe fuehrt wie gewuenscht zurueck
//                        zu den Kriterien, nicht ins Hauptmenue.
//                        Technisch: ie_frame_subtype_name() um die
//                        vollstaendigen IEEE-802.11-2016-Tabellen fuer
//                        Control- und Data-Subtypen ergaenzt sowie die
//                        bisher als "unbekannt" gefuehrten Management-
//                        Subtypen 6/7/14/15 korrekt benannt (Timing
//                        Advertisement/Reserved/Action No Ack/Reserved).
//                        Neue Kernfunktion apply_live_filter() nutzt den
//                        802.11-Fakt, dass Adresse 2 IMMER die Sendestation
//                        (TA) und Adresse 1 IMMER die Empfangsstation (RA)
//                        ist, unabhaengig von ToDS/FromDS und Frametyp -
//                        macht eine gesonderte ds-Fallunterscheidung fuer
//                        die Richtungspruefung ueberfluessig. Eingehaengt an
//                        zwei Stellen in promisc_cb() (Management-Zweig
//                        len==128 sowie der bisherige "sonstige Laenge"-
//                        Zweig, der VOR dem "frame_type!=2 -> return"-Sprung
//                        jetzt auch Control-Rahmen erfasst, die dort sonst
//                        unsichtbar geblieben waeren). STATE_DEBUG_LIVE
//                        (alter Punkt 2) bewusst NICHT entfernt, aber ueber
//                        die Tastatur nicht mehr erreichbar (siehe Kommentar
//                        beim enum MenuState) - Vollentfernung waere ein
//                        separater Aufraeum-Schritt.
// -----------------------------------------------------------------------
// Version: 2.30.23      Generiert: 2026-09-07 (BUGFIX: Nutzer meldete
//                        Phantom-Eintraege "3333ff..." in allen Listen seit
//                        dem Vortag, die eindeutig echten Clients zuordenbar
//                        waren, auf dem Router aber weiterhin nur unter der
//                        originalen MAC gefuehrt wurden. Ursache: 33:33:xx:
//                        xx:xx:xx ist der IEEE-reservierte IPv6-Multicast-
//                        Adressbereich (u.a. "Solicited-Node"-Multicast
//                        33:33:ff:xx:xx:xx bei IPv6 Neighbor Discovery/MLD -
//                        die letzten 3 Byte stimmen dabei oft mit der echten
//                        Client-MAC ueberein, daher die eindeutige Zuordnung).
//                        parse_data() (ds==2, AP->Client) sollte solche
//                        Gruppenadressen als "station" ausschliessen, die
//                        dortige Pruefung deckte mit dem festen Muster
//                        broadcast3={33,33,00} aber NUR den Fall drittes
//                        Byte=00 ab, nicht 0xFF (Solicited-Node) - die
//                        Adresse rutschte dadurch faelschlich als echter
//                        Client durch. Sichtbar erst "seit gestern", weil der
//                        Zweig-Tausch aus v2.30.19 diesen Pfad ueberhaupt erst
//                        regelmaessig durchlaufen laesst. Fix: die drei
//                        fehleranfaelligen Einzelmuster (broadcast1/2/3)
//                        ersetzt durch dasselbe Gruppenadress-Bit-Prinzip wie
//                        bei is_valid_ap_bssid() (IEEE 802: LSB des ersten
//                        Oktetts = Gruppen-/Multicast-/Broadcast-Adresse) -
//                        deckt jetzt lueckenlos ALLE Multicast-Muster ab.
//                        broadcast1/2/3-Arrays entfernt (RAM-Ersparnis, da
//                        ungenutzt geworden). Wirkung: betrifft nur die
//                        Klassifizierung innerhalb ds==2 - bei erkannter
//                        Gruppenadresse faellt der Code auf Adresse 3
//                        (urspruengliche Quelle) zurueck, GENAU wie es die
//                        Absicht von v2.30.19 schon war. Es werden dadurch
//                        keine neuen Clients erzeugt und keine bestehenden
//                        Eintraege umbenannt/ueberschrieben - lediglich die
//                        bisher faelschlich erzeugten "3333ff..."-Phantom-
//                        Eintraege entstehen ab jetzt nicht mehr neu (bereits
//                        vorhandene alte Phantom-Eintraege in clients_known[]
//                        bleiben bis zum naechsten manuellen Cleanup/Reboot
//                        stehen, werden aber nicht mehr aktualisiert).
// -----------------------------------------------------------------------
// Version: 2.30.22      Generiert: 2026-09-07 (KOMPILIERUNGSFIX zu 2.30.21:
//                        "watchlist_sighting does not name a type". Ursache:
//                        Arduino generiert Funktionsprototypen automatisch
//                        und fuegt sie weit oben im Sketch ein - die Struct
//                        watchlist_sighting (Rueckgabetyp von find_freshest_
//                        watchlist_sighting()) stand dort noch nicht zur
//                        Verfuegung, da sie bisher direkt bei der Funktion
//                        weiter unten im Sketch definiert war. Gleiche
//                        Fehlerklasse, die im Sketch bei clientinfo/
//                        beaconinfo bereits bekannt und dort korrekt geloest
//                        ist (Struct-Definition ganz oben, vor jeglicher
//                        Funktion). Fix: watchlist_sighting-Definition dort-
//                        hin verschoben (direkt vor beaconinfo), Funktions-
//                        implementierung selbst unveraendert an ihrer
//                        bisherigen Stelle belassen. Keine Verhaltens-
//                        aenderung, reiner Kompilierungsfix.
// -----------------------------------------------------------------------
// Version: 2.30.21      Generiert: 2026-09-07 (BUGFIX/AENDERUNG Watchlist:
//                        Nutzer meldete einen Watchlist-Eintrag, der trotz
//                        live sichtbarem Beacon (Menue 1) dauerhaft als
//                        uralt/"out" angezeigt wurde. Ursache: die MAC war
//                        schon immer AUSSCHLIESSLICH ein AP (eigener
//                        Mobilhotspot), nie ein Client - die Watchlist
//                        (Menue 4-Anzeige UND die Rueckkehr-Signalisierung
//                        in watchlist_background_check()) durchsuchte ueber
//                        find_freshest_entry_for_station() aber ausschliess-
//                        lich clients_known[], AP-Sichtungen (aps_known[])
//                        wurden nie beruecksichtigt. Neue Funktion find_
//                        freshest_watchlist_sighting() durchsucht jetzt
//                        BEIDE Quellen und liefert die jeweils juengste
//                        Sichtung - Watchlist-Eintraege greifen damit
//                        rollentransparent, egal ob die MAC als Client oder
//                        als AP auftritt. find_freshest_entry_for_station()
//                        selbst bleibt unveraendert (weiterhin fuer die
//                        Client-Roaming-Logik in format_client_cell() etc.
//                        zustaendig, wo eine AP-Sichtung fachlich nicht
//                        sinnvoll waere). MAC-Ausgabe in Menue 4 nutzt jetzt
//                        einheitlich watchlist[i].mac statt clients_known
//                        [slot].station.
// -----------------------------------------------------------------------
// Version: 2.30.20      Generiert: 2026-09-05 (AENDERUNG nach Nutzerwunsch,
//                        Menue 3a: "out" stand bisher in der AP-Spalte
//                        selbst und verdeckte dadurch, von welchem AP aus
//                        ein Client den WLAN-Bereich komplett verlassen
//                        hat. Jetzt (analog zum Wechsel-Hinweis ">N" aus
//                        v2.30.16): die AP-Spalte zeigt auch bei "out"
//                        weiterhin die eigene AP-Nummer/den eigenen Kanal;
//                        "out" wandert stattdessen in den sonst bei einem
//                        inaktiven Eintrag ungenutzten Trend-Platz.
//                        Gemeinsame Variable fuer Wechsel-/Out-Hinweis im
//                        Trend-Platz von "switch_suffix" in "trend_slot_
//                        suffix" umbenannt (wird jetzt fuer beide Faelle
//                        verwendet). Betrifft format_client_cell()
//                        (Zuweisung von trend_slot_suffix im station_gone-
//                        Zweig) sowie print_client_cell()/print_client_
//                        cell_ap_mode() (AP-/Kanal-Spalte zeigt bei "out"
//                        nicht mehr "out", sondern wie im Normalfall die
//                        eigene Nummer).
// -----------------------------------------------------------------------
// Version: 2.30.19      Generiert: 2026-09-04 (Zwei Bugfixes aus derselben
//                        Nutzer-Untersuchung ["?"-Wechselziel bei frischen
//                        Client-Eintraegen]:
//                        (1) find_freshest_entry_for_station() verglich
//                        last_heard-Rohwerte DIREKT (>), ohne Bezug zu
//                        "now" - exakt dieselbe Fehlerklasse wie der
//                        ap_before()-Bug aus v2.30.18. Nach einem millis()-
//                        Ueberlauf (~49,7 Tage Laufzeit) kann ein uralter,
//                        nie aufgeraeumter Geister-Eintrag (delete_old_
//                        clients() laeuft NICHT automatisch, nur manuell
//                        ueber das Cleanup-Menue) einen scheinbar GROSSEN
//                        last_heard-Rohwert haben und faelschlich als
//                        "aktueller" gelten als ein gerade eben frisch
//                        aktualisierter Eintrag - der frische Eintrag
//                        zeigte dann faelschlich ">?" (gewechselt zu
//                        unbekanntem Ziel), obwohl er selbst der wahre
//                        aktuellste Eintrag war. Fix: wie bei ap_before()
//                        jetzt ueber "now - last_heard" mit demselben
//                        ueberlaufsicheren 32-Bit-Cast vergleichen. Neuer
//                        Parameter "now" an allen 5 Aufrufstellen ergaenzt.
//                        (2) parse_data(), Fall ds==2 (ToDS=0/FromDS=1,
//                        AP->Client): "||" zwischen drei "stimmt NICHT
//                        ueberein"-Pruefungen ist so gut wie immer wahr,
//                        der ueberwiegend genommene Zweig verwendete
//                        dadurch praktisch IMMER Adresse 3 als "station" -
//                        nach 802.11-Standard ist bei ds==2 aber Adresse 1
//                        die tatsaechliche Ziel-Client-Adresse. Muss "&&"
//                        heissen; Zweige entsprechend getauscht.
// -----------------------------------------------------------------------
// Version: 2.30.18      Generiert: 2026-09-04 (BUGFIX Menue 3 AP-Liste,
//                        Sortierung nach Age: Nutzer beobachtete eine
//                        "kaputte" Sortierreihenfolge - eine Gruppe der
//                        aeltesten Eintraege (57k/59k/60k/"old") stand
//                        entgegen aufsteigender Sortierung ganz OBEN statt
//                        unten, waehrend der Rest der Liste (0 bis 51k)
//                        korrekt aufsteigend sortiert war. Ursache:
//                        ap_before() verglich bei AP_SORT_AGE bisher die
//                        last_heard-Rohwerte DIREKT (ohne Bezug zu "now"),
//                        in der (im Kommentar explizit begruendeten, aber
//                        falschen) Annahme, das sei aequivalent zu einem
//                        Alters-Vergleich. Das gilt nur, solange millis()
//                        nicht zwischenzeitlich ueberlaeuft (alle ~49,7
//                        Tage Laufzeit) - danach haben vor dem Ueberlauf
//                        zuletzt gehoerte Eintraege einen (scheinbar)
//                        GROSSEN last_heard-Rohwert nahe 0xFFFFFFFF,
//                        waehrend danach gehoerte Eintraege einen kleinen
//                        Rohwert haben. Der direkte Vergleich sortierte die
//                        VOR dem Ueberlauf gehoerten (tatsaechlich aeltesten)
//                        Eintraege dadurch faelschlich ganz nach vorn. Die
//                        Age-ANZEIGE selbst war davon nie betroffen (nutzt
//                        bereits ueberlaufsicheres "now - last_heard").
//                        Fix: ap_before()/sort_aps() bekommen jetzt "now"
//                        als Parameter und vergleichen wie das laengst
//                        korrekte Client-Pendant (client_before(),
//                        SORT_LASTSEEN) ueber "now - last_heard" mit
//                        demselben ueberlaufsicheren 32-Bit-Cast wie bei
//                        der Altersanzeige. Betrifft beide sort_aps()-
//                        Aufrufer (Menue 3, ntfy-Anhang).
// -----------------------------------------------------------------------
// Version: 2.30.17      Generiert: 2026-09-04 (BUGFIX Menue 3 AP-Liste:
//                        Nutzer beobachtete, dass ein AP-Eintrag grau
//                        (=stale) blieb, obwohl er nachweislich (Age-Spalte
//                        zeigte einen kleinen, frischen Wert) laengst
//                        wieder online war. Ursache: print_mac() resettet
//                        die VT100-Farbe NUR zuverlaessig, wenn die
//                        aufrufende Stelle das selbst uebernimmt (per
//                        vt_sgr()/vt_color_reset() VOR und NACH dem Aufruf,
//                        wie es print_client_cell()/print_client_cell_
//                        ap_mode() schon immer tun) - bei einer stalen
//                        Zeile (restore_sgr="90") "restauriert" print_mac()
//                        intern bewusst auf Grau statt komplett
//                        zurueckzusetzen, in Erwartung eines eigenen
//                        Resets durch den Aufrufer danach. print_ap_cell()
//                        tat das bisher NICHT - die Grau-Faerbung "leckte"
//                        dadurch aus einer stalen Zeile mit randomisierter/
//                        beobachteter MAC in die NAECHSTE Zeile hinein, die
//                        selbst (weil frisch) gar keine eigene Farbausgabe
//                        ausloeste und die geleakte Farbe deshalb einfach
//                        uebernahm. Betraf typischerweise mehrere Zeilen in
//                        Folge, je nachdem wie die MAC-Adressen zufaellig
//                        verteilt waren. Fix: print_ap_cell() rahmt seine
//                        print_mac()-Aufrufe jetzt genauso explizit ein wie
//                        das Client-Pendant (an beiden Stellen: Hersteller-
//                        Anzeige-Zweig und normaler Einzelspalten-Zweig).
// -----------------------------------------------------------------------
// Version: 2.30.16      Generiert: 2026-09-02 (AENDERUNG nach Nutzer-
//                        Beobachtung, Multi-AP-Ueberwachung mehrerer APs
//                        derselben SSID: bisher zeigte ein Eintrag, der zu
//                        einem anderen AP gewechselt ist, in der AP-Spalte
//                        NUR das Wechselziel (">N") - die eigene AP-
//                        Zugehoerigkeit dieses Eintrags war dadurch nicht
//                        mehr erkennbar, man konnte also nicht sehen, VON
//                        WELCHEM AP aus gewechselt wurde. Jetzt (Nutzer-
//                        Vorschlag): die AP-Spalte zeigt bei einem
//                        gewechselten Eintrag weiterhin die EIGENE AP-
//                        Nummer/den eigenen Kanal (wie im Normalfall);
//                        das Wechselziel ">N" wandert stattdessen in den
//                        sonst bei einem gewechselten/inaktiven Eintrag
//                        ungenutzten Trend-Platz (wo sonst "^+N"/"vN"
//                        steht). Bleibt automatisch so lange dort stehen,
//                        bis DIESER Eintrag (dieser AP) selbst wieder der
//                        aktuellste wird - ergibt sich direkt aus der
//                        bestehenden Freshest-Logik, kein zusaetzlicher
//                        Zustand noetig. Betrifft format_client_cell()
//                        (neuer trend_slot_suffix-Mechanismus im Trend-Platz)
//                        sowie print_client_cell()/print_client_cell_
//                        ap_mode() (AP-/Kanal-Spalte zeigt bei Wechsel
//                        nicht mehr ">N", sondern wie im Normalfall die
//                        eigene Nummer). "out"-Anzeige unveraendert.
// -----------------------------------------------------------------------
// Version: 2.30.15      Generiert: 2026-09-02 (1) enable_return_pulse
//                        (Menue 4, Rueckkehr-Signalisierung, Taste 'p')
//                        war bisher reine Session-Variable - auf
//                        Nutzerwunsch jetzt in settings.cfg persistiert
//                        (save_all_settings()/load_all_settings()) und im
//                        Werkseinstellungen-Reset beruecksichtigt.
//                        (2) BUGFIX (Nutzer-Beobachtung, Menue 3a Kombi-
//                        Modus "Sx"): wechselt ein Client von AP-A zu AP-B
//                        (gleiche SSID), bleiben zwei getrennte Eintraege
//                        bestehen - der aeltere (AP-A) zeigt korrekt ">B"
//                        (gewechselt), der aktuellste (AP-B) den normalen
//                        Status. Bisher kippten aber BEIDE Eintraege
//                        gleichzeitig auf "out", sobald der AP-B-Eintrag
//                        (der aktuellste) 600s alt wurde - der AP-A-Eintrag
//                        verlor damit seine eigentlich dauerhafte
//                        historische Information ">B" faelschlich zugunsten
//                        eines spaeteren, unabhaengigen Ereignisses. Fix in
//                        format_client_cell(): Reihenfolge der Pruefungen
//                        getauscht - ein nicht-aktuellster Eintrag zeigt
//                        jetzt IMMER ">N" (dauerhaft eingefroren), "out"
//                        kann nur noch der jeweils aktuellste Eintrag einer
//                        Station werden. Betrifft automatisch alle drei
//                        Anzeigevarianten (Einzel-AP/Kombiniert/Multi-AP),
//                        da sie sich format_client_cell() teilen.
// -----------------------------------------------------------------------
// Version: 2.30.14      Generiert: 2026-09-02 (NEU: Menue 3a bekommt einen
//                        "unsortiert"-Sortiermodus wie Menue 3 - Taste 'u'
//                        (set_sort_field(SORT_NONE)), zeigt die Clients in
//                        Registrierungsreihenfolge (= Array-Reihenfolge in
//                        clients_known[], unveraendert durch sort_clients()
//                        bei SORT_NONE, analog sort_aps()/AP_SORT_NONE).
//                        Neuer Enum-Wert SORT_NONE=3 bewusst ANGEHAENGT
//                        statt bestehende Werte umzunummerieren (sort_field
//                        wird als Zahl in settings.cfg/Listen-Schnappschuss-
//                        Dateien persistiert). Die "#"-Platznummer vor jeder
//                        Zeile bleibt automatisch korrekt (ist immer der
//                        echte clients_known-Index, unabhaengig von der
//                        Sortierreihenfolge).
//                        Da 'u' jetzt "unsortiert" ist, wandert die
//                        Aktualisierungsrate (list_refresh_sec) von 'u'/'d'
//                        auf '+'/'-' - analog zu Menue 3, das aus demselben
//                        Grund schon laenger '+'/'-' nutzt.
//                        AUSSERDEM (Nutzer-Vorgabe): Standard-Aktualisier-
//                        ungsintervall jetzt einheitlich 10s statt 15s -
//                        betrifft list_refresh_sec, ssid_select_refresh_sec,
//                        watchlist_refresh_sec, sowohl als globale Variablen-
//                        Startwerte (greift, wenn keine settings.cfg
//                        existiert) als auch im expliziten Werkseinstellungen-
//                        Reset (perform_factory_reset()).
// -----------------------------------------------------------------------
// Version: 2.30.13      Generiert: 2026-09-02 (BUGFIX Mausefalle - erster
//                        realer Fang zeigte zwei Fehler:
//                        (1) "Client: " blieb in der Datei leer - der
//                        print_mac()-Aufruf dort vergass den dritten
//                        Parameter (&file), lief dadurch mit dem Default-
//                        Parameter (&Serial) und schrieb die MAC auf die
//                        Konsole statt in die Datei.
//                        (2) Nach den echten Information Elements standen
//                        zwei unsinnige Zusatzeintraege ("ID 0 SSID Laenge
//                        0" und "ID 3 ... Laenge 1" ohne Inhalt) in der
//                        Datei. Ursache: legacy_length (RxControl) ist laut
//                        ESP8266-SDK nur bei sig_mode==0 (Legacy/Non-HT-
//                        Frame) die tatsaechliche Framelaenge - bei
//                        sig_mode==1 (802.11n/HT-Format, von vielen
//                        modernen Smartphones auch fuer Management-Frames
//                        wie Probe Requests genutzt) ist legacy_length
//                        NICHT verlaesslich (haeufig 0), massgeblich ist
//                        dann stattdessen HT_length (im RxControl-Struct
//                        bereits vorhanden, bisher nirgends benutzt). Bei
//                        legacy_length==0 fiel reallen auf 0 zurueck, die
//                        Anzeige/Datei-Ausgabe vertraute dadurch dem vollen
//                        112-Byte-SDK-Puffer, dessen ungenutzter Rest noch
//                        Reste eines fruehereren, laengeren Frames enthielt
//                        - die wurden faelschlich als weitere IEs dekodiert.
//                        Neue gemeinsame Hilfsfunktion sniffer_frame_
//                        length() kapselt die sig_mode-Fallunterscheidung
//                        an einer Stelle statt vier einzelnen Kopien;
//                        betrifft alle vier Stellen, die bisher direkt
//                        rx_ctrl.legacy_length gelesen haben (Mausefalle,
//                        Beacon-Analyse, Client-Frame-Analyse x2 - Beacon-
//                        und Client-Analyse hatten denselben latenten
//                        Fehler, nur bisher nicht bemerkt/getriggert).
// -----------------------------------------------------------------------
// Version: 2.30.12      Generiert: 2026-09-01 (BUGFIX Mausefalle: nach
//                        frametrap_client_arm() wurde sofort redraw_ssid_list()
//                        aufgerufen, was den Bildschirm augenblicklich
//                        loeschte und neu zeichnete - JEDE Rueckmeldung von
//                        frametrap_client_arm() (Erfolg "Falle scharf..." genauso
//                        wie eine Fehlermeldung wie "bereits scharf" oder
//                        "Maximal erreicht") wurde dadurch sofort wieder
//                        weggewischt, bevor sie sichtbar war. Nutzer konnte
//                        dadurch nicht erkennen, ob/warum eine schon anders
//                        markierte Watchlist-MAC (z.B. Rueckkehr-Ueber-
//                        wachung) beim Scharfmachen zusaetzlich markiert
//                        wurde oder nicht. Fix: kein sofortiges Redraw mehr
//                        nach dem Scharfmachen - die Meldung bleibt stehen,
//                        die Liste zeichnet sich beim naechsten normalen
//                        Auto-Refresh von selbst neu.
//                        BEKANNTES, NOCH OFFENES VERHALTEN (kein Bugfix,
//                        strukturell bedingt): Ausbleibende Faenge trotz
//                        Anmeldevorgang liegen vermutlich am staendigen
//                        Kanal-Hopping (default 100ms/Kanal, ca. 7% Dauer
//                        auf einem gegebenen Kanal bei bis zu 13 Kanaelen)
//                        kombiniert damit, dass ein Client bei einer
//                        Anmeldung an ein bereits bekanntes Netz oft gar
//                        keinen Probe Request sendet (direkte Authentication
//                        moeglich, da Kanal/BSSID schon bekannt). Moegliche
//                        Abhilfe (Kanal-Pinning waehrend scharfer Fallen)
//                        mit Nutzer noch nicht final abgestimmt.
// -----------------------------------------------------------------------
// Version: 2.30.11      Generiert: 2026-09-01 (NEU: "Mausefalle" - faengt
//                        den naechsten Probe Request eines schon
//                        autorisierten/bekannten Clients ein, unabhaengig
//                        vom Menue-Zustand und ohne Zeitlimit (ueberlebt
//                        auch einen Reboot). Aufruf in Menue 3a (STATE_
//                        SSID_LIST, Geraeteliste): "wp"+Zahl+Enter statt
//                        "w"+Zahl+Enter (Tasteneingabe erweitert - 'p'
//                        wird nur akzeptiert, solange nach 'w' noch keine
//                        Ziffer eingegeben wurde; Backspace nimmt 'p' und
//                        'w' einzeln zurueck).
//                        Architektur bewusst auf der bestehenden Watchlist
//                        aufgesetzt statt einer eigenen Zielliste: ein
//                        Watchlist-Eintrag mit " (wait PR)" in der
//                        Beschreibung ist "scharf" (frametrap_client_arm()/
//                        watchlist_entry_is_trapped()). Steht die MAC
//                        schon auf der Watchlist (z.B. zur Rueckkehr-
//                        Ueberwachung), wird der Marker an den bestehenden
//                        Text angehaengt statt ihn zu ueberschreiben. Bis
//                        zu FRAMETRAP_CLIENT_MAX_PENDING=5 Fallen gleichzeitig
//                        scharf (Nutzer-Vorgabe), frametrap_client_arm() verweigert
//                        weitere.
//                        promisc_cb() macht im Probe-Request-Zweig weiterhin
//                        NUR memcmp/memcpy (Lehre aus dem Stack-Panic-Fix in
//                        v2.30.10 - Datei-I/O im Callback waere riskant) -
//                        pro Fang wird ein malloc(112)-Puffer aus einem
//                        Pool von 5 Slots (frametrap_client_catches[]) belegt.
//                        menu_periodic() verarbeitet fertige Faenge im
//                        Hauptloop (frametrap_client_process_catch()): dekodiert
//                        MAC-Header+IEs (gleiche Logik wie die Konsolen-
//                        Client-Analyse) und schreibt sie in eine eigene
//                        Datei "/PR_<MAC 12 Zeichen>_<SSID gekuerzt>.txt" -
//                        SSID-Kuerzung auf genau 10 Zeichen (alnum/_/-
//                        gefiltert, wie beim bestehenden Speichern-Filter),
//                        da LittleFS nur 32 Byte fuer den kompletten Pfad
//                        erlaubt (siehe Kommentar bei auto_save_on_overflow).
//                        Datei-Header mit Zeitstempel (current_unix_time_
//                        with_tz(), wie beim bestehenden ntfy-Zeitstempel-
//                        Format) falls NTP synchronisiert, sonst Hinweis
//                        "kein NTP".
//                        Nach der Verarbeitung: frametrap_client_disarm_or_remove()
//                        entfernt NUR den Marker aus der Beschreibung (nicht
//                        den ganzen Eintrag) - bestand vorher schon ein
//                        anderer Text (z.B. Rueckkehr-Ueberwachung), bleibt
//                        der Eintrag mit diesem Text erhalten; war der
//                        Eintrag nur fuer die Falle angelegt, wird er beim
//                        Leerwerden komplett geloescht. Kein automatisches
//                        Timeout - Fallen bleiben scharf bis manuellem
//                        Loeschen ueber den bestehenden Watchlist-Loeschen-
//                        Dialog (Menue 4), der jetzt dieselbe neue
//                        remove_watchlist_entry()-Grundoperation nutzt.
// -----------------------------------------------------------------------
// Version: 2.30.10      Generiert: 2026-08-31 (BUGFIX: Absturz "Panic ...
//                        __yield" bei aktiviertem Vendor-Lookup in Menue 3a
//                        analysiert und behoben. Ursache war NICHT primaer
//                        die Vendor-Lookup-Aufrufkette selbst (die ist mit
//                        ca. 400-500 Byte moderat tief), sondern mehrere
//                        "uint16_t matches[MAX_CLIENTS_TRACKED]"-Arrays
//                        (MAX_CLIENTS_TRACKED=1000, also 2000 Byte) als
//                        STACK-lokale Variablen in genau den Funktionen,
//                        aus denen der Vendor-Lookup aufgerufen wird -
//                        allein eins dieser Arrays belegt die Haelfte des
//                        gesamten ESP8266-"cont"-Stacks (Standard 4096
//                        Byte) fuer die gesamte Funktionslaufzeit,
//                        wodurch fuer die ohnehin knappe Vendor-Lookup-
//                        Kette darunter kein Puffer mehr blieb. Betroffen
//                        und jetzt auf malloc()/free() umgestellt (Heap
//                        statt Stack, wie beim vergleichbaren Vorbild
//                        blockBuf/buffer in der VendorLookup-Klasse selbst,
//                        kein dauerhafter RAM-Verbrauch):
//                        - menu_enter_ssid_list(): matches[] (2000 Byte)
//                        - menu_enter_ssid_list_combined(): matches[] +
//                          ap_matches[] (2150 Byte)
//                        - menu_enter_ssid_list_multi(): matches[]
//                          (2000 Byte)
//                        - build_notif_attachment() (ntfy, dort Vendor-
//                          Lookup zwar schon deaktiviert, aber dieselben
//                          Arrays bleiben ein Risiko fuer andere tiefe
//                          Aufrufe): indices[] (2000 Byte), all_matches[] +
//                          ap_matches[] (2150 Byte)
//                        Alle vier Funktionen haben jetzt NULL-Checks nach
//                        malloc() mit sauberem Abbruch (inkl. Freigabe
//                        bereits allozierter Puffer) sowie free() an jedem
//                        Ausstiegspunkt.
// -----------------------------------------------------------------------
// Version: 2.30.9       Generiert: 2026-08-31 (BUGFIX Webserver-Seiten:
//                        (1) "/dateien": Banner-Bild wurde per "margin:0
//                        auto" zentriert, waehrend Ueberschrift/Dateitabelle
//                        darunter ganz normale, linksbuendige Block-
//                        Elemente sind - bei einem Banner, der schmaler als
//                        der 600px-Container ist, rueckte er dadurch
//                        sichtbar gegenueber der restlichen Ausgabe nach
//                        rechts ein. Fix: Banner jetzt ebenfalls linksbuendig
//                        (kein Auto-Margin mehr) - teilt sich jetzt dieselbe
//                        linke Kante mit Ueberschrift/Tabelle.
//                        (2) Startseite ("/"): Logo passte sich auf manchen
//                        mobilen Browsern nicht an die tatsaechliche
//                        Bildschirmgroesse an, weil reines 100vh/100vw die
//                        ein-/ausblendende Adressleiste nicht mitverfolgt
//                        (die sichtbare Hoehe aendert sich, 100vh bleibt
//                        aber auf dem urspruenglichen Wert stehen). Fix:
//                        100dvh/100dvw ("dynamic viewport") als Override
//                        nach dem bisherigen vh/vw-Wert ergaenzt (vh/vw
//                        bleibt als Fallback fuer aeltere Browser stehen,
//                        die dvh/dvw nicht kennen).
//                        NOCH OFFEN: Absturz bei aktiviertem Vendor-Lookup
//                        in Menue 3a - aus reiner Codepruefung nicht
//                        eindeutig lokalisiert, wartet auf Exception-
//                        Meldung/Geraeteanzahl vom Nutzer.
// -----------------------------------------------------------------------
// Version: 2.30.8       Generiert: 2026-08-31 (AENDERUNG nach Nutzer-Test:
//                        Client-Frame-Analyse (Menue 3a) wartete bisher NUR
//                        auf einen Probe Request des gewaehlten Clients -
//                        Nutzer-Beobachtung zeigte aber, dass ein bereits
//                        verbundener, aktiver Client praktisch KEINE Probe
//                        Requests mehr sendet (die werden nur beim aktiven
//                        Scannen vor/waehrend einer Verbindung gesendet;
//                        die regelmaessig zurueckgesetzte Age-Time in der
//                        Geraeteliste kommt von normalen Datenframes).
//                        Erfassung wartet jetzt auf das NAECHSTE Paket
//                        JEDER Art dieses Clients (Datenframe ODER
//                        Management-Frame, je nachdem was zuerst eintrifft).
//                        Datenframes liefern (SDK-bedingt) nur 36 statt 112
//                        Byte und enthalten keine Information Elements -
//                        die Anzeige zeigt in dem Fall MAC-Header (inkl.
//                        richtungsabhaengiger Adress-Beschriftung Client/AP/
//                        BSSID, QoS Control bei QoS-Data-Subtypen) plus die
//                        rohen (meist WPA2/3-verschluesselten) Nutzdaten-
//                        Byte. Nur bei einem tatsaechlichen Probe Request
//                        bleibt die bisherige volle IE-Dekodierung (SSID/
//                        Rates/RSN/Vendor) erhalten. Neu: ie_frame_subtype_
//                        name() fuer Klartextnamen beliebiger Frametyp/
//                        Subtyp-Kombinationen in der generischen Anzeige.
// -----------------------------------------------------------------------
// Version: 2.30.7       Generiert: 2026-08-31 (BUGFIX: STATE_CLIENT_ANALYSIS
//                        aus v2.30.6 war faelschlich auf denselben Zahlenwert
//                        (25) gesetzt wie das schon laenger existierende
//                        STATE_HTTP_SERVER (seit v2.30.0) - beim Einfuegen
//                        wurde nur STATE_BEACON_ANALYSIS=24 als Referenz
//                        geprueft, nicht die komplette Enum-Liste. Folge:
//                        waehrend des Wartens auf einen Probe Request
//                        (Menue 3a, "w"+Zahl) loeste JEDER folgende
//                        Tastendruck faelschlich den "if (menu_state ==
//                        STATE_HTTP_SERVER) { http_server_stop(); ... }"-
//                        Block in menu_handle_serial() aus (Zahlenwert-
//                        Kollision) - WLAN/Promiscuous-Mode wurden
//                        neu aufgesetzt und es sprang sofort ins
//                        Hauptmenue zurueck, statt auf das Ergebnis zu
//                        warten. STATE_CLIENT_ANALYSIS bekommt jetzt den
//                        naechsten freien Wert (28).
// -----------------------------------------------------------------------
// Version: 2.30.6       Generiert: 2026-08-30 (NEU: Client-Frame-Analyse
//                        (Probe Request) in Menue 3a (STATE_SSID_LIST,
//                        Geraeteliste einer gewaehlten SSID), Taste
//                        "w"+Zahl+Enter - analog zur Beacon-Frame-
//                        Rohanalyse aus v2.29.17, jetzt fuer Clients statt
//                        APs. Faengt den naechsten Probe-Request-Frame des
//                        gewaehlten Clients ab und zerlegt ihn genauso
//                        vollstaendig: MAC-Header (Frame Control inkl.
//                        Flags, Adressfelder, Sequence Control) sowie alle
//                        Information Elements (u.a. die gesuchte SSID,
//                        Supported Rates, Vendor-Specific inkl. OUI-
//                        Hersteller-Lookup). Bewusst NUR Probe Requests
//                        (kein Daten-Frame-Modus) - auf Nutzer-Ruecksprache,
//                        da Datenframes ohnehin verschluesselt sind und
//                        keine auswertbaren Klartext-IEs enthalten. Neuer
//                        Zustand STATE_CLIENT_ANALYSIS, eigener 112-Byte-
//                        Zwischenpuffer (malloc()/free(), kein dauerhafter
//                        RAM-Verbrauch, exakt wie beim Beacon-Pendant),
//                        20s-Timeout. Da Probe Requests MAC-randomisiert
//                        oder nur bei aktivem Scannen gesendet werden,
//                        kann die Erfassung je nach Geraet laenger dauern
//                        oder erfolglos bleiben - Hinweistext dazu im
//                        Wartebildschirm. Rueckkehr per Backspace/ESC fuehrt
//                        zurueck in dieselbe Geraeteliste (nicht wie beim
//                        Beacon-Pendant zur AP-Liste), da hier aus der
//                        Geraeteliste heraus gestartet wird. Selektion des
//                        Clients ueber eine neu eingefuehrte Nummerierung
//                        ("#") vor jeder Zeile in Menue 3a, Modus 1
//                        (einzelner AP) - Modi 2/3 (SSID-Buendelung/Multi-
//                        AP) sowie Watchlist/ntfy bleiben unveraendert
//                        (print_client_cell() selbst nicht angefasst, die
//                        Nummer wird nur in menu_enter_ssid_list() davor
//                        gedruckt). ie_element_name()/rsn_cipher_suite_
//                        name()/rsn_akm_suite_name()/decode_rsn_ie() aus
//                        der Beacon-Analyse werden unveraendert mit-
//                        genutzt (frametyp-unabhaengig). Reiner IE-Offset-
//                        Unterschied zum Beacon: Probe-Request-Frames
//                        haben KEINE festen Beacon-Felder (Timestamp/
//                        Intervall/Capability) - IEs beginnen direkt ab
//                        Byte 24 statt 36.
// -----------------------------------------------------------------------
// Version: 2.30.5       Generiert: 2026-08-30 (Nutzer-Feedback zu Punkt 7:
//                        (1) Die automatische Heap-Pruefung vor Upload-
//                        Annahme aus v2.30.4 wurde auf Wunsch des Nutzers
//                        WIEDER ENTFERNT (blockierte eine Funktion nach
//                        eigenem Ermessen des Nutzers unerwuenscht).
//                        Neuer Messwert vom Nutzer: Absturz bei ca. 7 KB
//                        freiem Heap, laeuft einwandfrei ab ca. 11 KB
//                        (durch eigene Reduzierung von MAX_APS_TRACKED auf
//                        150 erreicht). HTTP_UPLOAD_BUFLEN=128 und
//                        "Connection: close" aus v2.30.3/2.30.4 bleiben
//                        bestehen, da sie kein Verhalten blockieren,
//                        sondern nur RAM sparen.
//                        (2) BUGFIX: Absturz beim Beenden des Servers UEBER
//                        DEN BROWSER (Link "/beenden"), waehrend Beenden
//                        ueber die serielle Konsole einwandfrei lief.
//                        Ursache: http_handle_stop_request() rief bisher
//                        direkt http_server_stop() auf, welches u.a.
//                        "delete g_http_server" ausfuehrt - der Aufruf lief
//                        aber selbst als Methode/Callback VON g_http_server
//                        (ausgeloest durch dessen eigenes handleClient()).
//                        Wird das Objekt darin geloescht, arbeitet
//                        handleClient() beim Rueckkehren mit bereits
//                        freigegebenem Speicher weiter - Absturz. Der
//                        serielle Weg war nicht betroffen, weil das
//                        Beenden dort ausserhalb jedes Server-
//                        Methodenaufrufs passiert (siehe menu_handle_
//                        serial()). Fix: "/beenden" setzt jetzt nur noch
//                        das Flag g_http_stop_requested; menu_periodic()
//                        ruft http_server_stop() danach GETRENNT auf, erst
//                        NACHDEM g_http_server->handleClient() bereits
//                        vollstaendig zurueckgekehrt ist.
//                        (3) Boot-Logo (hlogo.jpg) ragte auf manchen
//                        Bildschirmen ueber den sichtbaren Bereich hinaus.
//                        CSS ueberarbeitet: html/body jetzt height:100%
//                        und overflow:hidden, das Bild bekommt zusaetzlich
//                        object-fit:contain sowie width/height:auto neben
//                        max-width/max-height - dadurch wird es IMMER
//                        proportional in den sichtbaren Bereich eingepasst,
//                        unabhaengig von Seitenverhaeltnis/Aufloesung.
//                        (4) NEU: Einstellungen > AP-Modus (Taste 'c' im
//                        Einstellungsmenue). Punkt 7 (HTTP-Datei-Server)
//                        kann jetzt wahlweise einen EIGENEN Access Point
//                        aufspannen (eigene SSID/Passwort, konfigurierbar
//                        in diesem neuen Untermenue, Punkt 1 = Ein/Aus-
//                        Schalter) statt sich mit einem bestehenden Router
//                        zu verbinden - praktisch ohne Router in
//                        Reichweite. Default: aus (unveraendertes
//                        Verhalten wie bisher). WLAN-Init/Teardown folgen
//                        auch hier der vollstaendigen Sequenz (WiFi.mode
//                        (WIFI_OFF) -> delay -> WiFi.mode(WIFI_AP) -> delay
//                        -> WiFi.softAP()), Promiscuous-Mode-Wiederherstellung
//                        beim Beenden ist fuer AP- und STA-Fall identisch,
//                        nur der WLAN-Teardown selbst unterscheidet sich
//                        (softAPdisconnect() statt disconnect()).
// -----------------------------------------------------------------------
// Version: 2.30.4       Generiert: 2026-08-30 (RAM-FIX zu Punkt 7, Teil 2:
//                        Nutzer meldete einen harten Absturz beim Upload
//                        (Exception 29 "StoreProhibited", excvaddr=0x0,
//                        epc1 im ROM-Adressbereich 0x4000d...) trotz
//                        v2.30.3. Einordnung: Exception 29 mit Zieladresse
//                        0 und einer Programmadresse im ROM-Bereich ist
//                        das typische Fehlerbild, wenn dem WLAN/TCP-Stack
//                        (SDK/lwIP) selbst der Speicher ausgeht - das
//                        passiert TIEF unterhalb des eigenen Sketch-Codes
//                        und laesst sich dort nicht per if-Abfrage
//                        abfangen, nur durch ausreichend Heap-Reserve
//                        vermeiden. Massnahmen in diesem Schritt:
//                        (1) HTTP_UPLOAD_BUFLEN weiter von 256 auf 128
//                        Byte gesenkt (weitere ~130 Byte Ersparnis).
//                        (2) NEU: HTTP_MIN_FREE_HEAP_FOR_UPLOAD (14000
//                        Byte) - vor Annahme eines Uploads wird der freie
//                        Heap geprueft; ist er zu knapp, wird der Upload
//                        sauber mit Fehlermeldung abgelehnt statt einen
//                        Absturz zu riskieren (Nutzer-Messwerte: 8 KB
//                        stuerzt ab, 20 KB laeuft einwandfrei - 14000 Byte
//                        liegt bewusst mit Sicherheitsabstand dazwischen,
//                        naeher an der bestaetigt funktionierenden Seite).
//                        (3) NEU: jede Antwort des HTTP-Servers sendet
//                        jetzt "Connection: close" (http_close_after_
//                        response()) statt die HTTP/1.1-Verbindung offen
//                        zu halten - Keep-Alive-Verbindungen binden beim
//                        ESP8266WebServer zusaetzliche TCP-Strukturen im
//                        RAM, die sich ueber mehrere Seitenaufrufe hinweg
//                        aufsummieren koennen, bevor der Browser sie von
//                        sich aus schliesst.
//                        WICHTIGER HINWEIS AN DEN NUTZER (kein Code): Die
//                        beiden statischen Tracking-Arrays clients_known[]
//                        (MAX_CLIENTS_TRACKED=1000) und aps_known[]
//                        (MAX_APS_TRACKED=250) sind mit Abstand der groesste
//                        permanente RAM-Posten des gesamten Sketches und
//                        bleiben unabhaengig von Punkt 7 immer vollstaendig
//                        reserviert. Sollte der freie Heap trotz dieser
//                        Massnahmen weiterhin knapp bleiben, waere eine
//                        Reduzierung dieser beiden Konstanten der mit
//                        Abstand wirksamste Hebel - das aendert aber die
//                        maximale Tracking-Kapazitaet und wurde deshalb
//                        bewusst NICHT eigenmaechtig vorgenommen.
// -----------------------------------------------------------------------
// Version: 2.30.3       Generiert: 2026-08-30 (RAM-FIX zu Punkt 7: Nutzer
//                        meldete einen Absturz beim Datei-Upload, wenn der
//                        freie Heap bei ca. 8 KB lag (ab ca. 20 KB lief es
//                        fehlerfrei). Ursache/Fix: HTTP_UPLOAD_BUFLEN, der
//                        von ESP8266WebServer intern per uint8_t-Array in
//                        der HTTPUpload-Struktur reservierte Upload-
//                        Zwischenpuffer, ist standardmaessig 2048 Byte
//                        gross - das laesst sich per Macro-Definition VOR
//                        dem Include von ESP8266WebServer.h auf einen
//                        kleineren Wert absenken (die Bibliothek prueft
//                        intern "#ifndef HTTP_UPLOAD_BUFLEN"). Jetzt auf
//                        256 Byte gesetzt (~1,75 KB Ersparnis gegenueber
//                        dem Standardwert), bei Bedarf im #define am
//                        Sketch-Anfang weiter absenkbar (z.B. 128 Byte).
//                        Funktional aendert sich dadurch nichts - der
//                        WRITE-Callback (http_handle_upload_data()) wird
//                        nur entsprechend oefter mit kleineren Haeppchen
//                        aufgerufen, jedes davon wird weiterhin sofort und
//                        gestreamt in die LittleFS-Datei geschrieben.
//                        Zusaetzlich: Heap-Diagnose (freier Heap bei
//                        Upload-Start/-Ende) ueber debugLog() ergaenzt -
//                        nur bei aktivem Debug-Modus (Strg+D) sichtbar,
//                        fuer den Fall dass bei sehr knappem Heap weitere
//                        Fehlersuche noetig wird.
//                        HINWEIS (kein Code, sondern IDE-Einstellung):
//                        Falls die verwendete Entwicklungsumgebung Zugriff
//                        auf "Tools > lwIP Variant" bietet, kann zusaetzlich
//                        die Einstellung "v2 Lower Memory" (statt "Higher
//                        Bandwidth") weiteren Heap freigeben - der TCP/IP-
//                        Stack selbst reserviert dort separat von der
//                        Sketch-Ebene Empfangspuffer, worauf der Sketch-
//                        Code keinen Einfluss hat.
// -----------------------------------------------------------------------
// Version: 2.30.2       Generiert: 2026-08-30 (BUGFIX zu v2.30.0/2.30.1:
//                        Punkt 7 (HTTP-Datei-Server) war im Browser gar
//                        nicht oder nur mit sehr hoher Paketverlustrate
//                        erreichbar (per Dauerping bestaetigt). Ursache:
//                        die Kanal-Hopping-Logik im Hauptloop (springt
//                        normalerweise fuers Sniffing der Reihe nach durch
//                        alle 14 Kanaele) lief unveraendert weiter, auch
//                        waehrend Punkt 7 aktiv war - sie ist an keinen
//                        Menuestatus gebunden, weil sie bisher nur mit dem
//                        Promiscuous-Sniffing zu tun hatte. Waehrend der
//                        HTTP-Server aber per WiFi.begin() fest mit einem
//                        Router auf dessen einem Kanal verbunden ist, hat
//                        wifi_set_channel() den Funkchip laufend auf einen
//                        anderen Kanal umgeschaltet und damit die
//                        bestehende TCP-Verbindung/den Traffic praktisch
//                        pausiert. Fix: der komplette Kanalwechsel-Block
//                        in loop() (sowohl der initiale wifi_set_channel()
//                        beim (Neu-)Start der aeusseren Schleife als auch
//                        der Wechsel bei should_hop) wird jetzt uebersprungen,
//                        solange menu_state == STATE_HTTP_SERVER ist -
//                        waehrenddessen gibt es wegen des deaktivierten
//                        Promiscuous-Sniffings ohnehin nichts zu scannen.
//                        Sonst keine Aenderung an v2.30.1.
// -----------------------------------------------------------------------
// Version: 2.30.1       Generiert: 2026-08-30 (BUGFIX zu v2.30.0: /dateien
//                        (und die Startseite bei vorhandenem hlogo.jpg)
//                        zeigten im Browser eine leere weisse Seite, obwohl
//                        der Server Daten sendete. Ursache: send(200,
//                        "text/html", "") mit anschliessenden sendContent()-
//                        Aufrufen setzt den Content-Length-Header auf 0
//                        (weil der an send() uebergebene Body-String leer
//                        ist) - der Browser liest dann genau 0 Byte und
//                        stellt nichts dar, obwohl die eigentlichen Daten
//                        per sendContent() noch hinterhergeschickt werden.
//                        Fix: server->setContentLength(CONTENT_LENGTH_
//                        UNKNOWN) VOR jedem send(200, "text/html", "")
//                        mit nachfolgendem gestreamtem Inhalt (betrifft
//                        http_handle_root() und http_handle_files_page()) -
//                        dadurch schaltet der Server auf Chunked Transfer
//                        Encoding um, was beliebig viele nachfolgende
//                        sendContent()-Aufrufe erlaubt. Sonst keine
//                        Aenderung an v2.30.0.
// -----------------------------------------------------------------------
// Version: 2.30.0       Generiert: 2026-08-30 (NEU: HTTP-Datei-Server,
//                        Punkt 7 im Hauptmenue. Nutzt den durch v2.29.19
//                        frei gewordenen RAM fuer einen zweiten,
//                        browserbasierten Zugang zum Flash-Dateihandling
//                        (bisher nur ueber Punkt 6 seriell moeglich).
//                        UMSETZUNG - Ressourcenschonend/risikoarm:
//                        - ESP8266WebServer wird NICHT global instanziiert,
//                          sondern erst beim Betreten von Punkt 7 per
//                          "new" angelegt und beim Verlassen sofort wieder
//                          per "delete" freigegeben (g_http_server-Zeiger,
//                          NULL wenn inaktiv) - kostet also im normalen
//                          Sniffing-Betrieb keinerlei zusaetzliches RAM,
//                          genau wie vom Nutzer gefordert.
//                        - Dateitransfer (Up-/Download) laeuft komplett
//                          gestreamt: Downloads ueber server->streamFile()
//                          direkt aus LittleFS, Uploads ueber die
//                          HTTPUpload-Callbacks chunkweise direkt in eine
//                          LittleFS-Datei geschrieben. Es wird nirgends
//                          eine komplette Datei im RAM gepuffert.
//                        - WLAN-Zugangsdaten: es werden bewusst KEINE
//                          neuen Zugangsdaten-Felder angelegt, sondern die
//                          bereits vorhandenen notif_wifi_ssid/
//                          notif_wifi_pass (Einstellungen > Benachrichtigung)
//                          wiederverwendet - identisches Netz wird ja
//                          ohnehin schon fuer den ntfy-Versand genutzt.
//                          Sind diese leer, bricht Punkt 7 mit einer
//                          Fehlermeldung ab (kein WLAN konfiguriert).
//                        - Promiscuous-Mode wird beim Starten des Servers
//                          GENAUSO vollstaendig heruntergefahren und beim
//                          Beenden GENAUSO vollstaendig neu aufgebaut wie
//                          bei sync_ntp_time()/notif_send_now() (identische
//                          Befehlsreihenfolge: wifi_promiscuous_enable
//                          (disable) -> wifi_set_opmode(STATION_MODE) ->
//                          wifi_set_channel() -> wifi_set_promiscuous_rx_cb()
//                          -> wifi_promiscuous_enable(enable)). Die
//                          WLAN-Verbindung selbst nutzt ebenfalls die
//                          bewaehrte vollstaendige Init-Sequenz (WiFi.mode
//                          (WIFI_OFF) -> delay -> WiFi.mode(WIFI_STA) ->
//                          delay -> WiFi.begin()), da unvollstaendige
//                          Umschaltungen in der Vergangenheit schon zu
//                          einem "tauben" Funkchip gefuehrt hatten (siehe
//                          Kommentare bei sync_ntp_time()).
//                        - Neuer Menuepunkt 7 ("HTTP-Datei-Server") und
//                          neuer Zustand STATE_HTTP_SERVER. Waehrend der
//                          Server aktiv ist, beendet EIN BELIEBIGER
//                          Tastendruck auf der seriellen Konsole den
//                          Server sauber (WLAN trennen, Promiscuous-Mode
//                          wiederherstellen, zurueck ins Hauptmenue) -
//                          unabhaengig vom Browser, also auch dann nutzbar,
//                          wenn kein Geraet mehr im Netz erreichbar ist.
//                        - Startseite ("/"): zeigt /hlogo.jpg an, FALLS
//                          diese Datei im Flash liegt, und wartet dann per
//                          JavaScript auf einen beliebigen Tastendruck
//                          (zusaetzlich auch auf Klick/Touch, da nicht
//                          jedes Zugriffsgeraet eine Tastatur hat), bevor
//                          sie zur Dateiverwaltungsseite "/dateien"
//                          weiterschaltet. Liegt /hlogo.jpg nicht vor,
//                          wird sofort direkt zu "/dateien" weitergeleitet.
//                        - Alle Seiten AUSSER der Startseite zeigen am
//                          oberen Rand /banner.jpg an, FALLS diese Datei
//                          im Flash liegt.
//                        - Dateiverwaltungsseite "/dateien": Liste aller
//                          LittleFS-Dateien mit Groesse, Download- und
//                          Loeschen-Link sowie einem Upload-Formular.
//                          Bereits ueber Punkt 6 als "geschuetzt"
//                          markierte Dateien (is_file_protected()) werden
//                          auch hier vor dem Loeschen bewahrt (Loeschen-
//                          Link wird fuer sie nicht angezeigt, ein direkter
//                          Aufruf von /delete wird serverseitig zusaetzlich
//                          zurueckgewiesen) - dieselbe Schutzliste wie bei
//                          Punkt 6, keine zweite Pflege noetig.
// -----------------------------------------------------------------------
// Version: 2.29.19      Generiert: 2026-08-30 (GROSSE RAM-OPTIMIERUNG:
//                        systematische, skriptgestuetzte Umstellung ALLER
//                        Text-Ausgaben im gesamten Sketch auf F()/PSTR()
//                        (Serial.print/println/printf, aber auch
//                        f.print/println/printf beim Dateispeichern und
//                        client.print/printf beim ntfy-Versand). Ausloeser
//                        war der RAM-Fund bei v2.29.17/18 (siehe dort) -
//                        eine Bestandsaufnahme des GESAMTEN Sketches zeigte,
//                        dass das kein Einzelfall war: 732 von 805
//                        Text-Ausgaben (~27.400 von ~30.300 Byte) lagen im
//                        RAM statt im Flash, quer durch den ganzen Sketch
//                        seit vielen Versionen. Automatisiert (Python-
//                        Skript, keine manuelle Einzelbearbeitung bei
//                        dieser Menge) umgestellt: Serial.print("x") ->
//                        Serial.print(F("x")), Serial.println("x") ->
//                        Serial.println(F("x")), Serial.printf("x", ...) ->
//                        Serial.printf_P(PSTR("x"), ...) - jeweils
//                        gleichbedeutend fuer f./client./out->-Aufrufe.
//                        Nach der Umstellung: 0 verbleibende unverpackte
//                        Text-Ausgaben. Zeilenzahl, Klammernbilanz-Differenz
//                        und Anfuehrungszeichen-Paarigkeit vor/nach Diff
//                        identisch verifiziert - reine RAM-Optimierung,
//                        keine Verhaltensaenderung. Erwarteter Gewinn:
//                        mehrere Kilobyte zusaetzlich freier RAM (siehe
//                        Nutzer-Test fuer den tatsaechlichen Wert).
// -----------------------------------------------------------------------
// Version: 2.29.18      Generiert: 2026-08-30 (RAM-BUGFIX zu v2.29.17:
//                        die Beacon-Frame-Analyse hatte den freien Heap
//                        beim Nutzer von ~5.960 auf ~2.920 Byte einbrechen
//                        lassen - schon direkt nach dem Boot, ganz ohne
//                        die Funktion je aufzurufen (per zwei Vergleichs-
//                        Screenshots bestaetigt). Ursache gefunden und
//                        durch Nachrechnen bestaetigt: alle neuen String-
//                        Literale in v2.29.17 (~3.400 Byte geschaetzt,
//                        passt zur beobachteten Differenz) lagen im RAM
//                        statt im Flash, weil F()/PSTR() vergessen wurden -
//                        der restliche Sketch nutzt das nur an 2 Stellen,
//                        ist an dieser Stelle also kein Einzelfall, aber
//                        bei so viel neuem Beschreibungstext auf einen
//                        Schlag eben deutlich spuerbar. Fix: alle
//                        Serial.println()/print() mit Text jetzt mit F(),
//                        alle Serial.printf() auf Serial.printf_P()+PSTR()
//                        umgestellt (Format-String wandert in den Flash,
//                        die eigentlichen Werte/Argumente bleiben normale
//                        Variablen). Die drei Klartextnamen-Nachschlage-
//                        funktionen (ie_element_name(), rsn_cipher_suite_
//                        name(), rsn_akm_suite_name()) liefern ihren Text
//                        jetzt per strcpy_P() aus PROGMEM in einen kleinen
//                        wiederverwendeten statischen Puffer (32/24 Byte je
//                        Funktion) statt direkte RAM-Strings zurueckzugeben.
//                        Funktionalitaet/Anzeige selbst unveraendert -
//                        reine RAM-Optimierung ohne Verhaltensaenderung.
// -----------------------------------------------------------------------
// Version: 2.29.17      Generiert: 2026-08-29 (NEU: Beacon-Frame-Rohanalyse
//                        in Punkt 3, "w"+Zahl+Enter. Zerlegt den naechsten
//                        eintreffenden Beacon des gewaehlten (aktiven) APs
//                        Bit-/Byte-genau: kompletter MAC-Header (Frame
//                        Control inkl. aller Flags, Adressfelder, Sequence
//                        Control), feste Beacon-Felder (Timestamp, Beacon-
//                        Intervall, Capability Info inkl. aller Bits), und
//                        alle Information Elements (SSID, Supported Rates,
//                        DSSS-Kanal, RSN/WPA2 inkl. Cipher-/AKM-Suiten,
//                        Vendor-Specific inkl. OUI-Hersteller-Lookup, alle
//                        anderen zumindest mit Klartextname+Rohbytes -
//                        nichts wird verschwiegen). BSSID-Hersteller per
//                        bestehender vendorCache_lookup_or_search() mit
//                        aufgeloest. Kein dauerhaft reservierter RAM: der
//                        112-Byte-Zwischenpuffer wird erst beim Start der
//                        Erfassung per malloc() angelegt und direkt nach
//                        der Anzeige wieder freigegeben (neuer Zustand
//                        STATE_BEACON_ANALYSIS). Erfassung laeuft
//                        asynchron im Promiscuous-Callback (nur memcmp
//                        gegen die Ziel-BSSID + memcpy, keine Wartezeit
//                        blockierend) mit 20s-Timeout, ueberwacht aus
//                        menu_periodic(). SDK-Puffergrenze von 112 Byte
//                        (Hardware-/SDK-seitig, nicht umgehbar) wird bei
//                        Ueberschreitung ehrlich als solche gekennzeichnet.
//                        Kernfunktionen bewusst eigenstaendig (kein Eingriff
//                        in Menue 3a) und ohne AP-Array-Abhaengigkeit
//                        aufgebaut, um spaeter aus Menue 3a heraus
//                        wiederverwendbar zu sein.
// -----------------------------------------------------------------------
// Version: 2.29.16      Generiert: 2026-08-29 (RUECKBAU: der in 2.29.11
//                        eingefuehrte Platzhalter-Mechanismus fuer AP-
//                        Eintraege ohne eigenen Beacon ("...wartet auf
//                        Beacon", ensure_ap_index(), AP_NO_BEACON_FLAG)
//                        wurde komplett wieder entfernt. Grund: bei
//                        schwachen/entfernten Nachbar-Netzen (laengerer
//                        Beacon-Frame -> hoehere Fehlerrate bei niedrigem
//                        SNR als bei kurzen Client-Frames) kann es
//                        Stunden dauern, bis der erste echte Beacon
//                        eintrifft - durch einen Vergleich mit einem
//                        parallel laufenden Geraet auf v2.29.7 bestaetigt
//                        (dieselben APs loesten sich dort nach Stunden
//                        sauber auf, kein grundsaetzlicher Bug, nur reine
//                        Signalphysik). Der Platzhalter blieb so lange
//                        sichtbar haengen und blaehte die Liste mit
//                        SSID-losen Eintraegen auf. Einfacher und identisch
//                        zum bewaehrten Verhalten vor Etappe 3: ein Client
//                        mit noch unbekannter BSSID bekommt einfach
//                        AP_IDX_NONE ("??"), bis der AP ganz regulaer ueber
//                        seinen eigenen Beacon entdeckt wird - kein
//                        Platzhalter-Eintrag, keine Sonderbehandlung beim
//                        Speichern/Laden. AP_CHANNEL_MASK zurueck auf
//                        0x7F. Die RAM-Ersparnis aus Etappe 3 (ap_idx
//                        statt bssid[6] im Client) bleibt unangetastet
//                        bestehen. Die is_valid_ap_bssid()-Pruefung (u.a.
//                        fuer den ds==3/WDS-Fall aus 2.29.15) bleibt
//                        ebenfalls bestehen - verhindert weiterhin, dass
//                        ungueltige BSSIDs zufaellig auf einen falschen
//                        echten AP-Eintrag matchen koennten.
// -----------------------------------------------------------------------
// Version: 2.29.15      Generiert: 2026-08-28 (BUGFIX: dauerhaft
//                        haengenbleibende "...wartet auf Beacon"-
//                        Platzhalter (vom Nutzer entdeckt: exakt dieselben
//                        zwei APs blieben ueber mehrere Minuten und
//                        Sitzungen hinweg unaufgeloest, obwohl mehrere
//                        Clients dazu gesehen wurden). Ursache: bei
//                        ds==3 (4-Adress-/WDS-Modus, z.B. Mesh-/Repeater-
//                        Backhaul-Verkehr zwischen zwei AP-Radios) gibt es
//                        KEIN echtes BSSID-Feld im klassischen Sinn -
//                        parse_data() nahm dort naeherungsweise die
//                        Sender-Adresse (TA) des weiterleitenden Knotens
//                        als "bssid", die aber NIE mit der echten, im
//                        Beacon gesendeten BSSID uebereinstimmt. Das fuehrte
//                        zu einem AP-Platzhalter, der strukturell nie
//                        aufloesbar war - kein Channel-Hopping-Pech,
//                        sondern eine dauerhafte Fehlzuordnung. Diese
//                        Ungenauigkeit gab es schon vor Etappe 3, war aber
//                        unsichtbar (Client zeigte nur dauerhaft "??").
//                        parse_data() liefert fuer ds==3 jetzt bewusst eine
//                        ungueltige (all-null) BSSID - wird von
//                        is_valid_ap_bssid() automatisch abgefangen
//                        (AP_IDX_NONE/"??" statt Phantom-Platzhalter).
//                        Bereits VOR diesem Fix entstandene haengende
//                        Platzhalter in der aktuell laufenden Liste werden
//                        dadurch nicht rueckwirkend bereinigt - manuell per
//                        d+Nummer loeschen oder Geraet neu starten.
// -----------------------------------------------------------------------
// Version: 2.29.14      Generiert: 2026-08-28 (BUGFIX/Verbesserung zu
//                        Etappe 3: Platzhalter-APs (noch kein eigener
//                        Beacon empfangen, siehe ensure_ap_index()) zeigten
//                        Kanal 0 und RSSI 0, obwohl der Kanal durch das
//                        empfangene Client-Frame bereits sicher bekannt
//                        war (das Frame kam auf genau diesem Kanal an) -
//                        bei belebten, aber selten gebeaconten Kanaelen
//                        (Channel-Hopping trifft den exakten Beacon-
//                        Zeitschlitz seltener als Client-Verkehr) konnte
//                        das mehrere Minuten so bleiben. Platzhalter
//                        uebernehmen jetzt sofort Kanal+RSSI vom Client-
//                        Frame. Da channel==0 damit nicht mehr als
//                        Erkennungsmerkmal fuer "Platzhalter" taugt, neues
//                        RAM-neutrales Flag-Bit AP_NO_BEACON_FLAG (0x40,
//                        bisher freies Bit im channel-Byte, analog zu
//                        AP_OPEN_FLAG). AP_CHANNEL_MASK entsprechend von
//                        0x7F auf 0x3F erweitert (maskiert jetzt beide
//                        Flag-Bits aus). AUSSERDEM: save_current_lists()
//                        speichert unaufgeloeste Platzhalter nicht mehr
//                        als BEACON-Zeile (haette sonst beim naechsten
//                        Laden einen vermeintlich "bestaetigten" AP mit
//                        leerer SSID und verfaelschtem Kanalwert erzeugt).
// -----------------------------------------------------------------------
// Version: 2.29.13      Generiert: 2026-08-28 (BUGFIX zu Etappe 3 /
//                        v2.29.11: load_scenario_file() erzeugte beim
//                        Laden einer Sicherung fuer jede DEVICE-Zeile
//                        ohne (in der Datei noch nicht gelesene) passende
//                        BEACON-Zeile per ensure_ap_index() einen
//                        Platzhalter-AP ("...wartet auf Beacon"). Beim
//                        LIVE-Scan ist das sinnvoll (der echte Beacon
//                        kommt normalerweise Millisekunden spaeter), aber
//                        eine geladene Datei ist offline - der Platzhalter
//                        blieb dauerhaft leer und blaehte die AP-Liste mit
//                        jeder BSSID auf, die in der Datei nur per Client-/
//                        Datenframe auftauchte, aber nie einen eigenen
//                        BEACON-Eintrag hatte (vom Nutzer entdeckt: 100
//                        statt der tatsaechlich gesicherten 54 APs, u.a.
//                        mit verlorengegangenen SSID-Namen bei Sortierungs-
//                        Kollisionen durch die vielen Zusatzeintraege).
//                        load_scenario_file() liest die Datei jetzt in
//                        ZWEI Durchlaeufen: zuerst ALLE BEACON-Zeilen
//                        (aps_known[] vollstaendig aufgebaut), danach erst
//                        die DEVICE-Zeilen - per find_ap_index_by_bssid()
//                        aufgeloest (kein Platzhalter mehr), bei fehlendem
//                        Treffer bekommt der Client AP_IDX_NONE (genau wie
//                        vor 2.29.11 als "??" sichtbar). Das Dateiformat
//                        selbst ist unveraendert, nur der Lade-Ablauf.
// -----------------------------------------------------------------------
// Version: 2.29.12      Generiert: 2026-08-28 (BUGFIX zu Etappe 3 /
//                        v2.29.11: Client-Frames mit ungueltiger BSSID
//                        (all-null oder Multicast/Broadcast-Bit gesetzt,
//                        z.B. aus einem fehlerhaft geparsten Frame) haben
//                        ueber ensure_ap_index() einen Phantom-Platzhalter-
//                        AP in aps_known[] erzeugt - sichtbar als Eintrag
//                        mit leerer SSID, Kanal 0, RSSI 0 in der AP-Liste,
//                        optisch nicht von einem echten versteckten Netz
//                        zu unterscheiden. Neue Funktion
//                        is_valid_ap_bssid() (all-null/Multicast-Check)
//                        wird jetzt vor jedem ensure_ap_index()-Aufruf
//                        geprueft (Live-Erfassung UND load_scenario_file());
//                        bei ungueltiger BSSID bekommt der Client
//                        stattdessen AP_IDX_NONE (0xFF) statt eines
//                        Platzhalters. AUSSERDEM: echte Platzhalter (gueltige
//                        BSSID, aber noch kein Beacon erfasst - erkennbar an
//                        Kanal 0, gueltige WLAN-Kanaele sind 1-14) zeigen in
//                        der Liste jetzt "...wartet auf Beacon" statt leer,
//                        damit sie nicht mit einer echten leeren/versteckten
//                        SSID verwechselt werden koennen.
// -----------------------------------------------------------------------
// Version: 2.29.11      Generiert: 2026-08-27 (Etappe 3 des Luecken-
//                        basierten AP-Arrays: clientinfo.bssid[6] durch
//                        ap_idx (1 Byte, Index in aps_known[]) ersetzt -
//                        20 auf 15 Byte pro Client (-25%), bei
//                        MAX_CLIENTS_TRACKED=500 macht das 2.500 Byte
//                        statisch reserviertes RAM frei. Struktursicher,
//                        da seit 2.29.9/2.29.10 kein Loesch-Pfad mehr
//                        Clients mit Referenz auf einen wiederverwendbaren
//                        Slot zuruecklaesst. NEU: ensure_ap_index() loest
//                        eine BSSID zum aps_known[]-Index auf und legt bei
//                        Bedarf einen Platzhalter-Eintrag an (leere SSID),
//                        falls ein Client-Frame vor dem zugehoerigen
//                        Beacon erfasst wird - register_beacon()
//                        vervollstaendigt den Platzhalter automatisch,
//                        sobald der echte Beacon eintrifft, statt einen
//                        zweiten Eintrag anzulegen. Alle Stellen, die
//                        vorher per BSSID-memcmp nach Clients zu einem AP
//                        gesucht haben (Kaskaden-Loeschung, dev_count-
//                        Zaehlung, Sortierung nach Geraeteanzahl, Multi-/
//                        Kombi-AP-Auswahl, Watchlist-Umschaltungs-
//                        erkennung), vergleichen jetzt direkt per ap_idx -
//                        teils sogar von O(n)-Suche auf O(1)-Zugriff
//                        verbessert (print_client(), save_current_lists()).
//                        load_scenario_file() (Sicherung laden) loest
//                        DEVICE-Zeilen ueber ensure_ap_index() auf und
//                        prueft bei BEACON-Zeilen jetzt zuerst auf einen
//                        bereits vorhandenen (ggf. Platzhalter-)Eintrag,
//                        statt blind anzuhaengen.
// -----------------------------------------------------------------------
// Version: 2.29.10      Generiert: 2026-08-27 (Etappe 1+2 des Luecken-
//                        basierten aps_known[]-Arrays: Loeschen markiert
//                        Slots jetzt nur noch als frei (last_heard =
//                        AP_SLOT_FREE_MARKER 0xFFFFFFFF, bssid genullt)
//                        statt das Array zu verschieben - Indizes aller
//                        UEBRIGEN APs bleiben damit fuer ihre gesamte
//                        Lebensdauer stabil (Grundlage fuer die kuenftige
//                        Client->AP-Index-Referenz, Etappe 3, noch NICHT
//                        Teil dieser Version). register_beacon() sucht
//                        beim Anlegen eines neuen APs zuerst einen freien
//                        Slot, bevor angehaengt wird. delete_old_aps()
//                        kaskadiert jetzt ebenfalls auf zugehoerige
//                        Clients (wie delete_ap_by_index() seit 2.29.9),
//                        da beides manuell vom Nutzer ausgeloeste Vorgaenge
//                        sind. WICHTIG: aps_known_count ist ab jetzt nur
//                        noch der High-Water-Mark, NICHT mehr die echte
//                        Anzahl - dafuer aps_known_live_count(). Alle
//                        ~30 Stellen im Code, die aps_known[]/.bssid/.ssid
//                        lesen, wurden um einen ap_slot_free()-Check
//                        ergaenzt (Anzeige, Sortierung, Suche, ntfy-Export,
//                        Backup, Menue-Auswahl) - sonst haetten stehen-
//                        gebliebene Altwerte in einem freigegebenen Slot
//                        faelschlich matchen koennen.
// -----------------------------------------------------------------------
// Version: 2.29.9       Generiert: 2026-08-27 (NEU: Ueberlauf-Verhalten
//                        ueberarbeitet (Fall 1/2/3). Default fuer
//                        auto_offline_on_overflow jetzt true (statt false)
//                        - ohne bewusstes Abschalten wird bei Ueberlauf
//                        immer zuerst offline geschaltet, Liste bleibt
//                        erhalten (Fall 1, auch bei Auto-Save+Auto-Offline
//                        gleichzeitig, siehe 2.29.2-Vorrang-Regel). Ist
//                        Auto-Offline bewusst ausgeschaltet (Fall 2):
//                        Client-Ueberlauf entfernt weiterhin den aeltesten
//                        Eintrag; AP-Ueberlauf entfernt jetzt den ersten AP
//                        OHNE jemals gesehenen Client (0/0 in der
//                        Geraetezaehlung, find_first_empty_ap(), bricht
//                        beim ersten Treffer ab) statt des aeltesten APs -
//                        existiert kein 0/0-AP mehr, wird zwangsweise
//                        offline geschaltet und ueber ein neues, laengeres
//                        Signalmuster signal_forced_offline_pattern()
//                        (50ms an/100ms aus, dreimal) signalisiert, klar
//                        unterscheidbar vom normalen Ueberlauf-Signal
//                        signal_overflow_pattern() (20/100/20ms). Fall 3
//                        (Auto-Save an, Auto-Offline aus) unveraendert.
//                        AUSSERDEM: delete_ap_by_index() (manuelles
//                        Loeschen im Menue) entfernt jetzt zusaetzlich alle
//                        Clients, die per BSSID zu diesem AP gehoeren -
//                        bewusst NUR beim manuellen Loeschen, nicht bei
//                        delete_old_aps() (dort bleiben Clients weiterhin
//                        erhalten, da ein Alters-Timeout nicht zwingend
//                        heisst, dass der AP wirklich verschwunden ist).
// -----------------------------------------------------------------------
// Version: 2.29.8       Generiert: 2026-08-25 (NEU: Erkennung offener (un-
//                        verschluesselter) Access Points. Das Privacy-Bit
//                        aus dem Capability-Info-Feld des Beacons (2 Byte
//                        vor den Information-Elements, kostet keinen
//                        zusaetzlichen Lesezugriff auf neue Daten) wird ab
//                        jetzt ausgewertet und als Flag in Bit 7 von
//                        beaconinfo.channel abgelegt (AP_OPEN_FLAG) - RAM-
//                        neutral, da ESP8266 nur 2,4-GHz-Kanaele 1-14
//                        kennt und Bit 7 dafuer nie gebraucht wird. Anzeige:
//                        offene APs erscheinen mit runden statt eckigen
//                        Klammern um die SSID - in der Menue-3-AP-Liste
//                        (inkl. Vendor-Ansicht), der rohen Live-Debug-
//                        Ansicht (Punkt 2, Beacon- und Device-Zeilen) und
//                        im ntfy-Dateiexport der AP-Liste (nutzt dieselbe
//                        Funktion). BEWUSST unveraendert: das rohe Backup-
//                        Format (DEVICE:/BEACON:-Zeilen) - die Lade-Routine
//                        sucht dort nach eckigen Klammern, runde wuerden
//                        das Wiederherstellen brechen; das Flag-Bit reist
//                        aber unveraendert im Kanal-Byte mit und uebersteht
//                        Speichern/Laden ohne weiteres Zutun. Ueberall, wo
//                        der reine Kanalwert noetig ist (Anzeige), wird mit
//                        AP_CHANNEL_MASK ausmaskiert.)
// Version: 2.29.7       Generiert: 2026-08-25 (Menue 3a (Variante 1/2/3):
//                        db-Spalte zeigt jetzt IMMER den letzten registrierten
//                        Pegelwert, auch wenn ein Client den AP gewechselt hat
//                        oder "out" ist (Age > 600s). Der Wechsel-/Out-Hinweis
//                        (">N" bzw. "out") steht dafuer jetzt in der Kanal-Spalte
//                        (Variante 1, bisher "ch"-Spalte, zeigt normal weiter
//                        den Kanal) bzw. der AP-Spalte (Variante 2/3) - beide
//                        auf 3 Zeichen rechtsbuendig erweitert (Header
//                        entsprechend nachgezogen, auch im ntfy-Dateiexport).
//                        Taste 'i' (Ignore-Filter) blendet ab jetzt NUR NOCH
//                        AP-Wechsler aus, "out"-Eintraege bleiben sichtbar -
//                        dafuer neue eigene Funktion client_is_switched(),
//                        client_is_hideable() bleibt fuer die Aktiv-Zaehlung
//                        im AP-Overview (Menue 3) unveraendert (anderer
//                        Anwendungsfall, sollte "out" weiterhin nicht als
//                        aktiv zaehlen). Watchlist (Menue 4) hat eigene
//                        Formatierung und ist von alldem nicht betroffen.)
// Version: 2.29.6       Generiert: 2026-08-25 (Basis ist 2.29.4, NICHT 2.29.5 -
//                        die Puffer-Zusammenlegung aus 2.29.5 (RAM-Optimierung
//                        Etappe 1) wurde komplett verworfen, da sie Factory-
//                        Reset und Vendor-Lookup kaputt gemacht hat und die
//                        eigentliche Ursache im Code-Review nicht zu finden war
//                        (Ursache blieb ungeklaert). BUGFIX 1: signal_update()
//                        kannte den manuellen Test-Zustand (Taste 'b' in Hidden
//                        Settings) nicht und hat ihn im naechsten loop()-Durch-
//                        lauf sofort wieder ausgeschaltet ("sehr kurzer Impuls"
//                        statt Dauersignal). BUGFIX 2: geschuetzte Dateien
//                        liessen sich ohne Warnung loeschen, sobald show_hidden
//                        aktiv war ("h"+Enter) - die Schutzpruefung war
//                        faelschlich an "!show_hidden" gekoppelt, obwohl das
//                        nur die Sichtbarkeit in der Liste steuern sollte, nicht
//                        den Loeschschutz. Bug bestand bereits in 2.28.3, ist
//                        also unabhaengig von den letzten RAM-Aenderungen.
//                        AUSSERDEM: FIRMWARE_VERSION/FIRMWARE_BUILD_DATE waren
//                        seit 2.29.3 nicht mehr synchron zum Header-Kommentar
//                        - jetzt korrigiert.)
// Version: 2.29.4       Generiert: 2026-08-24 (Messintervall in adc_voltage_monitor()
//                        von 1s auf 15s erhoeht - 1s brachte nur geringfuegige Besserung
//                        bei der Empfangsproblematik, 15s reicht fuer die Akku-Ueberwachung
//                        voellig aus. 5s-Bestaetigungstakt der 3-fach-Pruefung entsprechend
//                        an das neue 15s-Intervall angepasst (Meldungstexte korrigiert).)
// Version: 2.29.3       Generiert: 2026-08-24 (BUGFIX 1: Auto-Save-Dateinamen bei Listen-
//                        ueberlauf ("Client_overflow_..."/"AP_overflow_...") waren zu lang
//                        fuer LittleFS (32-Byte-Pfadlimit auf dem ESP8266) - "Datei konnte
//                        nicht angelegt werden". Praefixe auf "Cl_ovfl"/"AP_ovfl" gekuerzt.
//                        BUGFIX 2: adc_voltage_monitor() rief bei jedem loop()-Durchlauf
//                        (>500x/s) analogRead() auf - stoerte seit 2.29.0 den interrupt-
//                        gesteuerten Promiscuous-Empfang (AP/Client-Erkennung verzoegert
//                        oder verpasst). Jetzt auf max. 1 Messung/Sekunde gedrosselt.)
// Version: 2.29.2       Generiert: 2026-08-23 (BUGFIX: Auto-Offline hat jetzt Vorrang, wenn
//                        beide Ueberlauf-Funktionen gleichzeitig aktiv sind. Doppelte Sicherung/
//                        doppelte Meldung bei Listenueberlauf behoben (waehrend einer laufenden
//                        Bearbeitung eintreffende Frames loesten faelschlich eine zweite Runde
//                        aus). Neues Dateinamensformat bei Auto-Save: Client_overflow/AP_overflow,
//                        danach NTP-Zeitstempel falls verfuegbar, sonst millis().
// Version: 2.29.1       Generiert: 2026-08-23 (BUGFIX: Auto-Save/Auto-Offline bei Listen-
//                        ueberlauf verursachten einen Reset - Ursache war blockierendes
//                        delay()/save_current_lists()/go_offline() DIREKT im zeitkritischen
//                        WLAN-Sniffer-Callback. Jetzt setzt der Callback nur noch ein leichtes
//                        Flag, die eigentliche Behandlung laeuft sicher im Hauptloop. Auto-Save
//                        leert jetzt beide Listen komplett (statt nur den aeltesten Eintrag zu
//                        entfernen); Auto-Offline laesst die Liste unangetastet. Neu: kurzes
//                        Signalmuster (20ms an/100ms aus/20ms an) auf dem Signalisierungspin bei
//                        Ausloesung. Neu: versteckte Testtasten C/P in Hidden Settings simulieren
//                        einen echten Client-/AP-Listenueberlauf (Zaehler hochsetzen statt Funktion
//                        direkt aufzurufen).
// Version: 2.29.0       Generiert: 2026-08-23 (NEU: ADC-Eingang zur Akkuspannungs-Ueberwachung.
//                        Einstellungen > b) neues Untermenue "ADC (Akkuspannung)" mit Einpunkt-
//                        Kalibrierung (zeigt Roh-ADC-Wert vor Eingabe der gemessenen Spannung in
//                        mV). Info-Menue zeigt die berechnete Spannung zweistellig hinter dem
//                        Komma. Kontinuierliche Ueberwachung (menu_periodic, unabhaengig vom
//                        Menuestatus) loest bei Unterschreiten von 3,20V nach 3-facher Bestaetigung
//                        im 5s-Abstand einmalig eine Sicherung wie beim GPIO0-Button aus, nur mit
//                        "ADC_" statt "Bttn_" als Dateinamens-Praefix.
// Version: 2.28.6       Generiert: 2026-08-23 (2.28.5s globale Scratch-Puffer (~1300 Byte
//                        dauerhafte RAM-Reservierung) zurueckgenommen - stattdessen Vendor-
//                        Lookup fuer den ntfy-Versand grundsaetzlich deaktiviert, unabhaengig
//                        von der Einstellung. Ist sie eingeschaltet, wird die Liste einfach so
//                        erzeugt, als waere sie aus. Keine RAM-Mehrkosten, kein Stack-Risiko.)
// Version: 2.28.5       Generiert: 2026-08-23 (STACK-Fix: "Panic core_esp8266_main.cpp:191
//                        __yield" beim ntfy-Versand mit Vendor-Lookup - der ntfy-Aufrufpfad
//                        (notif_send_now -> build_notif_attachment -> write_notif_*_section)
//                        ist 3 Ebenen tiefer als der Konsolenpfad, bevor er in dieselbe ohnehin
//                        knappe Vendor-Lookup-Kette eintaucht. Zwei 1200-Byte- sowie zwei
//                        100-Byte-Arrays lagen dabei als lokale Stack-Variablen ungenutzt auf
//                        dem Stack, waehrend darunter der Lookup lief - jetzt gemeinsam genutzte
//                        globale Scratch-Puffer (g_notifClientIdx/g_notifApIdx) statt Stack-Arrays.
// Version: 2.28.4       Generiert: 2026-08-23 (RAM-Fix Teil 4: debugLog() wertete seine
//                        String-Verkettungs-Argumente bisher IMMER aus (C++-Funktionsargumente
//                        werden vor dem Aufruf ausgewertet) - bei 34 Aufrufen ueber die gesamte
//                        VendorLookup-Klasse verteilt entstand so bei JEDEM Lookup unnoetiger
//                        Heap-Verbrauch, obwohl g_debugFlag im Normalbetrieb aus ist und die
//                        Nachricht sofort verworfen wurde. Jetzt Macro, das den Flag-Check VOR
//                        der Argumentauswertung macht - bei ausgeschaltetem Debug quasi kein
//                        Overhead mehr. Vermutete Ursache des Exception(28)-Crashs bei Vendor-Lookup.
// Version: 2.28.3       Generiert: 2026-08-23 (RAM-Fix Teil 3: drei permanent reservierte
//                        "static"-Puffer (512+256+512 Byte) in der Vendor-Lookup-Klasse waren
//                        die ganze Laufzeit belegt, obwohl nur waehrend eines tatsaechlichen
//                        Lookups (bzw. nur einmalig beim allerersten Boot) benoetigt - jetzt
//                        Stack (Boot-Fall) bzw. malloc/free (Laufzeit-Faelle). Heap-Schutzschwelle
//                        von unrealistischen 6000 auf 1800 Byte gesenkt (deckt sich mit der
//                        bestehenden Start-Schwelle). Diagnose-Ausgaben (freier Heap) ergaenzt.
// Version: 2.28.2       Generiert: 2026-08-22 (RAM-Fix Korrektur: 2.28.1s Ansatz - Zieldatei pro
//                        Zeile zu oeffnen/schliessen - war selbst die Ursache neuer Abstuerze
//                        (auch ohne Vendor-Lookup). Zurueck zu EINEM durchgehend offenen Datei-
//                        Handle wie vor 2.28.0; einziger Schutz gegen den eigentlichen Vendor-
//                        Lookup-Crash ist jetzt ein Heap-Check vor jedem Hersteller-Lookup)
// Version: 2.28.1       Generiert: 2026-08-22 (RAM-Fix-Versuch: MAC-Bereinigung ohne String+=;
//                        s. 2.28.2 fuer Korrektur des Datei-Handling-Ansatzes dieser Version)
// Version: 2.28.0       Generiert: 2026-08-22 (NTFY: Ausgabeformat wie Konsole inkl. Vendor-Lookup+Sortierung,
//                        "ganze Liste" jetzt mit Clients+APs, Header-Text statt SSID als Absender+Dateiname;
//                        Rueckkehr-Signalisierung Menue 4 jetzt global im Hintergrund aktiv)
// Version: 2.27.4       Generiert: 2026-08-20 (Menue 3: Sortierung Age/MAC + Auto-Refresh; Vendor-Lookup Menue 3a Variante 3)
// Version: 2.27.3       Vorher: 2026-08-20 (BUGFIX: WLAN-Stack-Aushungerung bei langen Listen + Overflow-Reset-Bug bei APs/Clients)
// Version: 2.27.2       Vorher: 2026-08-20 (Menue 4: Formatierung kompakter - Leerzeichen/Beschreibung-Breite)
// Version: 2.27.1       Vorher: 2026-08-20 (REQ-1..4: Watchlist-Ausrichtung, Age-Cap "old", Age-Spalte Menue 3, Rueckkehr-Signalisierung)
// Version: 2.27.0       Vorher: 2026-08-20 (Vendor-Lookup Menue 3 + 3a Var.2, gelbe Randomisierungs-Faerbung)
// Version: 2.26.3       Vorher: 2026-08-19 (BUGFIX: Cache ueberlebte keinen Redraw)
// Version: 2.26.2       Vorher: 2026-08-19 (BUGFIX: signed/unsigned-Vergleichsfehler im Vendor-Cache)
// Version: 2.26.1       Vorher: 2026-08-19 (BUGFIX: Cache tatsaechlich verdrahtet + Age-Feld robust)
// Version: 2.26.0       Vorher: 2026-08-19 (VENDOR CACHE + AGE-SPALTEN-BUGFIX)
// Version: 2.25.0       Vorher: 2026-08-18 (FILE PROTECTION: Variante 1 - Schutz-Liste)
// Version: 2.24.0       Vorher: 2026-08-17 (GROSSE UMSTELLUNG: SPIFFS -> LITTLEFS)
// Seit 2.6.0 EINZELNE Datei (vorher wifi_monitor.ino, functions.h,
// functions.ino, structures.h als 4 separate Dateien).
//
// Credits (Original-Basis):
//   Original RTOS version https://github.com/espressif/esp8266-rtos-sample-code/tree/master/03Wifi/Sniffer_DEMO/sniffer
//   Converted to Arduino https://github.com/RandDruid/esp8266-deauth and https://github.com/kripthor/WiFiBeaconJam
//   Code refactor and improvements Ray Burnette https://www.hackster.io/rayburne/esp8266-mini-sniff-f6b93a
//
// Created by Firefly  enmgzirn@yahoo.de  2026
//
// Aenderungsverlauf (jeweils bei Aenderungen zu aktualisieren):
//   2.27.4: DREI ERWEITERUNGEN:
//           (a) Menue 3 (SSID-/AP-Uebersicht): zwei neue Sortieroptionen
//           AP_SORT_AGE (Taste 'a', Default: kleinstes Alter/frischest
//           zuerst) und AP_SORT_MAC (Taste 'm', aufsteigend). Sortierlegende
//           im Header auf alle 6 Felder erweitert.
//           (b) Menue 3 aktualisiert sich jetzt selbststaendig, gleiche
//           Auto-Refresh-Logik wie Menue 3a/4 (Zeitfenster + online_mode-
//           Gate, per input_field_active() gegen Ueberschreiben einer
//           laufenden AP-Nummern-Eingabe abgesichert). Eigene Variablen
//           ssid_select_refresh_sec/last_ssid_select_refresh_time statt
//           Wiederverwendung der Menue-3a-Variablen, da Menue 3 ein
//           eigenstaendiger Zustand ist. Tasten '+'/'-' statt der ueblichen
//           u/d, da u/d in Menue 3 bereits belegt sind (u=unsortiert,
//           d=Loeschmodus) - waere sonst eine Tastenkollision gewesen.
//           Nicht in settings.cfg persistiert (Session-Variable), analog zu
//           watchlist_refresh_sec.
//           (c) Vendor-Lookup jetzt auch in Menue 3a Variante 3 (Multi-AP,
//           S+Zahl,Zahl,... z.B. "S4,8,12"): nutzt bewusst dasselbe Flag wie
//           Variante 1/2 (show_vendors_in_menu3a) statt eines eigenen -
//           Umschalten in irgendeiner der drei Varianten gilt fuer alle.
//           vendorCache_begin() ergaenzt (Variante 3 ist auch direkt aus
//           Menue 3 heraus erreichbar, ohne vorher Variante 1/2 durchlaufen
//           zu haben). Der bestehende 'v'-Tastenhandler war bereits
//           variantenunabhaengig und musste nicht geaendert werden.
//   2.27.3: ZWEI BUGFIXES nach Nutzer-Report bei sehr langen Listen (362
//           Geraete, 54 APs):
//           (a) Falsche "aktiv"-Zahl in Menue 3: client_is_hideable() ruft
//           intern find_freshest_entry_for_station() auf - eine komplette
//           weitere Schleife ueber clients_known_count, OHNE jedes yield().
//           Bei einem AP mit z.B. 45 von 362 Geraeten summierten sich das zu
//           ca. 16.300 Vergleichen am Stueck. register_beacon() laeuft aus
//           wifi_set_promiscuous_rx_cb() heraus und braucht regelmaessig
//           Gelegenheit, sich einzuklinken - ohne yield() konnte der
//           WLAN-Stack ausgehungert werden und tatsaechlich eintreffende
//           Pakete verlieren, wodurch ausgerechnet die AP-Eintraege mit den
//           MEISTEN Geraeten (teuerste Zaehlung) die falscheste "aktiv"-Zahl
//           zeigten. Periodisches yield() alle 64 Iterationen in
//           find_freshest_entry_for_station() (dem eigentlichen Kosten-
//           treiber, auch von format_client_cell()/Watchlist genutzt) sowie
//           zusaetzlich alle 32 Iterationen in der Zaehlschleife selbst
//           behoben.
//           (b) Gelegentliche Duplikate mit identischer MAC-Adresse bei
//           schon lange getrackten APs/Clients: register_beacon() und
//           register_client() setzten bei vollem Array (100 APs bzw. 600
//           Clients) den Zaehler blind auf 0 zurueck - die alten Eintraege
//           blieben dabei PHYSISCH im Array stehen, fielen aber aus der
//           Suchreichweite (die nur bis zum Zaehler sucht). Wurde ein so
//           "vergessener" Eintrag spaeter wieder gehoert, fand die Suche ihn
//           nicht mehr und legte ihn doppelt an. Jetzt wird bei vollem Array
//           gezielt der AELTESTE Eintrag entfernt (kompaktiert, wie
//           delete_ap_by_index()) statt die ganze Liste zu verwerfen -
//           Zaehler und Array bleiben dabei jederzeit konsistent.
//           HINWEIS: (b) betraf bei der Analyse noch nicht den konkreten
//           Report (54 von 100 APs, 362 von 600 Clients - beide Grenzen
//           noch nicht erreicht), ist aber unabhaengig davon ein realer
//           Bug und wurde daher vorsorglich mitbehoben. Die tatsaechliche
//           Ursache des gemeldeten Duplikat-Phaenomens bei dieser
//           Groessenordnung ist noch nicht abschliessend gefunden.
//           AUSSERDEM: FIRMWARE_VERSION/FIRMWARE_BUILD_DATE-Defines waren
//           seit v2.25.0 nicht mehr synchron zum Header-Kommentar - jetzt
//           nachgezogen und fuer kuenftige Versionen im Blick zu behalten.
//   2.27.2: Menue 4 (Watchlist) kompakter formatiert, auf Basis eines
//           exakten Soll-Vorgaben-Beispiels rechnerisch (nicht geschaetzt)
//           nachgebaut und Zeichen-fuer-Zeichen gegen das Beispiel
//           verifiziert:
//           - Eintragsnummer: kein zusaetzliches fuehrendes Leerzeichen mehr
//             (nur noch das aus "%2d" selbst - 1 Leerzeichen bei 1-stelligen
//             Nummern, keins bei 2-stelligen)
//           - "(noch out)" ruemckt 1 Zeichen nach links
//           - Beschreibung-Feld von 20 auf 12 Zeichen verschmalert (= Laenge
//             des Wortes "Beschreibung") mit nur noch 1 statt 3 Leerzeichen
//             Abstand davor
//           - Hersteller-Spalte ruemckt dadurch auf 1 Leerzeichen an die
//             Beschreibung heran, jetzt exakt auf Spalte 41 (vorher 54)
//           Row-Format ist zwischen Vendor an/aus gemeinsamer Code, daher
//           gilt die kompaktere Formatierung fuer beide Header-Varianten.
//   2.27.1: VIER PUNKTE (REQ-1 bis REQ-4):
//           REQ-1: Vendor-Ausrichtung Menue 4 (Watchlist) korrigiert. Drei
//           Ursachen behoben: (a) Eintragsnummer "%d"->"%2d" (1-/2-stellige
//           Indizes erzeugten unterschiedliche Zeilenlaengen), (b) der
//           "(noch out)"-Zweig war 1 Zeichen laenger als der Normalzweig,
//           (c) die Position von "Hersteller" im Header-String selbst war
//           gegenueber der tatsaechlichen Ausgabe verschoben. Alle drei
//           Werte rechnerisch (nicht geschaetzt) gegen die reale printf-
//           Ausgabe verifiziert - "Hersteller" steht jetzt exakt auf Spalte
//           54, unabhaengig von Eintragsnummer und Geraetestatus.
//           REQ-2: format_age_compact() zeigt jetzt "old" statt "100k" fuer
//           Werte >99999s (das haette die garantierte 3-Zeichen-Breite von
//           format_age_field() gesprengt bzw. waere durch dessen Kappung zu
//           einem irrefuehrenden "00k" verstuemmelt worden). "old" ist genau
//           3 Zeichen, passt ohne weitere Anpassung durch format_age_field().
//           Praktisch nahezu unerreichbar (MAX_CLIENT_AGE=1000s entfernt
//           Clients laengst vorher aus clients_known[]) - dient als
//           Sicherheitsnetz.
//           REQ-3: Age-Spalte in Menue 3 (einspaltige SSID-Uebersicht ohne
//           Vendor-Lookup) zwischen dB und MAC-Adresse ergaenzt, nutzt
//           dieselbe format_age_field()-Funktion wie Menue 3a/4. Nur im
//           einspaltigen Nicht-Vendor-Zweig von print_ap_cell(), zwei-
//           spaltiger und Vendor-Modus unveraendert.
//           REQ-4: Neue Rueckkehr-Signalisierung in Menue 4 (Taste 'p' zum
//           Umschalten, Default AUS). Loest ueber die BESTEHENDE
//           Signalisierungspin-Infrastruktur (signal_pin/signal_enabled/
//           signal_active_low/signal_write_digital()) einen 5ms-Impuls aus,
//           wenn ein Watchlist-Eintrag entweder aus "(noch out)" wieder
//           auftaucht oder sein Alter von >999s auf einen kleineren Wert
//           zurueckfaellt (frisches Paket nach laengerer Inaktivitaet).
//           signal_update() um ein zweites, unabhaengiges Non-Blocking-
//           Zeitfenster erweitert (eigene Dauer/eigener Ausloeser als der
//           Boot-Puls, daher kein gemeinsames Timer-Flag). Die Pro-Eintrag-
//           Zustandsverwaltung (WatchlistPulseEntry[]) wird dynamisch erst
//           beim Menue-4-Eintritt alloziert und beim Verlassen wieder
//           komplett freigegeben (dasselbe Session-Guard-Muster wie beim
//           Vendor-Cache, keine feste Vorab-Reservierung) - schluesselt
//           ueber die MAC statt den Array-Index, da Loeschen in der
//           Watchlist nachfolgende Eintraege verschiebt.
//           RAM-Kosten dieser Version: ~11 Byte dauerhaft (enable_return_pulse,
//           return_pulse_active, return_pulse_start_time_ms, sowie Zeiger/
//           Zaehler/Guard-Flag fuer die Pulse-Zustandsverwaltung - der
//           eigentliche Zustandsspeicher pro Watchlist-Eintrag ist dynamisch
//           und existiert nur waehrend Menue 4 geoeffnet ist).
//   2.27.0: DREI ERWEITERUNGEN:
//           (a) Vendor-Lookup in Menue 3 (AP-/SSID-Uebersicht): neues
//           Session-Flag show_vendors_in_menu3 (eigenes Flag, da hier APs
//           statt Clients angezeigt werden), Taste 'v' zum Umschalten. Bei
//           aktiver Anzeige entfallen Geraete/Kanal/dB-Spalten komplett und
//           der zweispaltige Modus wird deaktiviert (kein Platz fuer
//           Herstellernamen) - stattdessen SSID, MAC, Hersteller in einer
//           Zeile. print_ap_cell() um Parameter show_vendor erweitert.
//           (b) Vendor-Lookup in Menue 3a Variante 2 (kombinierte SSID-
//           Ansicht, Aufruf ueber z.B. S+Zahl): nutzt bewusst dasselbe Flag
//           wie Variante 1 (show_vendors_in_menu3a) statt eines eigenen -
//           beide Varianten sind Teil derselben Geraeteliste-Menuefamilie.
//           Der bestehende 'v'-Tastenhandler war bereits variantenunabhaengig
//           (kein current_list_mode-Guard) und musste nicht geaendert werden.
//           (c) Gelbe Faerbung randomisierter MAC-Adressen: neue Funktion
//           is_randomized_mac() (Bit 0x02 im ersten Oktett, "locally
//           administered address"). print_mac() faerbt die ersten 3 Byte
//           (6 Hex-Zeichen) IMMER gelb (Code "33"), wenn dieses Bit gesetzt
//           ist - unabhaengig von "watched"/Blau oder der Zeilenfarbe. Die
//           hinteren 3 Byte folgen weiterhin der bisherigen Regel. Da
//           print_mac() die zentrale Ausgabefunktion fuer alle MAC-Adressen
//           im Programm ist, wirkt die Faerbung ueberall, ohne dass eine der
//           bestehenden Aufrufstellen angepasst werden musste.
//           RAM-Kosten dieser Version: 1 Byte dauerhaft (show_vendors_in_menu3,
//           analog zu den bereits bestehenden Flags show_vendors_in_menu3a/
//           show_vendors_in_watchlist). is_randomized_mac() ist zustandslos.
//   2.26.3: BUGFIX: der Vendor-Cache ueberlebte keinen einzigen Redraw und
//           brachte dadurch trotz korrekter Funktion (seit 2.26.2) keine
//           spuerbare Beschleunigung. Ursache: menu_enter_ssid_list(),
//           menu_enter_ssid_list_combined() und menu_enter_watchlist()
//           werden nicht nur beim ECHTEN Eintritt in Menue 3a/3b/4
//           aufgerufen, sondern bei JEDEM Redraw (Auto-Refresh-Tick,
//           Sortierungswechsel, u/d/t/v/i-Tasten - siehe redraw_ssid_list()
//           sowie der periodische STATE_WATCHLIST-Tick). Da vendorCache_begin()
//           am Anfang und vendorCache_end() am Ende dieser Funktionen standen,
//           wurde der Cache bei JEDEM Redraw neu angelegt und sofort danach
//           wieder verworfen - er konnte sich nie ueber mehrere
//           Bildschirmaufbauten hinweg aufbauen, genau dort, wo die
//           Beschleunigung eigentlich noetig gewesen waere (wiederkehrende
//           Redraws derselben Geraete alle paar Sekunden). Fix: neue globale
//           Guard-Variable g_vendorCacheSessionActive macht vendorCache_begin()
//           bei einem Redraw waehrend laufender Sitzung zum No-Op (Cache
//           bleibt erhalten); vendorCache_end() wurde aus den drei
//           menu_enter_*()-Funktionen entfernt und stattdessen an die
//           ECHTEN Austrittspunkte verschoben: menu_go_back() (Faelle
//           STATE_SSID_LIST und STATE_WATCHLIST) sowie den globalen
//           ESC-Handler (springt von jedem Zustand direkt zu STATE_MENU,
//           umgeht menu_go_back() komplett).
//   2.26.2: BUGFIX: vendorCache_lookup() gab bei einem Negativ-Cache-Treffer
//           "return VENDOR_CACHE_NOT_FOUND;" zurueck - eine uint32_t-
//           Konstante (0xFFFFFFFF), die bei der impliziten Konvertierung in
//           den int-Rueckgabetyp der Funktion zu -1 wurde. Das ist derselbe
//           Wert, den die Funktion auch fuer einen ECHTEN Cache-Miss lieferte.
//           Der Aufrufer verglich "cacheResult == VENDOR_CACHE_NOT_FOUND"
//           (int gegen uint32_t) - durch die ueblichen Arithmetik-
//           Konvertierungsregeln wurde -1 dabei ebenfalls zu 0xFFFFFFFF
//           hochkonvertiert, sodass JEDER echte Cache-Miss faelschlich als
//           Negativ-Treffer erkannt wurde und sofort "---" lieferte, OHNE
//           dass die echte Suche (VendorLookup::getManufacturer) je
//           aufgerufen wurde. Ergebnis: alle Vendor-Lookups zeigten nur noch
//           "---", der Cache konnte sich nie befuellen. Fix: Rueckgabewert
//           von vendorCache_lookup() ist jetzt strikt auf -1 (Miss) / 0
//           (Treffer) beschraenkt; Positiv/Negativ wird ausschliesslich noch
//           ueber den Referenzparameter outOffset unterschieden (Vergleich
//           mit VENDOR_CACHE_NOT_FOUND dort, wo beide Seiten uint32_t sind).
//   2.26.1: BUGFIX-NACHBESSERUNG zu 2.26.0 - zwei Fehler in der Erstumsetzung
//           behoben, die sich beim Test zeigten:
//           (a) Vendor-Cache war nie tatsaechlich verdrahtet: alle drei
//           Aufrufstellen (Menue 3a AP-Header, Menue 3a Geraeteliste,
//           Menue 4 Watchlist) riefen weiterhin direkt
//           VendorLookup::getManufacturer() auf, der Cache-Wrapper
//           vendorCache_lookup_or_search() wurde nirgends benutzt. Jetzt an
//           allen drei Stellen verdrahtet (alter Aufruf je auskommentiert
//           stehen gelassen). Zusaetzlich war die Offset-Speicherung im
//           Cache bei einem Positiv-Treffer nur eine Attrappe (Offset=0
//           statt echtem Byte-Offset) - haette bei einem Cache-Hit immer
//           die erste Zeile von vendors.txt geliefert. Behoben durch
//           Erweiterung von getVendorByLineNumber()/binarySearchMacFile()/
//           getManufacturer() um einen optionalen Ausgabeparameter
//           uint32_t* outOffset (Default nullptr, bestehende Aufrufer
//           unveraendert), der den Byte-Offset des Zeilenanfangs waehrend
//           des ohnehin laufenden Scans mitfuehrt - kein zusaetzlicher
//           Dateizugriff noetig.
//           (b) Age-Spalten-Bugfix aus 2.26.0 wirkte nur in Menue 3a
//           (format_client_cell). Menue 4 (Watchlist) hatte einen
//           komplett separaten, nie synchronisierten Age-Formatierungscode
//           mit demselben Bug (Sprung von 4 auf 5 Zeichen Breite bei
//           Uebergang zu "Xk"-Format). Ausserdem war der urspruengliche Fix
//           selbst nicht wasserdicht: %3s in printf ist eine Minimum-,
//           keine Maximum-Breite. Neue gemeinsame Hilfsfunktion
//           format_age_field() mit echter Kappung liefert jetzt garantiert
//           exakt 3 Zeichen und wird von BEIDEN Menues verwendet.
//   2.26.0: VENDOR CACHE + AGE-SPALTEN-BUGFIX:
//           Temporaerer, RAM-sparsamer Vendor-Lookup-Cache fuer Menue 3a
//           (AP-Detailansicht) und Menue 4 (MAC-Watchlist). Cache wird beim
//           Menueeintritt dynamisch alloziert (max. 50 Eintraege, je 10 Byte),
//           beim Menueaustritt komplett freigegeben. Negativ-Caching mit
//           Sentinel 0xFFFFFFFF fuer "nicht gefunden". Wachstum ueber die
//           gesamte Menueverweildauer, kein Rollover/Ueberschreiben. Weitergabe
//           des Byte-Offsets aus getVendorByLineNumber(), neue Hilfsfunktion
//           readVendorLineAtOffset() fuer direkten Zeilen-Lookup ohne
//           vendor_index.bin. Cache ist vollstaendig gekapselt in
//           VendorCache-Modul (begin/lookup/add/end), einfach entfernbar.
//           AUSSERDEM: Bugfix Age-Spalten-Formatierung (format_age_compact).
//           Das "k"-Suffix wurde bei Wechsel von "999" zu "1k0" falsch
//           ausgerichtet (zu weit nach rechts), wodurch nachfolgende Spalten
//           nach rechts verrutschten. Jetzt konstante Feldbreite fuer ALLE
//           Wertebereiche durch Padding-Logik in format_client_cell().
//   2.25.0: FILE PROTECTION - Variante 1 (Schutz-Liste):
//           Neue Hilfsdatei /protected.txt mit Liste systemkritischer Dateien
//           (settings.cfg, watchlist.cfg, MAC-Tabellen). Globale Variable
//           show_hidden (false = versteckt, true = sichtbar) toggle mit Taste
//           h allein. Taste h + Nummer markiert/demarkiert Datei als
//           geschuetzt. Menü 6 zeigt [PROTECTED] Label und Filterhinweis.
//           Vor Loesch-Operation: Schutzpruefung mit Fehler wenn protected &&
//           !show_hidden. protected.txt Verwaltung runtime mit LittleFS.open(w).
//   2.24.0: GROSSE UMSTELLUNG: SPIFFS -> LittleFS. Die Debug-Analyse der
//           Vendor-Blocksuche (siehe 2.22.x/2.23.x) hatte gezeigt, dass
//           die verbleibende Latenz nicht an der Suchlogik lag, sondern an
//           SPIFFS selbst: SPIFFS speichert Dateien in 256-Byte-Seiten,
//           die per Seitenkette verkettet sind - f.seek(offset) muss
//           diese Kette bis zum Ziel-Offset durchlaufen, die Seek-Dauer
//           steigt also mit dem Offset (in Messungen 38-85ms je nach
//           Byte-Position, obwohl jeweils nur ein kleiner Block/eine
//           Zeile gelesen wurde). LittleFS hat dieses Problem nicht
//           (echte indexierte Bloecke, O(1)-Seeks) und ist ausserdem seit
//           Core 2.7.0 ueber das mitgelieferte mklittlefs-Tool nutzbar -
//           die Python-Toolchain-Abhaengigkeit, die 2.2.0 zur Ruecknahme
//           von LittleFS gefuehrt hatte, besteht mit Core 3.1.2 nicht
//           mehr (in ArduinoDroid getestet: kompiliert/mountet
//           einwandfrei). Aenderungen: #include <LittleFS.h> ergaenzt,
//           alle SPIFFS.*-Aufrufe (begin/exists/open/format/remove/info/
//           openDir) auf LittleFS.* umgestellt, Variable spiffs_ok ->
//           littlefs_ok, Serial-Meldungen/Kommentare angepasst. Der
//           Auto-Format-Fallback (bei begin()-Fehlschlag) bleibt als
//           Sicherheitsnetz erhalten, greift aber im Normalfall nicht
//           mehr, da LittleFS anders als SPIFFS per Default schon beim
//           ERSTEN begin() automatisch formatiert, wenn keine gueltige
//           Struktur vorgefunden wird.
//           AUSSERDEM: Das kleine WLAN/HTTP-Upload-Hilfsprogramm
//           (separates .ino, nicht Teil dieser Datei) wurde ebenfalls
//           komplett auf LittleFS umgestellt (gleiche Aenderungen), damit
//           beide Programme dasselbe Dateisystem verwenden.
//           WICHTIG: LittleFS ist NICHT kompatibel mit vorhandenen
//           SPIFFS-Dateien - nach dem Flashen muessen vendors.txt,
//           mac_5/6/7byte.bin (und die davon selbst generierten Index-
//           Dateien) einmalig neu hochgeladen werden.
//   2.23.1: BUGFIX Kompilierungsfehler "'debugLog' was not declared in
//           this scope" (und Folgefehler bei debugPause/debugBytesToHex).
//           Ursache: Das Debug-Framework aus 2.23.0 wurde ERST NACH der
//           VendorLookup-Klasse definiert, obwohl die Klasse diese
//           Funktionen bereits vorher aufruft - C++ braucht die
//           Deklaration vor der ersten Verwendung. Fix: Forward-
//           Deklarationen (extern g_debugFlag + Funktionssignaturen)
//           direkt vor die VendorLookup-Klasse gesetzt, die vollstaendigen
//           Definitionen bleiben unveraendert an ihrer bisherigen Stelle.
//   2.23.0: NEUES FEATURE - allgemeines Debug-Ausgabe-Framework: Strg+D
//           schaltet jederzeit/ueberall (wie Strg+O) ein globales
//           g_debugFlag um. debugLog() gibt Zeilen NUR bei gesetztem Flag
//           aus, immer mit millis()-Zeitstempel am Zeilenanfang.
//           g_debugFlag ist als __attribute__((weak)) definiert, damit
//           Module wie VendorLookup auch in einem anderen Hauptprogramm
//           ohne eigenes Debug-Flag sauber compilieren/linken und dann
//           automatisch stumm bleiben (Flag gilt dort als nicht gesetzt).
//           debugPause() haelt das Programm an und wartet auf einen
//           beliebigen Tastendruck - ebenfalls nur bei gesetztem Flag.
//           Fuer die aktuelle Baustelle (Beschleunigung Index-Suche)
//           wurden folgende Debug-Meldungen in VendorLookup eingebaut:
//           Such-MAC, erster/gekuerzter Suchstring je Datei, geoeffnete
//           Datei (Index + mac_xByte.bin), Block-Suchergebnis (Treffer/
//           Nicht-Treffer inkl. Position und Index-Verweis), RAM-Suche im
//           geladenen Block, Fundstelle mit Verweis in vendors.txt, sowie
//           das an diesem Verweis gefundene Ergebnis. Nach jedem
//           abgeschlossenen Sucheversuch haelt debugPause() an.
//           AUSSERDEM: Vendor-Anzeige jetzt auch in Menue 4 (MAC-
//           Watchlist) mit Taste v umschaltbar (show_vendors_in_watchlist),
//           Hersteller-Spalte erscheint hinter der Beschreibung-Spalte.
//   2.22.2: PERF-FIX Vendor-Blocksuche war LANGSAMER statt schneller.
//           Ursache war NICHT die Blocklogik selbst, sondern: pro Suche
//           liefen bis zu 4 teure SPIFFS-Metadaten-Zugriffe (exists(file),
//           exists(index), open(index), open(file)) statt noetiger 2
//           (open(index), open(file)) - LittleFS.open()/.exists() muessen auf
//           dem ESP8266 das Objektregister im Flash durchsuchen und sind
//           selbst teuer. Dazu kam ein komplett unnoetiger zweiter
//           seek()+read() in findBlockOffset() (derselbe Eintrag wurde
//           zweimal gelesen). Beides entfernt: unnoetige exists()-Vorab-
//           checks raus, Treffer-Puffer der Index-Binaersuche wird direkt
//           beim Update gesichert statt hinterher nochmal gelesen.
//           Zusaetzlich ein kostenguenstiges Sicherheitsnetz eingebaut:
//           falls ein Treffer nicht im ermittelten Block liegt, wird noch
//           der erste Record des naechsten Blocks geprueft (nur 1 kleiner
//           Read, nur im Nicht-Treffer-Fall) - faengt theoretische
//           Randfaelle ab, ohne im Erfolgsfall (Normalfall) etwas zu
//           kosten. Die klassische Binaersuche bleibt als Fallback nur
//           fuer den Fall einer fehlenden/leeren Index-Datei erhalten.
//   2.22.1: BUGFIX Stack-Overflow (Panic in __yield) bei aktivierter
//           Hersteller-Anzeige in Menue 3a: Die neuen Puffer der Block-
//           Index-Suche (blockBuf[512] in binarySearchMacFile) sowie
//           buffer[256]/buffer[512] in getVendorByLineNumber()/
//           generateVendorIndex() lagen als lokale Arrays auf dem Stack.
//           Zusammen mit der ohnehin tiefen Aufrufkette (Menue -> Sortierung
//           -> Vendor-Lookup -> Serial.printf/String) hat das den knappen
//           ESP8266-cont-Stack (~4 KB) gesprengt. Fix: alle drei Puffer
//           als static deklariert -> liegen im BSS-Segment statt auf dem
//           Stack, kosten dort 0 Byte.
//   2.22.0: GESCHWINDIGKEITSOPTIMIERUNG Vendor-Suche (Punkt: MAC-Listen-
//           Index) - bisher ca. 250ms pro Suche durch klassische
//           Binaersuche mit log2(N) einzelnen Flash-Lesezugriffen direkt
//           in mac_5/6/7byte.bin. Jetzt analog zum bestehenden
//           vendor_index.bin-Prinzip: Pro MAC-Liste eine eigene, viel
//           kleinere Block-Index-Datei (mac5/6/7_index.bin), die beim
//           ersten Start automatisch erzeugt wird, falls sie fehlt.
//           Suche findet zuerst per Binaersuche in der kleinen Index-
//           Datei den passenden Block ("Block oder naechstkleiner"),
//           danach genau EIN Lesevorgang, der den kompletten Block
//           (512 Byte, passt in einen Read) ins RAM laedt - die
//           eigentliche Treffersuche laeuft dann nur noch im RAM ohne
//           weiteren Flash-Zugriff. Fallback auf klassische Binaersuche,
//           falls eine Index-Datei fehlt/nicht erzeugt werden konnte.
//           Ausserdem: Dateiliste (Menuepunkt 6) von 12 auf 20 Dateien
//           erweitert (file_list_names[12][32] → [20][32], kostet
//           zusaetzliches RAM, ausdruecklich gewuenscht).
//   2.21.1: STRUKTUR-OPTIMIERUNG - Weitere RAM-Ersparnis durch Feldlöschung:
//           clientinfo: 29 → 20 Bytes (-31%)
//             Gelöscht: seq_n (2B, nicht genutzt), ap[6] (6B, redundant), header (1B, nicht genutzt)
//             BEHALTEN: err, reported (werden für Fehlerlogik gelesen!)
//           beaconinfo: 51 → 48 Bytes (-6%)
//             Gelöscht: capa[2] (2B, nicht genutzt), header (1B, nicht genutzt)
//             BEHALTEN: err, reported (werden für Fehlerlogik gelesen!)
//           probeinfo: ~114 → ~95 Bytes (-17%)
//             Gelöscht: seq_n (2B, nicht genutzt), ap[6] (6B, nicht genutzt), header (1B, nicht genutzt)
//           Ersparnis bei 400 Clients + 90 APs: ~3.9 KB zusätzlich!
//           Status: v2.21.1 = v2.21.0 + Struktur-Optimierungen
//   
//   2.21.0: MAC-Herstellererkennung (Vendor Lookup) - VendorLookup-Klasse integriert:
//           Taste 'v' in Menü 3a: Toggle für Hersteller-Anzeige (Session-persistent)
//           On-Demand Lookup beim Rendern (KEIN Batch-Cache zur Speichersicherheit)
//           Bei Aktivierung: Einspaltige Ansicht mit Herstellernamen hinter dB
//           AP-Header zeigt: "AP-MAC: ... dB Hersteller: <Name>"
//           
//           RAM-OPTIMIERUNG (Punkt 3.1):
//           - Index-Arrays (indices[], all_matches[]): int → uint16_t (-900 Bytes)
//           - MAX_CLIENTS_TRACKED: bleibt 400
//           
//           Voraussetzung: /mac_7byte.bin, /mac_6byte.bin, /mac_5byte.bin, /vendors.txt im SPIFFS
//   2.13.0: Dynamische SSID-Länge, Channel-Filter (Hidden E3),
//           Scan-Verweilzeit (Hidden E4), Funktionsdeklarationen-Fix
//   2.14.0: Multi-AP Header mit SSID anzeigen (S4,7 → "4 (SSID1),7 (SSID2)"),
//           Hidden Test Function: Shift+A für Auto-Save Trigger
//   2.15.0: NTFY Message Title Header "WiFi-Monitor Liste von [SSID]",
//           Datei-Kopfzeile mit Sender-SSID + Zeitstempel
//   2.16.0: Auto-Load Datei beim Neustart (Punkt e → 10),
//           Auto-Load Online-Modus (nicht offline), Auto-Save markiert
//           geladene Datei als "last loaded"
//   2.17.2: Taste 'i' in Listen S5/S<n,n,...> (Modus 2/3): blendet Clients
//           aus, die den AP gewechselt haben oder "out" sind (nur Anzeige,
//           Hauptliste bleibt unveraendert), on-the-fly wie u/d.
//           Hauptmenue zeigt Warnzeile, solange Channel-Filter (Hidden E3)
//           nicht auf "alle" steht.
//           Bugfix: manuelles Laden (Punkt 6, l+Zahl+Enter) suchte durch
//           doppelt angehaengte ".txt"-Endung die falsche Datei und schlug
//           fehl.
//           Bugfix: Ntfy "ganze Liste" (Modus 0) war faelschlich nach MAC
//           sortiert statt in der rohen Reihenfolge wie Punkt 1 + Enter.
//           Bugfix: Nach Rueckkehr aus Offline wurde die komplette Offline-
//           Dauer auf alle Age-Times aufaddiert (falsches Ausgrauen);
//           jetzt laeuft die Age-Time nahtlos ab dem Einfrierzeitpunkt weiter.
//   2.17.3: Paket 3 - Listen-Rendering Liste 3/3a:
//           Bugfix: AP-Spalte in Modus 2 (S5) und Modus 3 (S<n,n,...>) zeigte
//           immer "--" (die alte Abfrage konnte nie zutreffen) - zeigt jetzt
//           den tatsaechlichen AP, ersetzt dabei die bisher dort gezeigte
//           (irrelevante) Kanalnummer. Header von "ch" auf "AP" umbenannt.
//           Bugfix: calculate_max_ssid_length() war bisher nirgends
//           eingebunden (Liste 3 nutzte feste Breiten) - jetzt aktiv, dazu
//           die faelschliche +2-Zeichen-Zugabe entfernt. Im zweispaltigen
//           Modus wird jede Spalte einzeln anhand ihrer eigenen Eintraege
//           gekuerzt.
//           Geraetespalte in Liste 3 zeigt jetzt "gefunden/aktiv" (z.B. 20/15).
//           Spaltenabstand in den zweispaltigen Client-Listen (Modus 2/3)
//           auf ein Leerzeichen reduziert.
//   2.17.4: Paket 4 - Liste 3 (AP-Uebersicht) jetzt sortierbar: unsortiert
//           (u), SSID (n), Anzahl Geraete (g), Pegel (p) - jeweils erneutes
//           Druecken derselben Taste kehrt die Richtung um, wie schon bei
//           der Client-Sortierung (m/a/r) in Liste 3a. Sortiereinstellung
//           wird wie gehabt in settings.cfg und Szenario-Dateien gespeichert.
//   2.17.5: Paket 5 - neue Menuefunktionen:
//           Neuer Menuepunkt "m" (Hauptmenue): alte Eintraege nach Alter
//           loeschen, waehlbar nur Clients / nur Access Points / beides.
//           Liste 3 (AP-Auswahl): "d+Zahl+Enter" loescht gezielt einen
//           einzelnen Access Point aus der Hauptliste (analog zu Punkt 6,
//           Datei loeschen). Zugehoerige Clients bleiben erhalten.
//   2.17.6: Paket 7 - Status-LED an frei waehlbarem GPIO-Pin (Hidden
//           Settings, Punkt 6): durchgehend an waehrend des Bootvorgangs,
//           sanftes Auf-/Abschwellen (PWM) im Scan-Betrieb (online),
//           kurzer 50ms-Blitz alle 2s im Offline-Modus, aus waehrend
//           zeitkritischer Vorgaenge (Dateitransfer, lange Listenausgabe,
//           ntfy-Versand). Taste 't' in den Hidden Settings schaltet die
//           LED am konfigurierten Pin manuell ein/aus zum Testen, ob der
//           richtige Pin gewaehlt wurde - die Automatik pausiert dabei.
//   2.17.7: Nutzer-Feedback zur Status-LED:
//           Bugfix: PWMRANGE war in dieser Core-Version nicht deklariert -
//           eigene STATUS_LED_PWM_RANGE-Konstante statt der Core-Konstante.
//           Neue Einstellung "7) Status-LED Polaritaet" (Hidden Settings):
//           viele Onboard-LEDs sind aktiv-LOW verdrahtet, das war bisher
//           nicht beruecksichtigt - der 50ms-Blitz leuchtete dadurch genau
//           umgekehrt (fast durchgehend an statt kurz auf).
//           Auf-/Abschwellen im Online-Betrieb jetzt auf 50% der maximalen
//           Helligkeit begrenzt.
//           GPIO16 hat auf dem ESP8266 keine PWM-Hardware (eigenes RTC-
//           Register, kein Timer angebunden) - fuer diesen Pin wird das
//           Schwellen jetzt per Software-PWM (kurzes An/Aus-Verhaeltnis
//           ueber einen 20ms-Zyklus) nachgebildet statt per analogWrite().
//   2.17.8: Paket 6 - Zeitzone/Daylight Saving Time:
//           Bugfix: Info-Seite (Punkt i) zeigte die NTP-Zeit immer als UTC
//           an, auch wenn eine Zeitzone/DST eingestellt war (falsche
//           Funktion current_unix_time() statt current_unix_time_with_tz()
//           wurde dort aufgerufen).
//           Neuer Einstellpunkt (Punkt 9, Taste 5): Zeitzone als UTC-Offset
//           frei einstellbar (-12 bis 12 Stunden), vorher nur per manueller
//           Konfigdatei-Bearbeitung moeglich. Standard weiterhin +1.
//           "MESZ" ueberall durch "Daylight Saving Time" ersetzt, da die
//           Sommer-/Winterzeit-Umstellung nicht nur in Europa existiert.
//           Punkt 9, Taste 6 schaltet DST jetzt nur noch grundsaetzlich an/
//           aus - die Umstellung selbst (welcher Zustand gerade gilt)
//           erfolgt automatisch nach Kalenderdatum (EU-Regel: letzter
//           Sonntag Maerz/Oktober, 01:00 UTC). Andere Weltregionen mit
//           abweichenden DST-Regeln (USA, Suedhalbkugel etc.) werden davon
//           NICHT korrekt erfasst - dafuer waere eine Regel pro Land noetig.
//   2.17.9: RAM-Optimierung (nicht Paket-basiert, sondern proaktive Stabilisierung):
//           Compiler meldete nur noch ~5 KB freien RAM. SPIFFS konnte deswegen
//           beim Boot nicht zuverlässig initialisiert werden.
//   2.18.0: Paket 1 - Bugfixes:
//           Min/Max RSSI Anzeige + Variablen + Funktionen komplett entfernt
//           (rssi_trend_threshold bleibt - das ist die Änderungs-Schwelle!).
//           Auto-Save um 0:00 Uhr: zusätzliche Minutenprüfung (tm_min == 0)
//           um Loop-Speichern zwischen 0:00-0:59 Uhr zu vermeiden.
//           Age-Zeit Kompaktformat: neue Funktion format_age_compact()
//           für Anzeige >999s als "Xk" statt vierstellig/fünfstellig.
//           Menü 3/3a Header-Abstände überarbeitet für bessere Spaltenausrichtung.
//           Massnahmen: prev_shown_rssi[250] von int zu int8_t (-750 Byte),
//           file_list_names von [16][32] zu [12][28] (-176 Byte), 10x kleine
//           int-Variablen zu uint8_t (-30 Byte), Char-Arrays reduziert
//           (notif_text_edit_buf, notif_channel, channel_filter, autoload_*,
//           notif_ssid_filter) (-110 Byte), min/max_rssi_seen zu int8_t (-6 Byte).
//           Gesamteinsparung: ~1.1 KB RAM freigegeben. MAX_APS_TRACKED (100) und
//           MAX_CLIENTS_TRACKED (250) blieben unverändert wie gewünscht.
//           Datei-Limit Punkt 6 von 16 auf 12 Dateien reduziert (seltene
//           Anwendung, der meiste Speicher hat ohnehin nicht so viele Dateien).
//
//   Schritt 1: Speicher-Tuning (MAX_APS_TRACKED/MAX_CLIENTS_TRACKED
//              erhoeht, Probes werden nicht mehr gespeichert)
//   Schritt 2: VT100-Menue-Geruest, Punkt 1 (Standardausgabe)
//   2.1.0: Punkt 3 voll ausgebaut (Sortierung, Auto-Refresh,
//          RSSI-Trend), Punkt 2 aktiviert, Einstellungen (e),
//          Hilfe (h), Punkt 5/6 (Speichern/Laden/Loeschen via
//          Dateisystem), Backspace-Navigation
//   2.2.0: SPIFFS statt LittleFS (Kompatibilitaet ohne Python-
//          Toolchain-Abhaengigkeit). [Rueckgaengig gemacht in 2.24.0,
//          siehe dort - der damalige Grund bestand mit Core 3.1.2
//          nicht mehr]. Bugfix Punkt 5 (Zustand blieb
//          nach Speichern haengen). Bugfix Punkt 6 (SPIFFS liefert
//          Dateinamen mit fuehrendem "/", fuehrte zu doppeltem
//          Slash beim Oeffnen/Loeschen). Ausgrauen (last seen>600s)
//          jetzt in Punkt 1/2/3 (SGR-Code von "2"/faint auf "90"/
//          grau umgestellt, da faint von vielen Terminals ignoriert
//          wird). RSSI-Trend zeigt jetzt dB-Differenz. Punkt-3-
//          Aktualisierungsintervall einstellbar (u/d). Boot startet
//          im Hauptmenue. Speicherplatzanzeige bei Punkt 5/6. Punkt
//          7 entfernt. Hilfe (h) und Info (i) getrennt: h=Programm-
//          beschreibung+Menuepunkte, i=Herkunft/Version/ESP-Chip-
//          und Speicherdaten/Dateianzahl/min-max-RSSI. Punkt-3-
//          Header zeigt jetzt auch den aktuellen AP-Pegel.
//   2.2.1: Kompatibilitaetsfix fuer aeltere esp8266-Boardpakete
//          (z.B. 2.4.2): ESP.getHeapFragmentation() und
//          ESP.getMaxFreeBlockSize() gibt es erst in neueren Core-
//          Versionen - in Punkt i entfernt, nur ESP.getFreeHeap()
//          (immer verfuegbar) bleibt.
//   2.3.0: Umbenennung in "WiFi Monitor" (Menue/Hilfe/Dateiname).
//          Punkt 6: Datei laden als aktiver Scan-Zustand (ersetzt
//          clients_known[]/aps_known[] komplett, "last seen" wird
//          relativ zu "jetzt" neu berechnet). Schaltet vor dem Laden
//          automatisch in den Offline-Modus, damit kein fremdes
//          Live-Umfeld versehentlich hineinmischt; im Online-Modus
//          wird ein geladenes Szenario durch echten Funkverkehr ganz
//          normal weiter aktualisiert. Rote Offline-Warnzeile jetzt
//          auf jedem Bildschirm sichtbar, solange online_mode=false.
//          Punkt-3-Header zeigt den AP-Pegel jetzt ohne "Pegel:"-Text.
//   2.3.1: Bugfix "last seen" nach Datei-Laden (Punkt 6): Eine
//          fehlerhafte Sicherheitsklammer (now > age ? now-age : now)
//          setzte das Alter faelschlich auf 0 zurueck, wenn das
//          gespeicherte Alter groesser war als die bisherige ESP-
//          Laufzeit (sehr haeufiger Fall). Jetzt konsequente unsigned-
//          Wraparound-Arithmetik ohne Klammer - Alter bleibt beim
//          Laden korrekt erhalten. Watchdog-Reset bei grossen Listen
//          (Punkt 1/2 Return-Dump, Speichern, Laden, Datei-Anzeige)
//          behoben: yield() an allen potentiell langen Schleifen
//          ergaenzt. Geraeteanzahl pro SSID in der Punkt-3a-Auswahl-
//          liste ergaenzt.
//   2.4.0: Grosses Update: Leerzeile im Hauptmenue zwischen Ziffern-
//          und Buchstaben-Punkten. Strg+O schaltet jederzeit (ausser
//          waehrend Text-/Zahleneingabe) zwischen Online/Offline um.
//          Speicherplatz-Anzeigen (Punkt i, Punkt 5/6) zeigen jetzt
//          auch den Prozentsatz frei. Punkt 3a (SSID-Auswahl) zeigt
//          jetzt Kanal und aktuellen Pegel hinter der MAC-Adresse.
//          Punkt 3 (Geraeteliste) und 3a auf kompaktes Format
//          umgestellt (ch/Age statt Kanal/LastSeen(s), Trend ohne
//          "staerker/schwaecher"-Text, nur Pfeil+dB-Differenz).
//          Zweispaltige Darstellung fuer Punkt 3 und 3a, je eigener
//          einstellbarer Schwellenwert in den Einstellungen (0=aus),
//          Standard 30 bzw. 40. last seen zaehlt im Offline-Modus
//          nicht mehr weiter (eingefroren beim Wechsel). Auto-Refresh
//          in Punkt 3 pausiert automatisch im Offline-Modus.
//          Sortierung/Refresh-Intervall/RSSI-Schwelle/Zweispalten-
//          Schwellenwerte werden jetzt mit in die Datei gespeichert
//          und beim Laden automatisch uebernommen (alte Dateien ohne
//          diesen Block bleiben kompatibel).
//   2.5.0: Bugfix AP_CELL_SSID_WIDTH/AP_CELL_WIDTH zu spaet definiert
//          (Compile-Reihenfolge). Bugfix Pufferueberlauf bei der
//          AP-Uebersichtsliste (einspaltig, 32-Zeichen-SSID sprengte
//          den Puffer, Pegel wurde abgeschnitten). Sortiertaste
//          LastSeen von l auf a umgestellt. Client-Roaming: Wechselt
//          ein Geraet den Access Point, entsteht jetzt ein neuer
//          Eintrag (Matching ueber Station+BSSID statt nur Station).
//          Nicht mehr aktive Verbindungen desselben Geraets zeigen
//          ">n" (n = AP-Auswahlnummer der aktiven Verbindung) statt
//          Pegel und werden ausgegraut; ist das Geraet nirgends mehr
//          aktiv (>600s), zeigen alle seine Eintraege "out". Redundante
//          Text-Labels (ch/age/G/dB) in den Zeilen von Punkt 3 und
//          Geraeteliste entfernt, Erklaerung steht im Spaltenkopf.
//          Pegel/MAC-Reihenfolge in Punkt 3 getauscht (Pegel zuerst),
//          MAC entfaellt dort im zweispaltigen Modus. Access Points
//          werden jetzt ebenfalls ausgegraut (last seen > 600s).
//          Einstellungen-Labels (Punkt 3/4) entschaerft. Info-Seite:
//          Flash-Aufteilung korrekt in Sketch-Partition vs. Datei-
//          Partition getrennt dargestellt, Betriebszeit seit letztem
//          Reset ergaenzt (Tage hh:mm:ss). Einstellungen werden jetzt
//          dauerhaft im Flash gespeichert (/settings.cfg): Start-Modus
//          (Online/Offline) und Logo-An/Aus sichern sich sofort
//          automatisch bei Aenderung, alle uebrigen Einstellungen nur
//          ueber den expliziten Menuepunkt "s" (Einstellungen
//          speichern) - bei Erstinstallation ohne vorhandene Datei
//          bleiben die Standardwerte aktiv. Boot-Logo (5s Anzeige,
//          abschaltbar ueber Hidden Settings), Hidden Settings ueber
//          Grossbuchstabe E im Hauptmenue erreichbar. Logo erscheint
//          auch im Hilfe-Seiten-Header. Vorbereitung fuer /logo.txt
//          als Datei-Override (fuer spaeteren Y-Modem-Upload).
//          Y-Modem-Dateitransfer und Zusammenfuehren der 4 Quelldateien
//          bewusst auf einen eigenen naechsten Schritt verschoben.
//   2.5.1: Bugfix: promisc_cb() behandelte bisher JEDES Paket mit
//          Laenge != 12 und != 128 ungeprueft als Client-Datenpaket.
//          Mesh-Management/Action-Frames fremder Access Points (haben
//          praktisch nie 128 Byte) wurden dadurch faelschlich als neue
//          Clients erkannt - seit dem Station+BSSID-Matching in 2.5.0
//          fuellte das die Geraeteliste innerhalb von Sekunden. Jetzt
//          wird vor der Client-Registrierung der echte frame_type aus
//          dem Frame-Control-Byte geprueft (nur Typ 2 = Data zulaessig),
//          zusaetzlich Mindestlaengen-Check (>=48 Byte).
//   2.6.0: Die 4 Quelldateien (wifi_monitor.ino, functions.h,
//          functions.ino, structures.h) zu dieser einen Datei
//          zusammengefuehrt. Menuepunkt 4 implementiert: MAC-Adress-
//          Watchlist (Anwesenheitscheck). Freie MAC-Adressen mit
//          Beschreibung koennen hinzugefuegt (a) und wieder entfernt
//          werden (x+Zahl+Enter, loescht nur aus der Watchlist, nicht
//          aus der Geraeteliste), dauerhaft gespeichert unter
//          /watchlist.cfg. Anzeige im selben Zeilenformat wie Punkt 3
//          (MAC/Kanal/Alter/RSSI+Trend), findet dabei automatisch die
//          aktuellste Sichtung je MAC ueber alle Access Points hinweg.
//          Einstellbares Auto-Refresh-Intervall (u/d) wie in Punkt 3.
//          Neue Funktion print_mac(): MAC-Adressen, die auf der
//          Watchlist stehen, werden ab sofort auf JEDER Ausgabe (Live-
//          Ausgabe Punkt 1/2, Geraeteliste Punkt 3, SSID-Auswahl
//          Punkt 3a, Watchlist selbst) blau markiert, unabhaengig von
//          der sonstigen Zeilenfarbe (z.B. grau bei "stale"). Dafuer
//          format_client_cell()/print_client_cell()/print_ap_cell()
//          entsprechend umgebaut (MAC wird nicht mehr in den
//          formatierten Textblock eingebettet, sondern separat via
//          print_mac() ausgegeben).
//   2.7.0: Punkt 3a (SSID-Auswahl) um kombinierte Ansicht erweitert:
//          Zahl+Enter zeigt wie bisher nur die Clients des gewaehlten
//          Access Points. S+Zahl+Enter (z.B. "S3" + Enter) zeigt
//          stattdessen alle Clients ueber ALLE Access Points hinweg,
//          die dieselbe SSID wie der gewaehlte Eintrag senden - z.B.
//          bei mehreren Access Points/Repeatern mit identischer SSID.
//          Neue Funktion menu_enter_ssid_list_combined(), Auto-Refresh/
//          Sortierung/Threshold-Aenderung ueber neue redraw_ssid_list()
//          gebuendelt, damit beide Modi darueber aktualisiert werden.
//   2.8.0: Diverse Fixes + neues Feature "Benachrichtigung":
//          - Bugfix: aps_known[].ssid ist uint8_t[], nicht char[] -
//            strncpy/strcmp in menu_enter_ssid_list_combined() gaben
//            Compiler-Fehler, jetzt memcpy() bzw. Cast auf (const char*).
//          - Bugfix Bootbildschirm: Bildschirm wird jetzt VOR dem Logo
//            geloescht, 5 Sekunden lang ist NUR das Logo zu sehen. Vorher
//            stand der Live-Ausgabe-Spaltenkopf ueber dem Logo und
//            eintreffende Pakete wurden waehrend der 5 Sekunden schon
//            unterhalb des Logos mitgeschrieben (menu_state war per
//            Default STATE_LIVE, bevor menu_init() lief). menu_state
//            wird jetzt schon in setup() auf STATE_MENU gesetzt; der
//            Spaltenkopf ("Type: ...") erscheint stattdessen beim
//            Betreten von Punkt 1/2.
//          - Logo von der Hilfe-Seite (h) auf die Info-Seite (i)
//            verschoben.
//          - Taste 'E' (Hidden Settings) ist jetzt nur noch INNERHALB
//            des Einstellungsmenues (Punkt e) aktiv, nicht mehr im
//            Hauptmenue. Backspace aus Hidden Settings fuehrt zurueck
//            zu den normalen Einstellungen statt zum Hauptmenue.
//          - Neu: Einstellungen > 6) Benachrichtigung (ntfy.sh).
//            Autonomer, periodischer Versand der aktuellen Liste als
//            Dateianhang per HTTPS-PUT an einen ntfy.sh-Kanal. WLAN-
//            SSID/Passwort fuer den Versand, Kanalname und Intervall
//            (Minuten) sind konfigurierbar, ebenso der Inhalt: (0)
//            komplette aktive Liste, (1) alle Clients einer SSID ueber
//            alle APs mit dieser SSID hinweg (nutzt dieselbe Logik wie
//            die S+Zahl+Enter-Ansicht aus 2.7.0), (2) mehrere SSID-Namen
//            kommagetrennt. Manueller Sofortversand ueber Taste 8.
//            Neue Funktionen: menu_enter_notif_settings(),
//            menu_enter_notif_text_edit(), build_notif_attachment(),
//            notif_send_now(). Einstellungen werden wie die uebrigen
//            Einstellungen ueber Taste 's' dauerhaft gespeichert.
//            WICHTIG: Waehrend des Versands (WLAN-Verbindung + Upload)
//            pausiert das Promiscuous-Sniffing kurz (ein Funkchip kann
//            nicht beides gleichzeitig) und laeuft danach automatisch
//            weiter. Zertifikatspruefung ist deaktiviert (setInsecure()),
//            da der ESP8266 keinen CA-Zertifikatsspeicher hat.
//   2.8.1: Zwei Bugfixes am Benachrichtigung-Feature aus 2.8.0:
//          - Compile-Fehler behoben: die notif_*-Variablen standen
//          hinter loop(), obwohl loop() sie schon braucht (gleiche
//          Fehlerklasse wie startup_online/show_logo in 2.6.0) - jetzt
//          vor setup()/loop() definiert.
//          - Absturz beim Versand (Exception 29, Nullpointer) behoben:
//          setInsecure() ist auf dem ESP8266 nicht optional - fehlt es,
//          versucht BearSSL trotzdem eine Zertifikatspruefung gegen eine
//          leere Vertrauensliste und stuerzt ab. Zusaetzlich
//          setBufferSizes(512, 512) ergaenzt, da die BearSSL-Standard-
//          puffer (16+16 KByte) auf dem ohnehin stark ausgelasteten
//          ESP8266-Heap leicht zu Speicherproblemen fuehren koennen.
//          (Diese beiden Aenderungen betrafen HTTPS/BearSSL und wurden
//          in 2.8.2 durch den Umstieg auf reines HTTP wieder hinfaellig,
//          siehe dort.)
//   2.8.2: Benachrichtigung von HTTPS auf reines HTTP (Port 80)
//          umgestellt, da ntfy.sh das nach Nutzerangabe unterstuetzt.
//          Grund: auf alten ESP8266-Cores ohne BearSSL (z.B. 2.4.2) gibt
//          es nur die alte axTLS-WiFiClientSecure, die mit modernen
//          TLS-Servern wie ntfy.sh oft abstuerzt statt sauber einen
//          Fehler zu melden (Exception 29) - reines HTTP umgeht dieses
//          Problem komplett. notif_send_now() nutzt jetzt WiFiClient
//          statt WiFiClientSecure, verbindet auf Port 80.
//          WiFiClientSecure.h wird nicht mehr eingebunden.
//   2.8.3: Vier Bugfixes nach Nutzertest von 2.8.2:
//          - Compile-Fehler behoben: "MenuState menu_state = STATE_LIVE;"
//          stand hinter setup()/loop(), obwohl setup() es schon braucht
//          (menu_state = STATE_MENU;) - gleiche Fehlerklasse wie
//          notif_*/startup_online/show_logo zuvor. Jetzt direkt nach dem
//          enum MenuState deklariert.
//          - "Sniffing wird taub" nach ntfy-Versand behoben: nach
//          WiFi.begin()/WiFi.disconnect() reichte
//          wifi_set_promiscuous_rx_cb()+wifi_promiscuous_enable() allein
//          nicht aus, der Funk blieb in einem Zustand haengen, in dem
//          promisc_cb() keine Pakete mehr bekam. notif_send_now()
//          wiederholt jetzt die komplette Init-Sequenz aus setup()
//          (disable -> wifi_set_opmode -> wifi_set_channel -> Callback
//          setzen -> enable), zusaetzlich nothing_new=0 zurueckgesetzt.
//          - Fehlende Wagenrueckläufe im Boot-Logo behoben: BUILTIN_LOGO
//          enthielt nur rohe \n zwischen den Zeilen (Treppenstufen-
//          Effekt). print_logo() fuegt jetzt vor jedem \n ein \r ein,
//          sowohl fuer /logo.txt als auch das eingebaute Logo.
//          - "?" statt Logo-Zeichen: siehe 2.8.4, die Korrektur in 2.8.3
//          (Umstellung auf ASCII) war auf Nutzerwunsch wieder verworfen.
//   2.8.4: Auf Nutzerwunsch das Original-Unicode-Logo aus 2.8.3 wieder
//          hergestellt (die ASCII-Umstellung war nicht gewuenscht - das
//          Logo hatte schliesslich schon vorher funktioniert, u.a. auch
//          mit vorherigem vt_clear_screen() auf der alten Hilfe-Seite).
//          Stattdessen echte vermutete Ursache behoben: eine kurze
//          delay(300) direkt nach Serial.begin() in setup() ergaenzt.
//          Vermutung: USB-Serial-Adapter/Terminalprogramme sind direkt
//          nach dem Oeffnen der Verbindung oft noch nicht bereit, die
//          ersten Bytes zuverlaessig zu empfangen - beim Boot treffen
//          Clear-Screen + die ersten (mehrbyteigen UTF-8-)Logozeichen
//          jetzt ganz am Anfang ohne vorherige "Aufwaerm"-Textzeilen auf
//          die Verbindung, anders als frueher. Konnte nicht an echter
//          Hardware verifiziert werden - bitte testen.
//   2.9.0: Zwei neue Funktionen:
//          1) Ueberlaufschutz fuer aps_known[]/clients_known[]
//          (Einstellungen 7/8): bisher wurden beide Listen beim
//          Erreichen von MAX_APS_TRACKED/MAX_CLIENTS_TRACKED
//          kommentarlos komplett geleert. Jetzt wird IMMER akustisch
//          gewarnt (3x Bell-Zeichen), und optional (je einzeln
//          schaltbar) automatisch vor dem Leeren gesichert
//          (handle_list_overflow(), Datei /overflow_<Zeitstempel>.txt)
//          und/oder automatisch auf Offline geschaltet (haelt die
//          Aufzeichnung sofort an, bewahrt die Liste unveraendert -
//          promisc_cb() bricht bei online_mode==false ohnehin schon
//          ganz am Anfang ab).
//          2) Punkt 6, Taste 'u': einfache Alternative zu Y-Modem fuer
//          Datei-Uploads PC -> ESP-SPIFFS. Zieldateiname eingeben, dann
//          wird auf die ersten Bytes gewartet und alles darunter
//          gespeichert, bis 3 Sekunden lang keine weiteren Daten mehr
//          ankommen (STATE_UPLOAD_FILENAME/STATE_UPLOAD_RECEIVING).
//          Sobald der Empfang begonnen hat, faengt menu_handle_serial()
//          jedes Byte roh ab (auch ESC/Backspace/Strg+O) und schreibt es
//          1:1 in die Datei - nur VOR dem ersten Byte funktioniert
//          Backspace/ESC noch zum Abbrechen. Warnung: bei Dateien, deren
//          allererstes Byte zufaellig genau 27 (ESC), 8 oder 127
//          (Backspace) ist, wuerde das faelschlich als Abbruch gewertet
//          - fuer die vorgesehenen Text-/Konfigdateien unkritisch.
//          [Entfernt in v2.30.52 zur Reduzierung der Binaergroesse -
//          Compiler-Fehler "dangerous relocation: j: cannot encode"
//          durch zu grosses Sketch-Binary. Menue 6/Taste 'u',
//          STATE_UPLOAD_FILENAME/STATE_UPLOAD_RECEIVING sowie alle
//          zugehoerigen Funktionen/Variablen wurden komplett entfernt.]
//   2.10.0: Nutzer-Feedback zu ntfy + drei neue Funktionen:
//          - Bugfix: zweiter ntfy-Versand in Folge schlug regelmaessig
//          fehl ("WLAN-Verbindung fehlgeschlagen"), erst ein Neustart
//          half wieder. Vermutete Ursache: der Funk blieb nach der
//          vorherigen Promiscuous-Reaktivierung in einem Zwischenzustand
//          haengen. Fix: vollstaendiger Moduswechsel WIFI_OFF -> WIFI_STA
//          (statt nur WiFi.mode(WIFI_STA)) vor jedem Verbindungsversuch,
//          sowohl in notif_send_now() als auch im neuen sync_ntp_time().
//          - ntfy: neuer Inhaltsmodus "Alle Access Points der Hauptliste"
//          (sendet die AP-Liste statt der Client-Liste).
//          - Drei vom Nutzer lokal geänderte Zeilen uebernommen:
//          User-Agent "Firefly-WiFi-Monitor", Credit-Zeile auf der
//          Info-Seite exakt angepasst, Hinweis auf Taste E im
//          Einstellungsmenue auskommentiert (macht die Funktion
//          "versteckter").
//          - Neu: Einstellungen > 9) NTP-Zeitsynchronisation. Eigene
//          WLAN-SSID/Passwort + NTP-Server + Ein/Aus. sync_ntp_time()
//          laeuft beim Boot VOR dem Aktivieren des Promiscuous-Sniffings
//          (braucht kurzzeitig eine normale WLAN-Verbindung, daher keine
//          Pausier-Logik wie bei notif_send_now() noetig). current_
//          unix_time() liefert die laufend fortgeschriebene Unix-Zeit
//          (ueber millis()-Versatz seit der Synchronisation) fuer
//          kuenftige Zeitstempel/zeitabhaengige Funktionen. Aktueller
//          Sync-Status + Uhrzeit werden auf der Info-Seite angezeigt.
//          Hinweis: eine konkrete Regel fuer "uhrzeitabhaengige ntfy-
//          Benachrichtigung" wurde noch nicht spezifiziert und daher
//          noch nicht umgesetzt - die Zeitbasis dafuer steht aber schon
//          bereit.
//          - Neu: Hidden Settings > 2) Werkseinstellungen wiederher-
//          stellen, mit Sicherheitsabfrage (Eingabe von "LOESCHEN" +
//          Enter erforderlich). perform_factory_reset() schaltet zuerst
//          das Sniffing taub (wifi_promiscuous_enable(disable)), loescht
//          danach ALLE Dateien im SPIFFS, setzt alle Einstellungen auf
//          ihre Standardwerte zurueck und bleibt anschliessend mit einer
//          Abschlussmeldung in einer Endlosschleife stehen (manueller
//          Neustart erforderlich - es gibt keinen sauberen Soft-Reset-
//          Aufruf in diesem Sketch, ein bewusster manueller Neustart ist
//          hier ohnehin sicherer).
//   2.12.0: Major Update - Bugs behoben + Timezone/Auto-Save:
//          BUGFIXES:
//          - NTP-Scanner-Bug: Nach NTP-Sync komplette Promiscuous Re-Init
//            (wifi_promiscuous_enable/disable + Kanal setzen + Callback)
//          - SSID-Bündelung (S+Zahl): Funktioniert wieder korrekt - zeigt
//            alle APs mit gleicher SSID wie vorgesehen (Roaming-Verfolgung)
//          - Multi-AP-Auswahl (S+Zahl,Zahl): Nur Clients der gewählten
//            APs, nicht vermischt mit SSID-Logik
//          - Punkt-3-Format Konsistenz: Alle NTFY-Ausgaben folgen jetzt
//            exakt dem Terminal-Format (MAC, ch/AP, age, RSSI)
//          - Refresh-Persistierung: Anzeigemodus bleibt über Aktualisierung
//            erhalten (Modus 1/2/3 mit Parametern)
//          FEATURES:
//          - Zeitzone (UTC-Offset, -12..12) und Daylight Saving Time (DST,
//            automatische Sommer-/Winterzeit nach EU-Regel): Einstellbar in
//            Punkt e→9 Taste 5/6, wird auf alle Zeit-Ausgaben angewendet
//            (Terminal + NTFY)
//          - Auto-Save täglich: Bei NTP um 00:00 Uhr, sonst 24h-Timer.
//            Format: Zeitstempel im Dateinamen. Ohne NTP: Clients-APs-Millis
//          - NTFY Terminal-Export: \"Alle APs\", \"Eine SSID\", \"Multi-SSID\"
//            nutzen alle jetzt das Terminal-Display-Format
//   2.13.0: Weitere Features + Deklarationen-Fix:
//          FEATURES:
//          - Dynamische SSID-Länge: Berechnet längsten Namen in Liste
//            (statt feste 32 Zeichen), spart Platz in Ausgabe
//          - Channel-Filter (Hidden E3): Nutzer kann \"alle\" oder \"1,6,11\"
//            eingeben, Scanner überspringt nicht-gefilterte Kanäle
//          - Scan-Verweilzeit (Hidden E4): Millisekunden pro Kanal ein-
//            stellbar (Standard 100ms, Bereich 10-5000ms)
//          BUGFIX:
//          - Funktionsdeklarationen: Alle neuen Funktionen werden jetzt
//            VOR ihrem ersten Aufruf deklariert (nicht dahinter), um
//            Kompilierungsfehler zu vermeiden
//
// Terminal: TeraTerm oder aehnliches mit VT100/ANSI-Unterstuetzung
// erforderlich (der Standard-Arduino-Serial-Monitor kann KEINE
// Escape-Sequenzen darstellen).
// =====================================================================

#include <ESP8266WiFi.h>
// NEU 2.30.3 RAM-FIX: HTTP_UPLOAD_BUFLEN MUSS vor dem Include von
// ESP8266WebServer.h definiert werden (die Bibliothek nutzt intern
// "#ifndef HTTP_UPLOAD_BUFLEN #define HTTP_UPLOAD_BUFLEN 2048 #endif").
// Der Standardwert von 2048 Byte ist ein fest in der HTTPUpload-Struktur
// eingebettetes uint8_t-Array (Teil des per "new" angelegten Server-
// Objekts, siehe menu_enter_http_server()) - bei nur wenigen KByte freiem
// Heap kann das alleine schon zum Absturz waehrend eines Uploads fuehren
// (vom Nutzer bestaetigt: Crash bei ~8 KB freiem Heap, funktioniert ab
// ~20 KB). Kleinerer Puffer = kleinerer Speicherblock, dafuer wird der
// WRITE-Callback (http_handle_upload_data()) entsprechend oefter mit
// kleineren Haeppchen aufgerufen - das kostet nur etwas mehr Flash-
// Schreibvorgaenge, keine zusaetzliche Funktionalitaet geht verloren.
// Bei Bedarf hier weiter absenken (z.B. 128), falls der freie Heap noch
// knapper ist; 256 Byte sind ein guter Kompromiss zwischen RAM-Ersparnis
// und Anzahl der Flash-Schreibvorgaenge.
#define HTTP_UPLOAD_BUFLEN 128
#include <ESP8266WebServer.h>  // NEU 2.30.0: Punkt 7, HTTP-Datei-Server. Wird
                               // nur waehrend Punkt 7 per "new" instanziiert
                               // (siehe g_http_server), kostet also im
                               // normalen Sniffing-Betrieb kein RAM.
#include <FS.h>
#include <LittleFS.h>   // NEU 2.24.0: Umstellung von SPIFFS auf LittleFS -
                        // echte O(1)-Seeks statt SPIFFS-Seitenketten-Scan,
                        // behebt den mit Debug-Logging nachgewiesenen
                        // Offset-abhaengigen Lese-/Seek-Overhead (siehe
                        // Changelog 2.24.0 weiter unten).
#include <time.h>       // fuer NTP-Zeitsynchronisation (configTime()/time())
#include <ctype.h>
#include <stdarg.h>

// ============================================================
// VendorLookup.h – MAC-Herstellererkennung (v2.22.0)
// EINGEBETTET: Keine separate .h Datei nötig
//
// NEU 2.22.0 GESCHWINDIGKEITSOPTIMIERUNG:
// Die drei MAC-Adresslisten (mac_5/6/7byte.bin) bekommen jetzt jeweils
// eine eigene Block-Index-Datei, nach demselben Prinzip wie schon bei
// vendors.txt/vendor_index.bin: Anstatt per klassischer Binaersuche
// mit log2(N) einzelnen Flash-Lesezugriffen direkt in der (teils sehr
// grossen) MAC-Liste zu suchen, wird zuerst in der viel kleineren
// Index-Datei (fast beliebig schnell, da sie um ein Vielfaches kleiner
// ist) der passende Block ermittelt ("Block oder naechstkleiner").
// Danach wird genau EIN Lesevorgang gemacht, der den kompletten Block
// (so gross bemessen, dass er in einen einzigen Read passt) ins RAM
// laedt. Die eigentliche Treffersuche findet dann nur noch im RAM
// statt - kein weiterer Flash-Zugriff mehr noetig. Die Index-Dateien
// werden beim ersten Start automatisch erzeugt, falls die zugehoerige
// MAC-Liste vorhanden, die Index-Datei aber noch fehlt.
// ============================================================

#define INDEX_STEP 250

// Blockgroesse fuer die MAC-Index-Dateien: so gewaehlt, dass ein Block
// bequem mit einem einzigen f.read() eingelesen werden kann (analog zum
// 512-Byte-Puffer bei der vendors.txt-Indizierung).
#define MAC_INDEX_BLOCK_BYTES 512

class VendorLookup {
public:
    static void begin() {
        if (LittleFS.exists("/vendors.txt") && !LittleFS.exists("/vendor_index.bin")) {
            generateVendorIndex();
        }
        // 36-Bit (MA-S/CID), 5-Byte-Praefix, 7-Byte-Records
        generateMacIndex("/mac_7byte.bin", "/mac7_index.bin", 5, 7);
        // 28-Bit (MA-M), 4-Byte-Praefix, 6-Byte-Records
        generateMacIndex("/mac_6byte.bin", "/mac6_index.bin", 4, 6);
        // 24-Bit (MA-L), 3-Byte-Praefix, 5-Byte-Records
        generateMacIndex("/mac_5byte.bin", "/mac5_index.bin", 3, 5);
    }

    // NEU 2.26.1: optionaler Ausgabeparameter outOffset liefert bei Treffer
    // den Byte-Offset der Zeile in vendors.txt zurueck (fuer Vendor-Cache).
    // Default nullptr -> bestehende Aufrufer (ohne Offset-Bedarf) unveraendert.
    static String getManufacturer(String mac, uint32_t *outOffset = nullptr) {
        uint8_t macBytes[6];
        // NEU 2.28.1 RAM-Optimierung: fester Stack-Puffer statt String += in
        // einer Schleife. String += alloziert bei JEDEM angehaengten Zeichen
        // neu (bis zu 12x pro Aufruf) - bei vielen aufeinanderfolgenden
        // Lookups (z.B. ntfy-Versand mit Vendor-Lookup fuer hunderte
        // Geraete, VENDOR_CACHE_MAX=50 also meist Cache-Miss) summierte sich
        // das zu massiver Heap-Fragmentierung bis zum RAM-Crash/Watchdog-Reset.
        char cleanMac[13];
        int cleanLen = 0;


        for (unsigned int i = 0; i < mac.length() && cleanLen < 12; i++) {
            char c = mac.charAt(i);
            if (isHexadecimalDigit(c)) cleanMac[cleanLen++] = (char)toupper(c);
        }
        cleanMac[cleanLen] = '\0';

        if (cleanLen < 12) {
            return F("---");
        }

        for (int i = 0; i < 6; i++) {
            macBytes[i] = (hexNibble(cleanMac[i * 2]) << 4) | hexNibble(cleanMac[i * 2 + 1]);
        }


        // 36-Bit-Praefix (MA-S/CID): 5 Bytes, aber nur oberes Nibble von Byte 5
        // gehoert zum Praefix -> maskLastNibble = true
        String result = binarySearchMacFile("/mac_7byte.bin", "/mac7_index.bin", macBytes, 5, 7, true, outOffset);
        if (result.length() > 0 && result != "---") {
            return result;
        }

        // 28-Bit-Praefix (MA-M): 4 Bytes, aber nur oberes Nibble von Byte 4
        // gehoert zum Praefix -> maskLastNibble = true
        result = binarySearchMacFile("/mac_6byte.bin", "/mac6_index.bin", macBytes, 4, 6, true, outOffset);
        if (result.length() > 0 && result != "---") {
            return result;
        }

        // 24-Bit-Praefix (MA-L / klassisches OUI): 3 volle Bytes, exakter
        // Vergleich korrekt -> maskLastNibble = false
        result = binarySearchMacFile("/mac_5byte.bin", "/mac5_index.bin", macBytes, 3, 5, false, outOffset);
        if (result.length() > 0 && result != "---") {
            return result;
        }

        return F("---");
    }

private:
    static uint8_t hexNibble(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        return 0;
    }

    static void generateVendorIndex() {
        File textFile = LittleFS.open("/vendors.txt", "r");
        File binFile = LittleFS.open("/vendor_index.bin", "w");
        if (!textFile || !binFile) {
            if (textFile) textFile.close();
            if (binFile) binFile.close();
            return;
        }

        // NEU 2.28.3 RAM-Fix: Dieser Pfad laeuft GENAU EINMAL, ganz am Anfang
        // des Boots (nur beim allerersten Start, solange vendor_index.bin
        // noch nicht existiert) - zu diesem Zeitpunkt ist der Aufrufpfad
        // flach (direkt aus begin()/setup()), ein Stack-Overflow-Risiko wie
        // beim Laufzeit-Vendor-Lookup (siehe blockBuf) besteht hier nicht.
        // "static" reservierte diese 512 Byte bisher fuer die GESAMTE
        // restliche Laufzeit, obwohl die Funktion danach nie wieder
        // aufgerufen wird - reiner Verlust. Jetzt normaler Stack-Puffer,
        // der nach dem einmaligen Aufruf sofort wieder freigegeben ist.
        uint8_t buffer[512];
        uint32_t currentByteOffset = 0;
        uint32_t currentLine = 1;
        uint32_t offset = 0;

        binFile.write((const uint8_t*)&offset, sizeof(uint32_t));

        while (textFile.available()) {
            size_t bytesRead = textFile.read(buffer, sizeof(buffer));
            for (size_t i = 0; i < bytesRead; i++) {
                if (buffer[i] == '\n') {
                    currentLine++;
                    if ((currentLine - 1) % INDEX_STEP == 0) {
                        uint32_t newOffset = currentByteOffset + i + 1;
                        binFile.write((const uint8_t*)&newOffset, sizeof(uint32_t));
                    }
                }
            }
            currentByteOffset += bytesRead;
            yield();
        }

        textFile.close();
        binFile.close();
    }

    // NEU 2.26.1: optionaler Ausgabeparameter outOffset liefert bei Treffer
    // den Byte-Offset zurueck, an dem die Zeile in vendors.txt BEGINNT
    // (nicht die Zeilennummer) - wird waehrend des Scans mitgefuehrt, indem
    // bei jedem '\n' die Position des naechsten Zeichens als neuer
    // Zeilenstart notiert wird. Kostet keinen zusaetzlichen Dateizugriff.
    static String getVendorByLineNumber(uint32_t targetLine, uint32_t *outOffset = nullptr) {

        if (targetLine == 0) return F("---");

        File binFile = LittleFS.open("/vendor_index.bin", "r");
        if (!binFile) return F("---");

        uint32_t indexEntry = (targetLine - 1) / INDEX_STEP;

        if (binFile.seek(indexEntry * sizeof(uint32_t))) {
            uint32_t startByteOffset = 0;

            if (binFile.read((uint8_t*)&startByteOffset, sizeof(uint32_t)) != sizeof(uint32_t)) {
                binFile.close();
                return F("---");
            }
            binFile.close();

            File f = LittleFS.open("/vendors.txt", "r");
            if (!f) return F("---");

            f.seek(startByteOffset);

            uint32_t currentLine = (indexEntry * INDEX_STEP) + 1;
            // NEU 2.28.3 RAM-Fix: statt "static" (dauerhaft in .bss reserviert,
            // auch wenn gerade kein Lookup laeuft) jetzt malloc()/free() - nur
            // waehrend des eigentlichen Lookups belegt. Stack-Sicherheit bleibt
            // erhalten (Heap statt Stack, wie beim urspruenglichen Umstieg auf
            // "static" beabsichtigt), aber die 256 Byte sind ausserhalb eines
            // Lookups wieder fuer anderes RAM verfuegbar.
            const size_t bufSize = 256;
            uint8_t *buffer = (uint8_t*) malloc(bufSize);
            if (!buffer) { f.close(); return F("---"); }
            String lineStr = "";
            // NEU 2.26.1: laufende Byte-Position + Startoffset der aktuellen Zeile
            uint32_t currentBytePos = startByteOffset;
            uint32_t lineStartOffset = startByteOffset;

            while (f.available()) {
                size_t bytesRead = f.read(buffer, bufSize);

                for (size_t i = 0; i < bytesRead; i++) {
                    char c = (char)buffer[i];
                    if (c == '\n') {
                        if (currentLine == targetLine) {
                            lineStr.trim();
                            f.close();
                            free(buffer);
                            if (outOffset) *outOffset = lineStartOffset;
                            return lineStr;
                        }
                        currentLine++;
                        lineStr = "";
                        // Naechste Zeile beginnt direkt nach diesem '\n'
                        lineStartOffset = currentBytePos + i + 1;
                    }
                    else if (c != '\r') {
                        if (currentLine == targetLine) {
                            lineStr += c;
                        }
                    }
                }
                currentBytePos += bytesRead;
                yield();
            }

            f.close();
            free(buffer);
            return F("---");
        }

        binFile.close();
        return F("---");
    }

    // Vergleicht targetBytes[0..macPrefixLen-1] mit buffer[0..macPrefixLen-1].
    // Bei maskLastNibble=true wird vom letzten Byte des Praefix nur das
    // obere Nibble verglichen (fuer 28-Bit- bzw. 36-Bit-IEEE-Bloecke, bei
    // denen das untere Nibble bereits zum Geraeteanteil der MAC gehoert
    // und in der Index-Datei auf 0 normiert gespeichert ist).
    static int compareMacPrefix(const uint8_t* targetBytes, const uint8_t* buffer, int macPrefixLen, bool maskLastNibble) {
        int fullBytes = maskLastNibble ? (macPrefixLen - 1) : macPrefixLen;
        int cmp = memcmp(targetBytes, buffer, fullBytes);
        if (cmp != 0) return cmp;

        if (maskLastNibble) {
            uint8_t t = targetBytes[macPrefixLen - 1] & 0xF0;
            uint8_t b = buffer[macPrefixLen - 1] & 0xF0;
            if (t < b) return -1;
            if (t > b) return 1;
        }
        return 0;
    }

    // Anzahl Records pro Block: so viele, wie in MAC_INDEX_BLOCK_BYTES
    // hineinpassen (immer mindestens 1).
    static int blockRecordCount(int recordSize) {
        int n = MAC_INDEX_BLOCK_BYTES / recordSize;
        return (n < 1) ? 1 : n;
    }

    // Erzeugt die Block-Index-Datei fuer eine MAC-Liste, falls die MAC-
    // Liste existiert, die Index-Datei aber noch fehlt. Pro Block wird
    // der Schluessel (die ersten macPrefixLen Bytes) des jeweils ersten
    // Records im Block zusammen mit dessen Byte-Offset in der MAC-Liste
    // abgelegt (Record: [macPrefixLen Byte Schluessel][4 Byte Offset]).
    static void generateMacIndex(const String& macFileName, const String& indexFileName, int macPrefixLen, int recordSize) {
        if (!LittleFS.exists(macFileName)) return;
        if (LittleFS.exists(indexFileName)) return;

        File macFile = LittleFS.open(macFileName, "r");
        File idxFile = LittleFS.open(indexFileName, "w");
        if (!macFile || !idxFile) {
            if (macFile) macFile.close();
            if (idxFile) idxFile.close();
            return;
        }

        size_t fileSize = macFile.size();
        long totalRecords = fileSize / recordSize;
        int blkRecords = blockRecordCount(recordSize);

        uint8_t keyBuf[5];  // max. macPrefixLen ist 5 (7-Byte-Records)

        for (long recStart = 0; recStart < totalRecords; recStart += blkRecords) {
            uint32_t offset = (uint32_t)(recStart) * (uint32_t)recordSize;
            macFile.seek(offset);
            macFile.read(keyBuf, macPrefixLen);
            idxFile.write(keyBuf, macPrefixLen);
            idxFile.write((const uint8_t*)&offset, sizeof(uint32_t));
            yield();
        }

        macFile.close();
        idxFile.close();
    }

    // Sucht in der (kleinen) Index-Datei per Binaersuche den Block, dessen
    // Start-Schluessel <= targetBytes ist und am naechsten an targetBytes
    // herankommt ("Block oder naechstkleiner"). Liefert per Referenz den
    // Byte-Offset des Blocks in der zugehoerigen MAC-Liste. Rueckgabe
    // false, wenn targetBytes kleiner als der allererste Schluessel ist
    // (dann kann kein Treffer existieren) oder die Index-Datei fehlt.
    //
    // NEU 2.22.2 PERF-FIX: Der Treffer-Puffer der Binaersuche wird direkt
    // beim Update von bestIdx mitgesichert (bestBuf) - dadurch entfaellt
    // der komplette zweite seek()+read() nach der Schleife, der vorher
    // (voellig unnoetig) den gleichen Eintrag nochmal gelesen hat.
    static bool findBlockOffset(const String& indexFileName, const uint8_t* targetBytes, int macPrefixLen, bool maskLastNibble, uint32_t& blockOffsetOut) {

        File idx = LittleFS.open(indexFileName, "r");
        if (!idx) {
            return false;
        }

        int entrySize = macPrefixLen + 4;
        size_t idxSize = idx.size();
        long totalEntries = idxSize / entrySize;

        if (totalEntries == 0) {
            idx.close();
            return false;
        }

        long low = 0, high = totalEntries - 1;
        long bestIdx = -1;
        uint8_t buf[9];       // max. entrySize ist 5+4=9
        uint8_t bestBuf[9];

        while (low <= high) {
            long mid = low + (high - low) / 2;
            idx.seek((uint32_t)mid * entrySize);
            idx.read(buf, entrySize);

            int cmp = compareMacPrefix(targetBytes, buf, macPrefixLen, maskLastNibble);

            if (cmp == 0) {
                bestIdx = mid;
                memcpy(bestBuf, buf, entrySize);
                break;
            } else if (cmp < 0) {
                high = mid - 1;
            } else {
                bestIdx = mid;
                memcpy(bestBuf, buf, entrySize);  // Kandidat sichern, ohne spaeteres Re-Read
                low = mid + 1;
            }
        }

        idx.close();

        if (bestIdx < 0) {
            return false;
        }

        uint32_t offset;
        memcpy(&offset, bestBuf + macPrefixLen, sizeof(uint32_t));
        blockOffsetOut = offset;
        return true;
    }

    // Ermittelt den Hersteller-Zeilenindex zu einer MAC ueber die Block-
    // Index-Datei: 1) Block per Binaersuche in der (kleinen) Index-Datei
    // finden, 2) genau EINEN Lesevorgang machen, der den kompletten Block
    // ins RAM laedt, 3) Treffersuche nur noch im RAM (kein weiterer
    // Flash-Zugriff).
    //
    // NEU 2.22.2 PERF-FIX: Keine LittleFS.exists()-Vorabchecks mehr - auf dem
    // ESP8266 ist LittleFS.open()/.exists() selbst teuer (Objektregister-Scan
    // im Flash), vorher wurden pro Suche bis zu 4 solcher Zugriffe gemacht
    // (exists(file), exists(index), open(index), open(file)) statt noetiger
    // 2 (open(index), open(file)). Das war der Hauptgrund fuer "langsamer
    // statt schneller", nicht die Blocklogik selbst.
    //
    // NEU 2.22.2 SICHERHEITSNETZ: Falls der Treffer nicht im gefundenen
    // Block liegt, wird zusaetzlich noch der erste Record des naechsten
    // Blocks geprueft (ein einzelner kleiner Read, nur im Nicht-Treffer-
    // Fall). Rein rechnerisch kann das bei sortierten, eindeutigen Block-
    // Grenzen nicht vorkommen, kostet aber im Erfolgsfall (Normalfall)
    // nichts extra und faengt Rand- bzw. Datenanomalien kostenguenstig ab.
    // NEU 2.26.1: optionaler Ausgabeparameter outOffset (durchgereicht von
    // getManufacturer) fuer den Byte-Offset der Treffer-Zeile in vendors.txt.
    static String binarySearchMacFile(const String& fileName, const String& indexFileName, const uint8_t* targetBytes, int macPrefixLen, int recordSize, bool maskLastNibble, uint32_t *outOffset = nullptr) {
        uint32_t blockOffset = 0;
        bool haveBlock = findBlockOffset(indexFileName, targetBytes, macPrefixLen, maskLastNibble, blockOffset);

        File f = LittleFS.open(fileName, "r");
        if (!f) {
            return "";
        }

        if (!haveBlock) {
            // Fallback (z.B. Index-Datei fehlt/konnte nicht erzeugt werden,
            // oder Target kleiner als der allererste Eintrag): klassische
            // Binaersuche direkt in der MAC-Liste.
            size_t fileSize = f.size();
            long totalRecords = fileSize / recordSize;
            long low = 0, high = totalRecords - 1;
            uint8_t buffer[7];

            while (low <= high) {
                long mid = low + (high - low) / 2;
                f.seek((uint32_t)mid * recordSize);
                f.read(buffer, recordSize);
                int cmp = compareMacPrefix(targetBytes, buffer, macPrefixLen, maskLastNibble);
                if (cmp == 0) {
                    uint8_t byte0 = buffer[macPrefixLen];
                    uint8_t byte1 = buffer[macPrefixLen + 1];
                    uint16_t lineIndex_BE = (byte0 << 8) | byte1;
                    f.close();
                    return getVendorByLineNumber(lineIndex_BE, outOffset);
                }
                if (cmp < 0) high = mid - 1; else low = mid + 1;
            }
            f.close();
            return "";
        }

        size_t fileSize = f.size();
        int blkRecords = blockRecordCount(recordSize);
        size_t bytesToRead = (size_t)blkRecords * recordSize;
        size_t bytesRemaining = fileSize - blockOffset;
        if (bytesToRead > bytesRemaining) bytesToRead = bytesRemaining;

        // NEU 2.28.3 RAM-Fix: statt "static" (dauerhaft in .bss reserviert -
        // 512 Byte, die 99% der Laufzeit ungenutzt herumlagen) jetzt
        // malloc()/free() - Stack-Sicherheit bleibt erhalten (Heap statt
        // Stack, derselbe Grund wie beim urspruenglichen Umstieg auf
        // "static", s. Kommentar oben), aber die 512 Byte sind ausserhalb
        // eines Lookups wieder fuer anderes RAM verfuegbar. Freigabe direkt
        // nach der Block-Suche (Treffer oder nicht) - der nachfolgende
        // Sicherheitsnetz-Codeblock braucht blockBuf nicht mehr.
        uint8_t *blockBuf = (uint8_t*) malloc(MAC_INDEX_BLOCK_BYTES);
        if (!blockBuf) { f.close(); return ""; }
        f.seek(blockOffset);
        size_t actuallyRead = f.read(blockBuf, bytesToRead);

        int recordsInBlock = actuallyRead / recordSize;

        long low = 0, high = recordsInBlock - 1;
        while (low <= high) {
            long mid = low + (high - low) / 2;
            uint8_t* rec = blockBuf + (mid * recordSize);
            int cmp = compareMacPrefix(targetBytes, rec, macPrefixLen, maskLastNibble);

            if (cmp == 0) {
                uint8_t byte0 = rec[macPrefixLen];
                uint8_t byte1 = rec[macPrefixLen + 1];
                uint16_t lineIndex_BE = (byte0 << 8) | byte1;
                f.close();
                free(blockBuf);
                return getVendorByLineNumber(lineIndex_BE, outOffset);
            }

            if (cmp < 0) high = mid - 1;
            else low = mid + 1;
        }
        free(blockBuf);  // ab hier nicht mehr benoetigt (Sicherheitsnetz liest direkt aus der Datei)

        // Sicherheitsnetz (siehe Kommentar oben): ersten Record des naechsten
        // Blocks pruefen, falls noch einer folgt. Kostet nur im Nicht-Treffer-
        // Fall einen einzigen kleinen Read.
        size_t nextBlockOffset = blockOffset + actuallyRead;
        if (nextBlockOffset < fileSize) {
            uint8_t nextRec[7];
            f.seek(nextBlockOffset);
            size_t got = f.read(nextRec, recordSize);
            f.close();
            if (got == (size_t)recordSize && compareMacPrefix(targetBytes, nextRec, macPrefixLen, maskLastNibble) == 0) {
                uint8_t byte0 = nextRec[macPrefixLen];
                uint8_t byte1 = nextRec[macPrefixLen + 1];
                uint16_t lineIndex_BE = (byte0 << 8) | byte1;
                return getVendorByLineNumber(lineIndex_BE, outOffset);
            }
            return "";
        }

        f.close();
        return "";
    }
};

// =====================================================================
// NEU 2.26.0: VENDOR CACHE - Temporaerer, RAM-sparsamer Lookup-Cache
// =====================================================================
// Datenstruktur fuer einen Cache-Eintrag (10 Byte pro Eintrag)
struct VendorCacheEntry {
    uint8_t mac[6];           // Vollstaendige MAC-Adresse (Kollisionssicherheit)
    uint32_t vendorTextOffset; // Byte-Offset direkt in vendors.txt (NOT Zeilennummer)
};

// Globale Variablen für Cache-Verwaltung (nur Zeiger + Zaehler, der Datenblock ist dynamisch)
VendorCacheEntry *g_vendorCache = NULL;
int g_vendorCacheCount = 0;
const int VENDOR_CACHE_MAX = 50;  // Harte Obergrenze
const uint32_t VENDOR_CACHE_NOT_FOUND = 0xFFFFFFFF;  // Sentinel für Negativ-Caching
// BUGFIX 2.26.3: Guard-Flag gegen wiederholtes Zuruecksetzen bei jedem
// Redraw (siehe vendorCache_begin() fuer Details).
bool g_vendorCacheSessionActive = false;

// Forward-Deklarationen der Cache-Funktionen (VOR ihren Implementierungen)
void vendorCache_begin();
void vendorCache_end();
String vendorCache_lookup_or_search(uint8_t *mac);
void vendorCache_add_entry(uint8_t *mac, uint32_t offset);
int vendorCache_lookup(uint8_t *mac, uint32_t &outOffset);
String readVendorLineAtOffset(uint32_t offset);
// NEU 2.26.1: getVendorByLineNumberWithOffset() entfernt - der Offset wird
// stattdessen ueber den optionalen Parameter uint32_t* outOffset an
// VendorLookup::getManufacturer()/binarySearchMacFile()/getVendorByLineNumber()
// selbst durchgereicht (siehe VendorLookup-Klasse oben). Vermeidet doppelte,
// potenziell divergierende Suchlogik.

// ---------------------------------------------------------------
// Globale Variablen für Vendor-Anzeige (v2.21.0)
// ---------------------------------------------------------------
bool show_vendors_in_menu3a = false;  // Session-Flag für Hersteller-Anzeige
bool show_vendors_in_watchlist = false;  // NEU 2.23.0: Session-Flag für Hersteller-Anzeige in Menue 4 (Watchlist)

// =====================================================================
// NEU 2.27.1 REQ-4: RUECKKEHR-SIGNALISIERUNG (Menue 4 / Watchlist)
// =====================================================================
// Nutzt bewusst die BESTEHENDE Signalisierungspin-Infrastruktur
// (signal_pin/signal_enabled/signal_active_low/signal_write_digital()) -
// keine parallele Pin-Konfiguration. Nur ein zweites, unabhaengiges
// Non-Blocking-Zeitfenster (analog zum bereits vorhandenen Boot-Puls),
// da Boot-Puls und Rueckkehr-Puls unterschiedliche Dauer/Ausloeser haben
// und sich sonst gegenseitig ueberschreiben koennten, wenn sie zufaellig
// gleichzeitig aktiv waeren.
bool enable_return_pulse = false;   // Menue 4: Ein/Aus (Taste 'p'), Default AUS
uint32_t return_pulse_start_time_ms = 0;
bool return_pulse_active = false;
#define RETURN_PULSE_DURATION_MS 5   // 5ms Impulsdauer, 1ms Aufloesung reicht (millis())

// Pro-Eintrag-Zustand fuer die Flankenerkennung ("noch out"->aktiv bzw.
// Age-Drop von >999s). Wird ERST beim Eintritt in Menue 4 dynamisch
// alloziert (0 Eintraege) und beim Verlassen wieder komplett freigegeben -
// keine feste Vorab-Reservierung. Schluesselt ueber die MAC (nicht den
// Array-Index), da Loeschen in der Watchlist nachfolgende Eintraege nach
// vorne verschiebt (memmove-artig) und ein indexbasierter Abgleich sonst
// nach einem Loeschvorgang den falschen Eintrag treffen wuerde.
// last_age == WATCHLIST_PULSE_WAS_OUT (Sentinel) bedeutet: beim letzten
// Redraw war der Eintrag "(noch out)" - spart ein eigenes bool-Feld.
#define WATCHLIST_PULSE_WAS_OUT 0xFFFFFFFFUL
struct WatchlistPulseEntry {
  uint8_t mac[6];
  uint32_t last_age;
};
WatchlistPulseEntry *g_watchlistPulseState = NULL;
int g_watchlistPulseStateCount = 0;
bool g_watchlistPulseSessionActive = false;  // Guard gegen Reset bei jedem Redraw (siehe vendorCache_begin() fuer dieselbe Problematik/Loesung)
// NEU 2.26.x: eigenes Session-Flag fuer Menue 3 (AP-/SSID-Uebersicht) - hier
// werden APs, nicht Clients, angezeigt, daher separates Flag statt
// show_vendors_in_menu3a (das gilt fuer die Geraeteliste in Menue 3a).
bool show_vendors_in_menu3 = false;

// ---------------------------------------------------------------
// Inhalt von structures.h (in einer Datei zusammengefuehrt)
// ---------------------------------------------------------------
//
// Aenderungen ggue. Original:
//   - probes_known[] entfaellt komplett (Probes werden nur noch live
//     ausgegeben, nicht mehr gespeichert) - siehe functions.ino
//   - probeinfo-Struct bleibt bestehen (wird weiterhin fuer das reine
//     Parsen/Anzeigen benoetigt)

#define ETH_MAC_LEN 6

// ================= Filter-UI-Zustand (Punkt 2, NEU 2.30.24) =================
// KOMPILIERUNGSFIX 2.30.25: urspruenglich weiter unten im Watchlist-UI-
// Abschnitt platziert - apply_live_filter()/print_filtered_frame() (weiter
// oben im Sketch, direkt vor promisc_cb()) griffen zu dem Zeitpunkt in der
// Datei aber schon auf diese Variablen zu. Anders als bei Funktionen (siehe
// Arduino-Auto-Prototypen-Kommentar bei struct watchlist_sighting weiter
// oben) generiert Arduino KEINE Vorab-Deklarationen fuer globale Variablen -
// die muessen bei diesem Sketch also selbst vor ihrer ersten Verwendung
// stehen. Deshalb jetzt ganz oben bei den uebrigen fruehen Konstanten/
// Deklarationen (gleiche Fehlerklasse wie beim watchlist_sighting-Fix,
// nur Variable statt Typ).
// Absichtlich als einfache globale Variablen (kein struct/Array-Overhead) -
// bleiben nach Nutzerwunsch dauerhaft im RAM erhalten (auch nach Verlassen
// des Menues), damit ein Zurueckkehren die Checkbox-Einstellungen behaelt.
// Bitmasken-Prinzip: Bit n gesetzt = Subtyp n dieser Kategorie aktiv. Fuer
// Management sind die Bits 4/5/8 (Probe Request/Response/Beacon) bewusst NIE
// gesetzt - die haben eigene, uebergeordnete Checkboxen (filter_sel_beacon/
// filter_sel_probe_req/_resp), analog zur mit dem Nutzer abgestimmten
// Kategorien-Aufteilung "Beacons, Probes, Management" als gleichrangige
// Geschwister.
bool filter_has_mac = false;          // true = Punkt 2.1 (MAC-bezogen), false = Punkt 2.2 (alle Geraete)
uint8_t filter_mac[ETH_MAC_LEN];
bool filter_dir_out = true;           // "abgehend" (MAC ist Sender/TA) - nur bei filter_has_mac relevant
bool filter_dir_in  = true;           // "ankommend" (MAC ist Empfaenger/RA)

bool filter_sel_beacon = false;
bool filter_sel_probe_req = false;
bool filter_sel_probe_resp = false;
uint16_t filter_mgmt_mask = 0;
uint16_t filter_ctrl_mask = 0;
uint16_t filter_data_mask = 0;

// "Sonstige/selten"-Sammelmasken je Kategorie (siehe Recherche-Tabellen):
// Management: Timing Advertisement(6), Reserved(7), Action No Ack(14), Reserved(15)
#define FILTER_MGMT_MISC_MASK (((uint16_t)1<<6)|((uint16_t)1<<7)|((uint16_t)1<<14)|((uint16_t)1<<15))
// Alle einzeln benannten Management-Bits (0,1,2,3,9,10,11,12,13) + die Sammelmaske = "alles"
#define FILTER_MGMT_FULL_MASK (((uint16_t)1<<0)|((uint16_t)1<<1)|((uint16_t)1<<2)|((uint16_t)1<<3)|((uint16_t)1<<9)|((uint16_t)1<<10)|((uint16_t)1<<11)|((uint16_t)1<<12)|((uint16_t)1<<13)|FILTER_MGMT_MISC_MASK)
// Control: Reserved(0-3), Beamforming Report Poll(4), VHT/HE NDP Announcement(5),
// Control Frame Extension(6), Control Wrapper(7), CF-End(14), CF-End+CF-Ack(15)
#define FILTER_CTRL_MISC_MASK (((uint16_t)1<<0)|((uint16_t)1<<1)|((uint16_t)1<<2)|((uint16_t)1<<3)|((uint16_t)1<<4)|((uint16_t)1<<5)|((uint16_t)1<<6)|((uint16_t)1<<7)|((uint16_t)1<<14)|((uint16_t)1<<15))
#define FILTER_CTRL_FULL_MASK (((uint16_t)1<<8)|((uint16_t)1<<9)|((uint16_t)1<<10)|((uint16_t)1<<11)|((uint16_t)1<<12)|((uint16_t)1<<13)|FILTER_CTRL_MISC_MASK)
// Data: Data+CF-Ack/-Poll-Varianten(1,2,3,5,6,7,9,10,11), Reserved(13), QoS CF-Poll/-Ack(14,15)
#define FILTER_DATA_MISC_MASK (((uint16_t)1<<1)|((uint16_t)1<<2)|((uint16_t)1<<3)|((uint16_t)1<<5)|((uint16_t)1<<6)|((uint16_t)1<<7)|((uint16_t)1<<9)|((uint16_t)1<<10)|((uint16_t)1<<11)|((uint16_t)1<<13)|((uint16_t)1<<14)|((uint16_t)1<<15))
#define FILTER_DATA_FULL_MASK (((uint16_t)1<<0)|((uint16_t)1<<4)|((uint16_t)1<<8)|((uint16_t)1<<12)|FILTER_DATA_MISC_MASK)

char filter_mac_input_buf[13];        // Eingabe von 12 Hex-Zeichen (Punkt 2.1)
int filter_mac_input_len = 0;

// NEU 2.30.29: Punkt 2.3 "MAC-Adresse nachschlagen" - eigener Eingabepuffer,
// getrennt von filter_mac_input_buf, da beide Wege (2.1-Filter und 2.3-
// Nachschlag) unabhaengig voneinander benutzt werden koennen sollen.
char lookup_mac_input_buf[13];
int lookup_mac_input_len = 0;
uint8_t lookup_mac_result_mac[ETH_MAC_LEN];  // zwischengespeichert zwischen Eingabe- und Ergebnis-Bildschirm

// NEU 2.30.29: Kanal-Lock fuer Punkt 2.1 (siehe menu_enter_filter_live()) -
// waehrend eine MAC-bezogene Live-Auswertung laeuft, wird channel_filter
// (siehe Einstellungen Punkt e) auf den bekannten Kanal dieser MAC gesperrt
// und beim Verlassen wieder auf den vorherigen Wert zurueckgesetzt.
bool channel_lock_active = false;
char saved_channel_filter[32];

// NEU 2.30.32: Punkt 2.4 "Diagnose: scharfer Timing-Test" - komplett aus der
// normalen Verarbeitung herausgeloest (siehe promisc_cb()/timing_test_
// process_packet() weiter unten): waehrend timing_test_active gesetzt ist,
// ueberspringt promisc_cb() ALS ALLERERSTES die komplette uebrige Logik
// (kein Beacon-/Client-Parsing, kein Live-Filter, kein Serial.print() pro
// Paket) - Zweck ist auszuschliessen, dass unsere eigene Verarbeitung an
// einem verpassten Empfang mitschuld sein kann. Bewusst kein Timer-Interrupt
// (siehe Ruecksprache) - ein millis()-Vergleich reicht fuer eine Sekunden-
// genaue Begrenzung voellig aus und ist ISR-frei (kein Absturzrisiko durch
// Serial-Zugriff aus einer echten Interrupt-Routine heraus).
#define TIMING_TEST_MAX_ENTRIES 40
struct timing_test_entry {
  uint32_t t_ms;    // Millisekunden seit Teststart
  uint8_t role;     // Bit0 = MAC war Sender (TA), Bit1 = MAC war Empfaenger (RA)
  uint8_t fc_byte;  // rohes Frame-Control-Low-Byte (Typ/Subtyp daraus ableitbar)
  int8_t rssi;
  uint8_t channel;
};
bool timing_test_active = false;
uint32_t timing_test_start_ms = 0;
// NEU 2.30.44: Startzeitpunkt fuer den Zeitstempel-Praefix in Punkt 2.1/2.2
// (Live-Ausgabe), analog zum bereits vorhandenen Zeitstempel in Punkt 2.4.
uint32_t filter_live_start_ms = 0;
uint32_t timing_test_duration_s = 60;  // Vorgabe, bei Bedarf spaeter per Eingabe waehlbar
uint8_t timing_test_mac[ETH_MAC_LEN];
char timing_test_mac_input_buf[13];
int timing_test_mac_input_len = 0;
timing_test_entry timing_test_log[TIMING_TEST_MAX_ENTRIES];
int timing_test_count = 0;

// NEU 2.29.8: "Offenes WLAN"-Flag im obersten Bit von beaconinfo.channel
// untergebracht (RAM-neutral - kein neues Feld/Byte). ESP8266 kennt nur
// 2,4-GHz-Kanaele 1-14 (passen in 4 Bit), Bit 7 ist also garantiert frei.
// AP_CHANNEL_MASK IMMER verwenden, wenn der reine Kanalwert gebraucht wird
// (Anzeige, Vergleich) - der rohe .channel-Wert kann sonst das Flag mit
// einschliessen. Ausnahme bewusst: die rohe Backup-Datei (DEVICE:/BEACON:-
// Zeilen) speichert/liest .channel unveraendert als einfache Zahl - das
// Flag "reist" dort automatisch mit und uebersteht Speichern/Laden 1:1,
// ohne dass an der Lade-/Schreiblogik etwas geaendert werden muss.
#define AP_OPEN_FLAG    0x80  // gesetzt = offenes WLAN (keine Verschluesselung)
// NEU 2.29.16: AP_NO_BEACON_FLAG (Platzhalter-Erkennung) wieder entfernt,
// siehe Kommentar bei den Prototypen (Platzhalter-Mechanismus rueckgebaut).
#define AP_CHANNEL_MASK 0x7F  // reiner Kanalwert ohne Flag

// NEU 2.30.21: Rueckgabetyp von find_freshest_watchlist_sighting() (siehe
// dort). Muss HIER (vor allen Funktionen) stehen, nicht erst bei der
// eigentlichen Funktionsdefinition weiter unten - Arduino generiert
// Funktionsprototypen automatisch und fuegt sie weit oben im Sketch ein;
// stand die Struct dort noch nicht zur Verfuegung, schlug das Kompilieren
// mit "watchlist_sighting does not name a type" fehl (gleiche Fehlerklasse
// wie bei clientinfo/beaconinfo weiter oben in dieser Datei behandelt).
struct watchlist_sighting {
  bool found;
  uint32_t last_heard;
  uint8_t channel;
  int8_t rssi;
};

// NEU 2.30.29: Rueckgabetyp von lookup_mac() (Punkt 2.3 "MAC-Adresse
// nachschlagen" UND fuer den Kanal-Lock von Punkt 2.1) - aus demselben
// Grund wie watchlist_sighting oben bereits HIER platziert, vor jeglicher
// Funktion.
struct mac_lookup_result {
  bool found;
  bool is_ap;      // true = MAC ist eine bekannte AP-BSSID, false = Client
  uint8_t channel; // bekannter Kanal (nur gueltig wenn found)
  int ap_idx;      // bei is_ap: Index der AP selbst in aps_known[];
                    // bei Client: Index des AP, an dem er angemeldet ist (-1 wenn unbekannt)
};

// ============================================================================
// Szenario-Kompression v1 (CSZ1) - Typen und Konstanten
// BUGFIX 2.30.51: hierher vorgezogen (urspruenglich weiter unten, direkt vor
// den Forward-Declarations) - gleiche Fehlerklasse wie schon mehrfach zuvor
// in diesem Sketch (watchlist_sighting/filter_has_mac/selected_ap_indices):
// Arduino generiert fuer JEDE gefundene Funktions-DEFINITION automatisch
// einen Prototypen ganz oben in der Datei - und das gilt nicht nur fuer den
// Rueckgabetyp, sondern genauso fuer PARAMETERTYPEN. Solange die 17
// scenario_*-Funktionen nur deklariert (kein Koerper) waren, fand der
// Scanner keine Definitionen und generierte nichts - seit sie in v2.30.50
// implementiert wurden, versucht Arduino automatisch Prototypen mit
// "ScenarioEncoder&"/"ScenarioDecoder&" als Parameter zu erzeugen, weit vor
// der bisherigen Struct-Definition weiter unten im Sketch ("ScenarioEncoder
// was not declared in this scope"). Fix: Structs (und die Konstanten, von
// denen sie abhaengen) ganz nach vorne, vor jede Funktion.
// ============================================================================
static const uint8_t SCENARIO_MAGIC_HEADER[4] = {'C','S','Z','1'};
// NEU 2.30.62: Fenster wieder von 512 auf 2048 angehoben (siehe Historie
// 2.30.54/.55 unten) - moeglich geworden durch die neue Hash-Suche in
// scenario_find_match_hash() (siehe dort), die den Zeitnachteil des
// groesseren Fensters ausgleicht. Das Bytestrom-Format aendert sich NICHT:
// das Distanzfeld im Match-Token war schon immer 11 Bit breit (0..2047,
// siehe Formatkommentar oben bei save_current_lists), Fenster 512 hat davon
// nur einen Teil ausgenutzt. Eine mit Fenster 512 gespeicherte Datei liest
// diese Firmware weiterhin korrekt (das 2048-Fenster ist nur ein groesserer
// Puffer fuer denselben Wertebereich). Umgekehrt NICHT kompatibel: eine mit
// DIESER Firmware (Fenster 2048) gespeicherte Datei kann eine 512er-
// Firmware nicht mehr fehlerfrei lesen (Distanzen >512 passen dort nicht
// in den kleineren Puffer) - relevant, falls noch Geraete mit 512er-Stand
// im Einsatz sind.
// Fruehere Notiz (2.30.54/.55, inzwischen ueberholt): Fenster testweise auf
// 512 reduziert, weil die damalige lineare Suche bei 2048 ca. 2,3-2,4x
// langsamer war. Mit der Hash-Suche entfaellt dieser Nachteil weitgehend.
static const uint16_t SCENARIO_LZSS_WINDOW = 2048;
static const uint8_t SCENARIO_LZSS_MIN_MATCH = 3;
static const uint8_t SCENARIO_LZSS_MAX_MATCH = 34;  // NEU 2.30.55: von 18 auf 34 erhoeht - das ist exakt der groesstmoegliche Wert, den das 5-Bit-Laengenfeld im Match-Token hergibt (Bits 11-15 = Laenge-MIN_MATCH, 0..31 -> 3+31=34), keine Formataenderung noetig
static const uint8_t SCENARIO_RLE_ESCAPE = 0xFF;

// NEU 2.30.62: Hash-Beschleunigung fuer die Match-Suche beim Komprimieren
// (siehe scenario_find_match_hash()). 512 Buckets a 2 Kandidaten = 2048
// Byte, direkt hinter dem 2048-Byte-Fenster in EINER zusammenhaengenden
// malloc()-Allokation in save_current_lists() (siehe dort). Nur beim
// Schreiben genutzt - der Dekoder (Laden/Anzeigen) kommt ohne Hash aus und
// braucht dafuer weiterhin nur das reine Fenster.
static const uint8_t SCENARIO_HASH_BITS = 9;
static const uint8_t SCENARIO_HASH_WAYS = 2;
static const uint16_t SCENARIO_HASH_SIZE = (uint16_t)1 << SCENARIO_HASH_BITS;      // 512 Buckets
static const uint16_t SCENARIO_HASH_BYTES = SCENARIO_HASH_SIZE * SCENARIO_HASH_WAYS * 2;  // 2048 Byte

// NEU 2.30.53 (testweise, klein): zwei einfache Zaehler zur Diagnose der
// Kompressionsrate - Rohbytes vor RLE vs. tatsaechlich an LZSS uebergebene
// Bytes nach RLE. Kein Speicher-Overhead ausser 8 Byte RAM, kein Einfluss
// auf die eigentliche Kodierung/Dekodierung. BUGFIX 2.30.53b: muessen wie
// die Structs/Konstanten oben ganz nach vorne, vor jede Funktion, die sie
// benutzt (save_current_lists() steht vor scenario_hist_put() im Sketch -
// Variablen bekommen anders als Funktionen KEINEN Auto-Prototyp von
// Arduino, siehe Kommentar zu v2.30.51 oben).
static uint32_t g_scenario_dbg_raw_bytes = 0;
static uint32_t g_scenario_dbg_rle_bytes = 0;

struct ScenarioEncoder {
  File *file; uint8_t *window; uint16_t win_pos; uint16_t hist_len;
  uint8_t look[SCENARIO_LZSS_MAX_MATCH]; uint8_t look_len;
  uint8_t flags; uint8_t token_count; uint8_t token_buf[16]; uint8_t token_len;
  bool ok; bool rle_pending; uint8_t rle_value; uint8_t rle_count;
  // NEU 2.30.62: optionale Hash-Beschleunigung. hash bleibt NULL, wenn beim
  // Speichern nicht genug zusammenhaengender RAM fuer Fenster+Hash frei war
  // (siehe save_current_lists) - scenario_lzss_step() nutzt dann weiterhin
  // die lineare Suche (langsamer, aber ohne weiteren RAM-Bedarf). abs_ctr
  // zaehlt committete Bytes fortlaufend mit (16-Bit-Ueberlauf ist unschaedlich,
  // siehe Kommentar bei scenario_find_match_hash) und dient dort als
  // Positions-ID fuer die Distanzberechnung.
  uint16_t *hash; uint16_t abs_ctr;
};

struct ScenarioDecoder {
  File *file; uint8_t *window; uint16_t win_pos; uint16_t hist_len;
  uint8_t flags; uint8_t flag_count; uint16_t match_pos; uint8_t match_left;
  bool eof; uint8_t rle_mode; uint16_t rle_left; uint8_t rle_value;
};

struct ScenarioLineReader {
  File *file;
  ScenarioDecoder *decoder;
  bool compressed;
};

struct beaconinfo
{
  // NEU 2.21.1 OPTIMIZATION: Struktur von 51 auf 48 Bytes reduziert (-6%)
  // Entfernt: capa[2] (2B, nicht genutzt), header (1B, nicht genutzt)
  uint32_t last_heard;
  
  uint8_t bssid[ETH_MAC_LEN];       // 6 Bytes: AP-MAC
  uint8_t ssid[33];                 // 33 Bytes: SSID
  uint8_t channel;                  // 1 Byte: Kanal (Bit 7 = AP_OPEN_FLAG, siehe oben)
  int8_t rssi;                      // 1 Byte: Signalstärke
  uint8_t ssid_len;                 // 1 Byte: SSID Länge
  uint8_t err;                      // 1 Byte: Error Code (wird gelesen!)
  uint8_t reported;                 // 1 Byte: Reporting Status (wird gelesen!)
} __attribute__((packed));

struct clientinfo
{
  // NEU 2.21.1 OPTIMIZATION: Struktur von 29 auf 20 Bytes reduziert (-31%)
  // Entfernt: seq_n (2B, nicht genutzt), ap[6] (6B, redundant), header (1B, nicht genutzt)
  // NEU 2.29.11 OPTIMIZATION (Etappe 3): bssid[6] (redundant - der AP steht
  // ja bereits vollstaendig in aps_known[]) durch ap_idx (1 Byte) ersetzt -
  // 20 auf 15 Byte (-25%). ap_idx verweist auf den Index in aps_known[];
  // siehe ensure_ap_index()/find_ap_index_by_bssid(). NICHT direkt
  // vergleichen/dereferenzieren ohne vorherige Gueltigkeitspruefung
  // (< aps_known_count && !ap_slot_free()) - siehe Kommentar bei
  // ap_slot_free().
  uint32_t last_heard;

  uint8_t ap_idx;                    // 1 Byte: Index in aps_known[]
  uint8_t station[ETH_MAC_LEN];     // 6 Bytes: Client-MAC
  uint8_t channel;                  // 1 Byte: WLAN-Kanal
  int8_t rssi;                      // 1 Byte: Signalstärke
  uint8_t err;                      // 1 Byte: Error Code (wird gelesen!)
  uint8_t reported;                 // 1 Byte: Reporting Status (wird gelesen!)
} __attribute__((packed));

struct probeinfo
{
  // NEU 2.21.1 OPTIMIZATION: Struktur von ~114 auf ~95 Bytes reduziert
  // Entfernt: seq_n (2B, nicht genutzt), ap[6] (6B, nicht genutzt), header (1B, nicht genutzt)
  uint32_t last_heard;
  
  uint8_t bssid[ETH_MAC_LEN];       // 6 Bytes
  uint8_t station[ETH_MAC_LEN];     // 6 Bytes
  uint8_t ssid[33];                 // 33 Bytes
  uint8_t channel;                  // 1 Byte
  int8_t rssi;                      // 1 Byte
  uint8_t ssid_len;                 // 1 Byte
  uint8_t err;                      // 1 Byte
  uint8_t reported;                 // 1 Byte
} __attribute__((packed));

/* ==============================================
   Promiscous callback structures, see ESP manual
   ============================================== */
struct RxControl {
  signed rssi: 8;
  unsigned rate: 4;
  unsigned is_group: 1;
  unsigned: 1;
  unsigned sig_mode: 2;
  unsigned legacy_length: 12;
  unsigned damatch0: 1;
  unsigned damatch1: 1;
  unsigned bssidmatch0: 1;
  unsigned bssidmatch1: 1;
  unsigned MCS: 7;
  unsigned CWB: 1;
  unsigned HT_length: 16;
  unsigned Smoothing: 1;
  unsigned Not_Sounding: 1;
  unsigned: 1;
  unsigned Aggregation: 1;
  unsigned STBC: 2;
  unsigned FEC_CODING: 1;
  unsigned SGI: 1;
  unsigned rxend_state: 8;
  unsigned ampdu_cnt: 8;
  unsigned channel: 4;
  unsigned: 12;
};

// BUGFIX 2.30.13: legacy_length gilt laut ESP8266-SDK nur bei sig_mode==0
// (Legacy/Non-HT-Frame) als tatsaechliche Framelaenge. Bei sig_mode==1
// (802.11n/HT-Format - viele moderne Smartphones nutzen das auch fuer
// Management-Frames wie Probe Requests) ist legacy_length NICHT verlaesslich
// (haeufig 0) - dann gilt stattdessen HT_length. Bisher wurde ueberall nur
// legacy_length gelesen; bei einem HT-Probe-Request fiel dadurch reallen=0,
// die Anzeige/Datei-Ausgabe fiel auf den vollen 112-Byte-Puffer zurueck und
// zeigte SDK-Pufferreste (alte, laengere Frames) als vermeintliche
// zusaetzliche Information Elements an. Eine Stelle statt vier Kopien,
// damit der Fix nicht erneut auseinanderlaufen kann.
inline uint16_t sniffer_frame_length(const struct RxControl &rx)
{
  return rx.sig_mode == 0 ? (uint16_t)rx.legacy_length : (uint16_t)rx.HT_length;
}

struct LenSeq {
  uint16_t length;
  uint16_t seq;
  uint8_t  address3[6];
};

struct sniffer_buf {
  struct RxControl rx_ctrl;
  uint8_t buf[36];
  uint16_t cnt;
  struct LenSeq lenseq[1];
};

struct sniffer_buf2 {
  struct RxControl rx_ctrl;
  uint8_t buf[112];
  uint16_t cnt;
  uint16_t len;
};

struct control_frame {
  unsigned int ver : 2;     // protocol version (should be 0x0)
  unsigned int type : 2;    // 0x0=Management, 0x1=Control, 0x2=Data
  unsigned int subtype : 4;
};

// ---------------------------------------------------------------
// Inhalt von functions.h (Prototypen/Enums, in einer Datei
// zusammengefuehrt)
// ---------------------------------------------------------------
// include ESP8266 SDK functions
extern "C" {
#include "user_interface.h"
typedef void (*freedom_outside_cb_t)(uint8 status);
int  wifi_register_send_pkt_freedom_cb(freedom_outside_cb_t cb);
void wifi_unregister_send_pkt_freedom_cb(void);
int  wifi_send_pkt_freedom(uint8 *buf, int len, bool sys_seq);
}


struct clientinfo parse_data(uint8_t *frame, uint16_t framelen, signed rssi, unsigned channel, uint8_t *bssid_out);
struct beaconinfo parse_beacon(uint8_t *frame, uint16_t framelen, signed rssi);
struct probeinfo  parse_probe(uint8_t *frame, uint16_t framelen, signed rssi);

int register_beacon(beaconinfo beacon);
int register_client(clientinfo ci, int *out_client_index);
// register_probe entfaellt - Probes werden nicht mehr gespeichert (Schritt 1)

// NEU 2.30.42: Detailstatistik fuer genau einen ausgewaehlten Client.
// Die Funktionsprototypen verwenden nur bereits bekannte primitive Typen,
// damit die automatische Arduino-Prototyperzeugung keine spaeteren Struct-
// Definitionen vorziehen muss.
bool traffic_detail_address_match(uint8_t *frame, uint16_t frame_len,
                                   uint8_t frame_type, uint8_t frame_subtype,
                                   const uint8_t *mac);
void traffic_detail_stop();
void traffic_detail_start(int client_idx);
void traffic_detail_record(uint8_t *frame, uint16_t frame_len, uint8_t frame_type, uint8_t frame_subtype);
void traffic_detail_redraw();

void print_beacon(beaconinfo beacon);
void print_client(clientinfo ci);
void print_probe(probeinfo ci);

void promisc_cb(uint8_t *buf, uint16_t len);

// ===================== Menue-System (VT100) =====================

// VT100/ANSI Basis-Hilfsfunktionen
void vt_clear_screen();
void vt_cursor_home();

// Zustandsmaschine
enum MenuState {
  STATE_LIVE = 0,          // Punkt 1: Standardausgabe
  STATE_MENU = 1,           // Menue-Uebersicht (durch ESC/Backspace erreichbar)
  STATE_SSID_SELECT = 2,    // Punkt 3a: SSID auswaehlen
  STATE_SSID_LIST = 3,      // Punkt 3b: Geraeteliste zur gewaehlten SSID
  STATE_DEBUG_LIVE = 4,     // RESERVIERT - nicht mehr verwendet, nur zur Stabilitaet der Enum-Nummern
  STATE_SETTINGS = 5,       // Punkt e: Einstellungen
  STATE_HELP = 6,           // Punkt h: Hilfe (Programmbeschreibung, Menuepunkte)
  STATE_INFO = 9,           // Punkt i: Info (Herkunft, Version, ESP-/Speicherdaten)
  STATE_SAVE_FILENAME = 7,  // Punkt 5a: Dateinamen eingeben
  STATE_FILE_LIST = 8,      // Punkt 6: gespeicherte Dateien anzeigen/waehlen/loeschen
  STATE_HIDDEN_SETTINGS = 10,  // "E" im Einstellungsmenue (Punkt e)
  STATE_WATCHLIST = 11,        // Punkt 4: MAC-Watchlist-Ansicht
  STATE_WATCHLIST_ADD_MAC = 12,   // Punkt 4: neue MAC-Adresse eingeben
  STATE_WATCHLIST_ADD_DESC = 13,  // Punkt 4: Beschreibung dazu eingeben
  STATE_NOTIF_SETTINGS = 14,      // Einstellungen > Benachrichtigung (ntfy.sh)
  STATE_NOTIF_TEXT_EDIT = 15,     // Einstellungen > Benachrichtigung: Textfeld eingeben
  STATE_NTP_SETTINGS = 18,        // Einstellungen > NTP-Zeitsynchronisation
  STATE_NTP_TEXT_EDIT = 19,       // Einstellungen > NTP: Textfeld eingeben
  STATE_FACTORY_RESET_CONFIRM = 20,  // Hidden Settings: Werksreset-Sicherheitsabfrage
  STATE_CLEANUP = 21,          // NEU 2.17.5: Punkt m - alte Eintraege nach Alter loeschen
  STATE_ESP_RESTART_CONFIRM = 22,  // NEU 2.20.0 FEATURE 4: Hidden Settings: ESP-Neustart-Sicherheitsabfrage
  STATE_ADC_SETTINGS = 23,         // NEU 2.29.0: Einstellungen > ADC (Akkuspannung)
  STATE_BEACON_ANALYSIS = 24,      // NEU 2.29.17: Punkt 3, "w"+Zahl - Beacon-Frame-Rohanalyse
  STATE_HTTP_SERVER = 25,          // NEU 2.30.0: Punkt 7 - HTTP-Datei-Server aktiv
  STATE_APMODE_SETTINGS = 26,      // NEU 2.30.5: Einstellungen > AP-Modus
  STATE_APMODE_TEXT_EDIT = 27,     // NEU 2.30.5: Textfeld (SSID/Passwort) fuer AP-Modus
  // BUGFIX 2.30.6: STATE_CLIENT_ANALYSIS war zunaechst faelschlich auch auf
  // 25 gesetzt (Kollision mit STATE_HTTP_SERVER, das erst in v2.30.0 dazu-
  // kam und beim Einfuegen uebersehen wurde) - dadurch griff bei jedem
  // Tastendruck waehrend des Wartens der "if (menu_state == STATE_HTTP_
  // SERVER) { http_server_stop(); ... }"-Block in menu_handle_serial() und
  // sprang sofort ins Hauptmenue. Jetzt auf den naechsten freien Wert 28.
  STATE_CLIENT_ANALYSIS = 28,      // NEU 2.30.6: Menue 3a, "w"+Zahl - Client-Probe-Request-Rohanalyse

  // NEU 2.30.24: Punkt 2 "Funkverkehr gezielt untersuchen" (Filter-Untermenue)
  STATE_FILTER_MENU = 29,          // Punkt 2: Auswahl 1=nach MAC, 2=nach Pakettyp
  STATE_FILTER_MAC_INPUT = 30,     // Punkt 2.1: MAC-Adresse eingeben
  STATE_FILTER_CRITERIA = 31,      // Punkt 2.1/2.2: Checkbox-Kriterien (gemeinsamer Bildschirm)
  STATE_FILTER_SUB_PROBE = 32,     // Unterauswahl: Probe Request/Response einzeln
  STATE_FILTER_SUB_MGMT = 33,      // Unterauswahl: Management-Subtypen einzeln
  STATE_FILTER_SUB_CTRL = 34,      // Unterauswahl: Control-Subtypen einzeln
  STATE_FILTER_SUB_DATA = 35,      // Unterauswahl: Data-Subtypen einzeln
  STATE_FILTER_LIVE = 36,           // laufende gefilterte Live-Ausgabe

  // NEU 2.30.29: Punkt 2.3 "MAC-Adresse nachschlagen"
  STATE_MAC_LOOKUP_INPUT = 37,
  STATE_MAC_LOOKUP_RESULT = 38,

  // NEU 2.30.32: Punkt 2.4 "Diagnose: scharfer Timing-Test" (Debug)
  STATE_TIMING_TEST_MAC_INPUT = 39,
  STATE_TIMING_TEST_RUNNING = 40,
  STATE_TIMING_TEST_RESULT = 41,
  STATE_RAM_DEBUG = 42,              // NEU 2.30.34: Hidden Settings > Debug RAM Memory
  STATE_CALL_CHAIN_VIEW = 43,        // NEU 2.30.35: Debug RAM Memory > Call-Chain anzeigen
  STATE_TRAFFIC_STATS = 44,           // NEU 2.30.39: Hintergrundverkehr
  STATE_TRAFFIC_DETAIL = 45,           // NEU 2.30.42: Detailstatistik eines Clients
  STATE_ROAMING_GROUPS = 46,           // NEU 2.30.60: Punkt v - Versorgungsbereiche (Roaming-Gruppen)
  STATE_TIMEWATCH_ADD_DESC = 47          // NEU 2.30.67: TimeWatch-Beschreibung
};

// Muss VOR setup()/loop() deklariert sein, da setup() menu_state schon
// direkt setzt (gleiche Fehlerklasse wie startup_online/show_logo weiter
// unten: Arduino generiert automatische Prototypen nur fuer Funktionen,
// nicht fuer globale Variablen).
MenuState menu_state = STATE_LIVE;

// Sortierfelder fuer die Geraeteliste (Punkt 3)
enum SortField {
  SORT_MAC = 0,
  SORT_LASTSEEN = 1,
  SORT_RSSI = 2,
  // NEU 2.30.14: "unsortiert" fuer Menue 3a, analog AP_SORT_NONE in Menue 3.
  // Bewusst als NEUER Wert (3) angehaengt statt die bestehenden Werte
  // umzunummerieren - sort_field wird als reine Zahl in settings.cfg und in
  // gespeicherten Listen-Schnappschuessen persistiert; ein Umsortieren der
  // Werte haette dort die Bedeutung bestehender Dateien stillschweigend
  // veraendert.
  SORT_NONE = 3
};

// NEU 2.17.4: Sortierfelder fuer die AP-Uebersichtsliste (Punkt 3, SSID-
// Auswahl, menu_enter_ssid_select()). AP_SORT_NONE = unsortiert, d.h. die
// Reihenfolge, in der die APs auch in Punkt 1 (Standardausgabe) auftauchen.
enum ApSortField {
  AP_SORT_NONE  = 0,
  AP_SORT_SSID  = 1,
  AP_SORT_COUNT = 2,
  AP_SORT_RSSI  = 3,
  AP_SORT_AGE   = 4,  // NEU 2.27.4
  AP_SORT_MAC   = 5   // NEU 2.27.4
};

// BUGFIX 2.30.47: explizite Prototypen fuer Funktionen, die SortField/
// ApSortField als Parameter nehmen. Ohne diese hier (direkt nach den Enum-
// Definitionen) versucht die automatische Arduino-Prototyperzeugung selbst
// welche zu erzeugen und setzt sie dabei vor die Enum-Definitionen - siehe
// bereits vorhandener Kommentar bei traffic_detail_address_match() zum
// selben Phaenomen (dort mit primitiven Typen umgangen). Ohne eigene
// Deklaration hier fuehrte das je nach Arduino-Build-Tool-Version zu
// Kaskadenfehlern ("SortField was not declared in this scope" usw.).
bool default_ascending_for(SortField f);
void set_sort_field(SortField f);
const char* sort_field_name(SortField f);
bool default_ap_ascending_for(ApSortField f);

void menu_init();
void menu_handle_serial();     // liest verfuegbare Serial-Eingaben, nicht blockierend
void menu_periodic();          // vom Hauptloop aufgerufen, realisiert 15s-Auto-Refresh
// NEU 2.17.6: Status-LED (Paket 7) - frei waehlbarer GPIO-Pin (Hidden
// Settings, Default: GPIO 2), zeigt den Betriebszustand:
// - Boot: durchgehend an waehrend setup() laeuft
// - Online (Scan aktiv): Blitz alle 10s fuer 20ms
// - Offline: Fade In/Fade Out (Breathing-Animation)
// - Zeitkritisch: LED-Ansteuerung pausiert (Dateitransfer, NTFY, etc.)
void led_apply_pin_config(); // richtet pinMode() fuer den aktuell konfigurierten Pin ein
void led_update();           // nicht blockierend, aus dem Hauptloop periodisch aufgerufen
void led_force_off();        // schaltet die LED sofort aus (vor blockierenden Vorgaengen)
// NEU 2.17.7: Helper beruecksichtigen status_led_active_low (invertierte
// Logik) und Software-PWM fuer GPIO16 (keine PWM-Hardware auf dem ESP8266)
void led_write_digital(bool on);
void led_write_pwm(int level_0_to_range, uint32_t now_ms);
void menu_draw();              // zeichnet die Menue-Uebersicht

// NEU 2.21.0: Signal-Pin Funktionen (ähnlich wie LED)
void signal_apply_pin_config(); // richtet pinMode() fuer den aktuell konfigurierten Pin ein
void signal_write_digital(bool on);  // schaltet Signal auf GPIO
void signal_force_off();  // schaltet das Signal sofort aus
void signal_boot_pulse();  // startet 500ms Signal beim Boot
// NEU 2.27.1 REQ-4: Rueckkehr-Signalisierung (Menue 4) - nutzt dieselbe
// Pin-Infrastruktur wie oben, eigenes (zweites) Non-Blocking-Zeitfenster.
void signal_start_return_pulse();  // startet den 5ms Rueckkehr-Puls
void adc_low_start_pulse();        // NEU 2.30.35: startet den 5x 100/100ms Akku-Warnimpuls
void watchlistPulse_begin();       // alloziert Zustandsarray (jetzt permanent, s. setup())
void watchlistPulse_end();         // gibt Zustandsarray frei (aktuell ungenutzt, Zustand bleibt permanent)
void watchlist_background_check(); // NEU 2.28.0: Rueckkehr-Signalisierung global im Hintergrund, unabhaengig vom Menuestatus
bool watchlistPulse_check_and_update(uint8_t *mac, bool currently_out, uint32_t current_age);
void menu_go_back();           // Backspace-Navigation: zurueck zum vorherigen Zustand
void menu_enter_ssid_select(); // zeichnet die AP-Auswahlliste
// NEU 2.17.5: Punkt m - alte Eintraege loeschen; Punkt 3 - einzelnen AP loeschen
void menu_enter_cleanup();
int delete_old_clients(int max_age_sec, uint64_t now);
int delete_old_aps(int max_age_sec, uint64_t now);
int delete_ap_by_index(int idx);
// NEU 2.29.10: Luecken-basiertes aps_known[]-Array (statt Verschieben beim
// Loeschen). aps_known_count bleibt der High-Water-Mark (hoechster jemals
// belegter Index + 1), NICHT mehr die tatsaechliche Anzahl - fuer die echte,
// lebende Anzahl siehe aps_known_live_count(). Ein Slot ist frei, wenn
// last_heard == AP_SLOT_FREE_MARKER (0xFFFFFFFF) - technisch unmoeglich im
// Normalbetrieb, da last_heard = millis()/1000 erst nach ueber 135 Jahren
// Dauerbetrieb in diesen Bereich kaeme. WICHTIG: jede Schleife, die
// aps_known[].bssid vergleicht, MUSS zuerst ap_slot_free() pruefen - sonst
// koennten stehengebliebene bssid-Altbytes eines geloeschten APs faelschlich
// matchen.
#define AP_SLOT_FREE_MARKER 0xFFFFFFFFUL
bool ap_slot_free(int idx);
void ap_slot_mark_free(int idx);
int aps_known_live_count();
// NEU 2.29.16 BUGFIX/VEREINFACHUNG: Der in 2.29.11-2.29.15 eingefuehrte
// Platzhalter-Mechanismus (ensure_ap_index(), "...wartet auf Beacon") wurde
// wieder entfernt. Grund: bei schwachen/entfernten Nachbar-APs (laengerer
// Beacon-Frame -> hoehere Fehlerrate bei niedrigem SNR als bei kurzen
// Client-Frames) kann es Stunden dauern, bis der erste echte Beacon
// eintrifft - der Platzhalter blieb so lange sichtbar "haengen" und
// blaehte die Liste mit nutzlosen Eintraegen ohne SSID auf. Einfacher und
// robuster (und identisch zum bewaehrten Verhalten vor Etappe 3): ein
// Client mit noch unbekannter BSSID bekommt einfach AP_IDX_NONE ("??"),
// bis der AP ganz regulaer ueber seinen eigenen Beacon entdeckt wird -
// kein Platzhalter-Eintrag, keine Sonderbehandlung beim Speichern/Laden.
int find_ap_index_by_bssid(uint8_t* bssid);
#define AP_IDX_NONE 0xFF

// =====================================================================
// NEU 2.30.39: AUFTRAG 1 - Hintergrundverkehr-Statistik
// NEU 2.30.49: AUFTRAG 2 - auf Varianten 2 (SSID-Buendelung) und 3 (Multi-AP)
// erweitert. Bisher war die Statistik fest an EINEN AP-Index gebunden
// (traffic_stats_ap_idx, siehe traffic_stats_record()-Guard). Jetzt
// entscheidet traffic_stats_mode (Snapshot von current_list_mode bei Start),
// welches Kriterium traffic_stats_ap_included() prueft:
//   Modus 1: ap_idx == traffic_stats_ap_idx (wie bisher)
//   Modus 2: SSID von aps_known[ap_idx] == traffic_stats_ssid (Snapshot)
//   Modus 3: ap_idx steckt in selected_ap_indices[0..selected_ap_count-1]
//            (bestehendes, bereits global vorhandenes Array - bewusst NICHT
//            dupliziert, siehe Kommentar dort)
// Der "AP gesamt"-Zaehler ist jetzt die SUMME ueber alle eingeschlossenen
// APs (bei Modus 1 weiterhin exakt der eine AP). Das ap_idx-Feld in
// traffic_ap_stat wurde gestrichen - es wurde nie gelesen (siehe Analyse),
// und bei Modus 2/3 gibt es ohnehin keinen einzelnen sinnvollen Wert dafuer.
// =====================================================================
// Die Datensaetze sind absichtlich gepackt: AP = 16 Byte, Client = 24 Byte
// (NEU 2.30.58: vorher 10 Byte, siehe mac[6]/last_client_idx unten).
// Die Puffer existieren nur waehrend der aktiven Statistik-Anzeige.
struct traffic_ap_stat {
  uint32_t packets_tx;
  uint32_t packets_rx;
  uint32_t bytes_tx;
  uint32_t bytes_rx;
} __attribute__((packed));

// NEU 2.30.58: AUFTRAG (Aenderungsauftrag Hintergrundverkehr-Statistik) -
// Schluessel von clients_known[]-Index auf die physische MAC-Adresse
// umgestellt. Vorher legte register_client() pro Access Point, an dem ein
// roamender Client gesehen wurde, einen eigenen clients_known[]-Eintrag an,
// wodurch dieselbe MAC bis zu einmal pro eingeschlossenem AP als eigene
// Statistikzeile auftauchte (Dubletten) und den 64er-Puffer schon bei
// rechnerisch ~16 physischen Geraeten voll laufen liess. Jetzt ist mac[6]
// der Sortier-/Suchschluessel (memcmp), last_client_idx wird bei jedem
// traffic_stats_record()-Aufruf aktualisiert und dient nur noch der Anzeige
// (Client-Index-Spalte, sowie clients_known[last_client_idx].ap_idx fuer die
// AP-Spalte in Modus 2/3 - zeigt damit den zuletzt gesehenen AP dieser MAC).
struct traffic_client_stat {
  uint8_t  mac[6];             // Zusammenfassungs-Schluessel
  uint16_t last_client_idx;    // aktuellster clients_known[]-Index dieser MAC, nur fuer Anzeige/Taste 'd'
  uint32_t packets_tx;
  uint32_t packets_rx;
  uint32_t bytes_tx;
  uint32_t bytes_rx;
} __attribute__((packed));

#define TRAFFIC_STATS_MAX_CLIENTS 128
#define TRAFFIC_STATS_REFRESH_SEC 5

uint8_t *traffic_ap_storage = NULL;
uint8_t *traffic_client_storage = NULL;
uint8_t traffic_stats_client_count = 0;
bool traffic_stats_detailed_view = false; // false=kompakt, true=erweitert
char traffic_stats_locked_filter[16] = "";   // NEU 2.30.74: temporaerer Kanalfilter der Hintergrundstatistik
bool traffic_stats_active = false;    // NEU 2.30.49: ersetzt "traffic_stats_ap_idx >= 0" als generisches Aktiv-Flag (das galt nur fuer Modus 1)
int traffic_stats_mode = 0;           // NEU 2.30.49: 1/2/3, Snapshot von current_list_mode bei Start
int traffic_stats_ap_idx = -1;        // nur Modus 1
char traffic_stats_ssid[33] = "";     // NEU 2.30.49: nur Modus 2 (Snapshot der gebuendelten SSID)
// NEU 2.30.58: Last-Hit-Cache jetzt auf MAC statt clients_known[]-Index (ersetzt traffic_stats_last_client_idx)
uint8_t traffic_stats_last_mac[6];
bool    traffic_stats_last_mac_valid = false;
int     traffic_stats_last_pos = -1;
uint32_t traffic_stats_last_refresh = 0;
uint32_t traffic_stats_dropped_clients = 0;  // NEU 2.30.58: zaehlt Frames, nicht Clients (siehe Beschriftung in traffic_stats_redraw())
bool traffic_stats_start_confirm_pending = false;
int traffic_stats_pending_mode = 0;
int traffic_stats_pending_ap_idx = -1;
char traffic_stats_pending_ssid[33] = "";

// NEU 2.30.65: Startzeit der aktuellen Statistik-Sitzung
uint32_t traffic_stats_started_ms = 0;
time_t   traffic_stats_started_unix = 0;

// NEU 2.30.65: Startzeit der aktuellen Detail-Sitzung
uint32_t traffic_detail_started_ms = 0;
time_t   traffic_detail_started_unix = 0;

bool traffic_stats_ap_included(int ap_idx);  // NEU 2.30.49
void traffic_stats_start(int mode, int ap_idx, const char* ssid);
void traffic_stats_request_start(int mode, int ap_idx, const char* ssid);
void traffic_stats_stop();
void traffic_stats_release_lock();
void traffic_stats_reapply_lock();
void filter_channel_unlock_if_active();
void traffic_stats_record(int ap_idx, int client_idx, const uint8_t *mac, uint16_t frame_len, bool is_tx);  // NEU 2.30.58: mac-Parameter
int traffic_stats_find_client(const uint8_t *mac);  // NEU 2.30.58: Suche jetzt ueber MAC statt clients_known[]-Index
void traffic_stats_redraw();
void traffic_stats_print_header(Print &out);
void traffic_stats_print_table(Print &out);
void traffic_stats_print_file_table(Print &out);
void traffic_stats_save_to_file();
void traffic_detail_print_table(Print &out);
void traffic_detail_save_to_file();
void format_duration_hms(uint32_t total_sec, char* buf, size_t buflen);
void format_uptime_dhm(uint32_t total_sec, char* buf, size_t buflen);
void traffic_stats_get_primary_ssid(char* out, size_t outlen);

// NEU 2.30.42: Detailstatistik fuer genau einen ausgewaehlten Client.
// Ein einzelner dynamischer Datensatz spart dauerhaft reserviertes RAM.
struct traffic_detail_stat {
  uint8_t mac[ETH_MAC_LEN];
  uint32_t packets_total;
  uint32_t bytes_total;
  uint32_t packets[3][16];
  uint32_t bytes[3][16];
} __attribute__((packed));

uint8_t *traffic_detail_storage = NULL;
int traffic_detail_client_idx = -1;
bool traffic_detail_selecting = false;
char traffic_detail_input_buf[6];
uint8_t traffic_detail_input_len = 0;
uint32_t traffic_detail_last_refresh = 0;

void traffic_detail_stop();
void traffic_detail_start(int client_idx);
void traffic_detail_record(uint8_t *frame, uint16_t frame_len, uint8_t frame_type, uint8_t frame_subtype);
void traffic_detail_redraw();

// NEU 2.29.17: Beacon-Frame-Rohanalyse (Punkt 3, "w"+Zahl+Enter). Absichtlich
// KEIN statisches Array pro AP - nur EIN einziger, dynamisch angelegter
// Zwischenpuffer, der ausschliesslich waehrend des Wartens auf den naechsten
// Beacon bzw. der anschliessenden Anzeige existiert und danach sofort wieder
// freigegeben wird (kein dauerhaft belegter Heap/RAM). Muss so aufgebaut
// sein, dass die Kernfunktionen (Erfassung + Zerlegung) spaeter auch aus
// Menue 3a heraus wiederverwendbar sind, OHNE dort schon eingebaut zu sein.
#define BEACON_ANALYSIS_TIMEOUT_MS 20000UL
uint8_t *beacon_capture_buf = NULL;     // malloc(112), nur waehrend Warten/Anzeige belegt
uint16_t beacon_capture_reallen = 0;    // echte Framelaenge (RxControl.legacy_length), kann >112 sein
uint8_t beacon_capture_target_bssid[ETH_MAC_LEN];
volatile bool beacon_capture_armed = false;  // true = Callback sucht aktiv nach dieser BSSID
volatile bool beacon_capture_done = false;   // true = Callback hat den Beacon eingefangen
int8_t beacon_capture_rssi = 0;
uint32_t beacon_capture_start_ms = 0;
int beacon_capture_ap_idx = -1;         // nur fuer die Wartebildschirm-Anzeige (SSID-Name)

void menu_start_beacon_capture(int idx);  // startet die Erfassung (Punkt 3)
void cancel_beacon_capture();             // bricht ab/raeumt auf (Backspace/ESC waehrend des Wartens)
void display_beacon_frame_analysis();     // zerlegt beacon_capture_buf und zeigt die Tabelle
const char* rsn_cipher_suite_name(uint8_t type);  // Hilfsfunktion fuer RSN/WPA2-IE
const char* rsn_akm_suite_name(uint8_t type);     // Hilfsfunktion fuer RSN/WPA2-IE
void decode_rsn_ie(uint8_t *d, int len);          // Hilfsfunktion fuer RSN/WPA2-IE
const char* ie_element_name(uint8_t id);          // Klartextname bekannter Information-Element-IDs

// NEU 2.30.6: Client-Frame-Analyse (Menue 3a, "w"+Zahl+Enter) - Pendant zur
// Beacon-Frame-Rohanalyse oben, aber fuer den naechsten Frame eines
// gewaehlten CLIENTS statt des Beacons eines APs.
// BUGFIX/AENDERUNG 2.30.8: urspruenglich (v2.30.6) NUR Probe Requests -
// Nutzer-Test zeigte aber, dass verbundene Clients im Alltag praktisch
// KEINE Probe Requests mehr senden (die werden nur beim aktiven Scannen
// vor/waehrend einer Verbindung gesendet, nicht im laufenden Betrieb -
// die regelmaessig zurueckgesetzte Age-Time kommt von Datenframes). Die
// Erfassung wartet deshalb jetzt auf das NAECHSTE Paket JEDER Art dieses
// Clients (Datenframe ODER Management-Frame wie Probe Request/Auth/...),
// je nachdem, was zuerst eintrifft - genau wie vom Nutzer vorgeschlagen.
// Ein einziger dynamisch angelegter Zwischenpuffer, nur waehrend
// Warten/Anzeige belegt (kein dauerhafter RAM-Verbrauch).
uint8_t *client_capture_buf = NULL;     // malloc(112), nur waehrend Warten/Anzeige belegt
uint16_t client_capture_reallen = 0;    // echte Framelaenge (RxControl.legacy_length), kann > Kapazitaet sein
// NEU 2.30.8: wie viele Byte von client_capture_buf tatsaechlich gueltig
// sind - 112 bei einem Management-Frame (sniffer_buf2, z.B. Probe Request),
// nur 36 bei einem Datenframe (sniffer_buf - das SDK liefert fuer
// Datenframes von vornherein nur einen kleineren Puffer, da die
// Nutzdaten ohnehin meist verschluesselt sind).
uint16_t client_capture_buf_capacity = 0;
uint8_t client_capture_target_station[ETH_MAC_LEN];
volatile bool client_capture_armed = false;  // true = Callback sucht aktiv nach dieser Station-MAC
volatile bool client_capture_done = false;   // true = Callback hat ein passendes Paket eingefangen
int8_t client_capture_rssi = 0;
uint32_t client_capture_start_ms = 0;
int client_capture_client_idx = -1;     // nur fuer die Wartebildschirm-Anzeige (MAC)
bool client_select_analyze_mode = false;     // 'w'-Praefix wurde vor der Zahl eingegeben (Menue 3a)
bool client_frametrap_mode = false;          // NEU 2.30.11: 'p' nach 'w' - "wp"+Zahl+Enter macht die Falle scharf statt sofort zu erfassen

void menu_start_client_capture(int idx);  // startet die Erfassung (Menue 3a)
void cancel_client_capture();             // bricht ab/raeumt auf (Backspace/ESC waehrend des Wartens)
void display_client_frame_analysis();     // zerlegt client_capture_buf und zeigt die Tabelle
const char* ie_frame_subtype_name(uint8_t ftype, uint8_t fsubtype);  // NEU 2.30.8: Klartextname fuer beliebige Frametyp/Subtyp-Kombination

// NEU 2.30.11: "Mausefalle" - wartet (unbegrenzt, ueberlebt Reboot) auf den
// naechsten Probe Request eines schon autorisierten/bekannten Clients, ganz
// unabhaengig vom Menue-Zustand. Bewusst auf der Watchlist aufgesetzt statt
// einer eigenen Zielliste: ein Watchlist-Eintrag mit FRAMETRAP_CLIENT_MARKER in
// der Beschreibung ist "scharf". promisc_cb() macht dabei WEITERHIN nur
// memcpy/memcmp (siehe Kommentar bei client_capture_* oben zur Panic-
// Lehre aus v2.30.9/2.30.10) - das eigentliche Dekodieren+Datei-Schreiben
// passiert erst danach in menu_periodic() im Hauptloop. Bis zu
// FRAMETRAP_CLIENT_MAX_PENDING Fallen dürfen gleichzeitig scharf sein (Nutzer-
// Vorgabe); dieselbe Zahl dient auch als Puffergroesse zwischen Callback
// und Verarbeitung (mehr als eine Handvoll gleichzeitiger Faenge sind bei
// so seltenen Ereignissen praktisch ausgeschlossen).
#define FRAMETRAP_CLIENT_MAX_PENDING 5
#define FRAMETRAP_CLIENT_MARKER " (wait PR)"
struct FrameTrapClientCatch {
  uint8_t station[ETH_MAC_LEN];
  uint8_t *buf;            // malloc(112), NULL = Slot frei
  uint16_t reallen;
  int8_t rssi;
};
FrameTrapClientCatch frametrap_client_catches[FRAMETRAP_CLIENT_MAX_PENDING];

bool watchlist_entry_is_trapped(int idx);           // hat FRAMETRAP_CLIENT_MARKER in der Beschreibung?
int frametrap_client_armed_count();                        // wie viele Eintraege sind gerade scharf?
void remove_watchlist_entry(int idx);                // Loeschen-Grundoperation (Array-Shift), OHNE save_watchlist()/Ausgabe
bool frametrap_client_arm(uint8_t *mac);                    // scharf machen (Menue 3a, "wp"+Zahl+Enter)
void frametrap_client_disarm_or_remove(uint8_t *mac);        // NEU 2.30.11: Marker entfernen, Eintrag nur loeschen wenn dann leer (Variante B)
void frametrap_client_process_catch(int slot);               // dekodiert+schreibt Datei, raeumt Slot/Watchlist auf

// NEU 2.30.46 (Anwenderwunsch): Beacon-FrameTrap jetzt - wie der Client-
// FrameTrap - ueber die Watchlist verwaltet statt ueber eine eigene, nicht
// persistente Liste. Vorteile, wie beim Anwender bemaengelt: der scharfe
// FrameTrap erscheint jetzt in der Watchlist-Anzeige (Menue 4) markiert,
// UND uebersteht (wie der Client-FrameTrap) einen Neustart, weil die
// Watchlist ohnehin schon geladen/gespeichert wird. Die Watchlist "kennt"
// dabei weiterhin nur MAC-Adressen ganz allgemein - ob es sich um eine
// Client- oder eine AP/BSSID-Adresse handelt, ergibt sich ausschliesslich
// aus dem jeweiligen Marker in der Beschreibung.
#define FRAMETRAP_BEACON_MARKER " (wait BC)"
bool watchlist_entry_is_beacon_trapped(int idx);      // hat FRAMETRAP_BEACON_MARKER in der Beschreibung?

struct FrameTrapBeaconCatch {
  uint8_t bssid[ETH_MAC_LEN];
  uint8_t *buf;            // malloc(112), NULL = Slot frei
  uint16_t reallen;
  int8_t rssi;
};
#define FRAMETRAP_BEACON_MAX_PENDING 5
FrameTrapBeaconCatch frametrap_beacon_catches[FRAMETRAP_BEACON_MAX_PENDING];

int frametrap_beacon_armed_count();                   // wie viele BSSIDs sind gerade scharf?
bool frametrap_beacon_is_armed(uint8_t *bssid);        // ist diese BSSID gerade scharf?
bool frametrap_beacon_arm(uint8_t *bssid);             // scharf machen (Menue 3, "wt"+Zahl+Enter)
void frametrap_beacon_disarm(uint8_t *bssid);          // Gegenstueck, nach einem Fang oder manuellem Entschaerfen
void frametrap_beacon_process_catch(int slot);         // dekodiert+schreibt Datei, raeumt Slot auf

// NEU 2.30.45: 't'-Praefix in Menue 3 (STATE_SSID_SELECT), analog zu
// client_frametrap_mode oben, nur fuer den AP-Auswahlbildschirm.
bool ap_select_frametrap_mode = false;

// NEU 2.17.4: Sortierung fuer die AP-Uebersichtsliste (Liste 3), analog zur
// bereits vorhandenen Client-Sortierung (SortField/set_sort_field/sort_clients).
// Vorwaertsdeklariert, da menu_enter_ssid_select() diese Funktionen nutzt,
// ihre eigentlichen Definitionen aber weiter unten im Sketch stehen.
void set_ap_sort_field(ApSortField f);
void sort_aps(uint8_t *idx, int count, uint64_t now);  // BUGFIX 2.30.18: now-Parameter fuer ueberlaufsicheren Alters-Vergleich
const char* ap_sort_field_name(ApSortField f);
void menu_enter_ssid_list(int ap_index); // zeichnet die (sortierte) Geraeteliste
void menu_enter_ssid_list_combined(int seed_ap_index); // wie oben, aber ueber alle APs mit gleicher SSID
bool parse_multi_ap_selection(const char *input); // NEU 2.12.0: parst "1,5,7" fuer Multi-AP Mode
void menu_enter_ssid_list_multi(); // NEU 2.12.0: zeigt Clients mehrerer gewaehlter APs
void print_client_cell(int slot, uint64_t now, Print* out = &Serial); // Terminal-Ausgabe Client (NEU 2.28.0: out-Parameter)
void print_client_cell_ap_mode(int slot, uint8_t *ap_indices, int ap_count, uint64_t now, Print* out = &Serial); // NEU 2.12.0: mit AP-Nummer, NEU 2.28.0: out-Parameter
int calculate_max_ssid_length(uint8_t *ap_indices, int ap_count); // NEU 2.13.0: dynamische SSID-Länge
void print_ap_cell(int idx, int ssid_width, bool two_col, uint64_t now, bool show_vendor, Print* out = &Serial); // NEU 2.28.0: out-Parameter fuer ntfy-Datei-Ausgabe
// NEU 2.17.2: Ignore-Filter (Taste 'i') fuer Modus 2 (S5) und Modus 3 (S<n,n,...>)
bool client_is_hideable(int slot, uint64_t now); // true = Client hat AP gewechselt oder ist "out"
bool client_is_switched(int slot, uint64_t now); // NEU 2.29.7: true = nur AP-Wechsel (fuer Ignore-Filter 'i')
void redraw_ssid_list(); // zeichnet Punkt 3b neu, je nach Modus (einzelner AP oder kombiniert)
void menu_enter_settings();    // Punkt e: Einstellungen
void menu_enter_help();        // Punkt h: Hilfe (Programmbeschreibung, Menuepunkte)
void menu_enter_roaming_groups();  // NEU 2.30.60: Punkt v: Versorgungsbereiche (Roaming-Gruppen)
void menu_enter_hidden_settings();  // "E" im Einstellungsmenue (Punkt e)
void print_logo();             // Boot-Logo bzw. Logo-Header (Datei-Override falls /logo.txt existiert)

// ===================== Benachrichtigung (ntfy.sh) - Zustand =====================
// Muss VOR loop() (weiter unten) stehen, da loop() notif_enabled/
// notif_send_pending/notif_interval_min/last_notif_send_min direkt
// verwendet - Arduino generiert automatische Prototypen nur fuer
// FUNKTIONEN, nicht fuer globale Variablen (gleiche Fehlerklasse wie
// bei startup_online/show_logo, siehe Kommentar weiter unten).
// NEU 2.20.12: NTFY Struktur überarbeitet - jeder Parameter isoliert + korrekte Größen
// Speicherung: NUR bei Taste 's' im Settings-Menü (nicht auto-save!)
// Buffer-Overflow-Schutz: Alle destmax-Werte stimmen mit Array-Größen überein
bool notif_enabled = false;
char notif_wifi_ssid[33] = "";        // WLAN-SSID für Versand (max 32 + \0)
char notif_wifi_pass[65] = "";        // WLAN-Passwort (max 64 + \0)
char notif_channel[24] = "";          // ntfy.sh Kanalname (max 23 + \0)
char notif_header_text[33] = "WiFi-Monitor";  // Message-Header/Betreff (max 32 + \0)
uint8_t notif_interval_min = 15;      // Sendeintervall in Minuten
uint8_t notif_content_mode = 0;       // 0=komplette, 1=eine SSID, 2=mehrere, 3=alle APs
char notif_ssid_filter[64] = "";      // SSID-Filter kommagetrennt (max 63 + \0)

uint32_t last_notif_send_min = 0;     // wann zuletzt gesendet wurde (Minuten seit Boot)
bool notif_send_pending = false;      // true = "Jetzt senden" wurde angefordert

bool notif_interval_input_active = false;
char notif_interval_input_buf[5];
uint8_t notif_interval_input_len = 0;

char notif_text_edit_buf[96];  // Eingabepuffer für Text-Edit (max 95 + \0)
uint8_t notif_text_edit_len = 0;
int notif_edit_target = 0;            // 1=SSID 2=Pass 3=Kanal 4=Header 5=Filter (NEU 2.20.12)

void save_single_setting(const char* key, int value);
void save_all_settings();
void load_all_settings();
void menu_enter_info();        // Punkt i: Info (Herkunft, Version, ESP-/Speicherdaten)
void menu_enter_save_filename(); // Punkt 5a: Dateiname eingeben
void menu_enter_file_list();   // Punkt 6: gespeicherte Dateien anzeigen

// ===================== HTTP-Datei-Server (Punkt 7, NEU 2.30.0) =====================
// g_http_server ist NULL, solange Punkt 7 nicht aktiv ist - das Objekt wird
// erst beim Betreten per "new" angelegt und beim Verlassen per "delete"
// wieder freigegeben, damit im normalen Sniffing-Betrieb kein zusaetzliches
// RAM gebunden bleibt (siehe Changelog 2.30.0).
ESP8266WebServer* g_http_server = nullptr;
void menu_enter_http_server();       // Punkt 7: WLAN verbinden, Server starten
void http_server_stop();             // Server beenden, WLAN trennen, Promiscuous-Mode wiederherstellen
void http_handle_root();             // "/" - Startseite (hlogo.jpg + Tastendruck-Warteschleife)
void http_handle_files_page();       // "/dateien" - Dateiverwaltung (Liste/Upload/Download/Loeschen)
void http_handle_download();         // "/download?f=NAME" - Datei gestreamt ausliefern
void http_handle_delete();           // "/delete?f=NAME" - Datei loeschen (respektiert Schutzliste)
void http_handle_hlogo();            // "/hlogo.jpg" - Startlogo ausliefern (falls vorhanden)
void http_handle_banner();           // "/banner.jpg" - Bannerbild ausliefern (falls vorhanden)
void http_handle_upload_done();      // Antwort NACH Abschluss eines Uploads (POST /upload)
void http_handle_upload_data();      // HTTPUpload-Callback, chunkweise waehrend des Uploads
void http_handle_stop_request();     // "/beenden" - Server per Browser beenden
void http_close_after_response();    // NEU 2.30.4: setzt "Connection: close" vor jeder Antwort
void http_handle_not_found();        // 404-Handler
void http_send_banner_if_present();  // Hilfsfunktion: <img>-Tag fuer banner.jpg in Seiten einfuegen
File g_http_upload_file;             // aktuell per Upload beschriebene Datei (nur waehrend POST /upload offen)
bool g_http_upload_rejected = false; // true = Ziel ist geschuetzt/ungueltig, Chunks werden verworfen
const char* g_http_upload_reject_reason = "";  // Klartextgrund fuer die Ablehnung (siehe http_handle_upload_done())
// BUGFIX 2.30.5: "/beenden" darf http_server_stop() (mit "delete
// g_http_server") NICHT direkt aufrufen - der Aufruf laeuft ja gerade
// SELBST als Methode/Callback von g_http_server, ausgeloest durch
// g_http_server->handleClient(). Wird das Objekt darin geloescht, arbeitet
// handleClient() hinterher mit bereits freigegebenem Speicher weiter ->
// Absturz (nur beim Beenden ueber den Browser, nicht ueber die serielle
// Konsole, weil die Konsole ausserhalb jedes Server-Methodenaufrufs
// beendet). Deshalb setzt der "/beenden"-Handler nur dieses Flag, und
// menu_periodic() ruft http_server_stop() erst NACH dem Rueckkehren aus
// handleClient() auf - also ausserhalb von dessen Aufrufkette.
bool g_http_stop_requested = false;

// ===================== AP-Modus (NEU 2.30.5) =====================
// Eigener Access Point als Alternative zum Beitritt in ein bestehendes
// WLAN (notif_wifi_ssid/notif_wifi_pass) fuer Punkt 7 (HTTP-Datei-Server).
// Praktisch, wenn kein Router in Reichweite ist oder keine Zugangsdaten
// hinterlegt werden sollen - das Geraet spannt dann sein eigenes kleines
// WLAN auf, mit dem sich Handy/PC direkt verbinden koennen.
bool ap_mode_enabled = false;
char ap_mode_ssid[33] = "WiFi-Monitor";  // Default-SSID des eigenen Access Points (max 32 + \0)
char ap_mode_pass[65] = "";              // leer = offenes WLAN, sonst WPA2 (mind. 8 Zeichen), max 64 + \0
char ap_mode_text_edit_buf[96] = "";     // Eingabepuffer, analog zu notif_text_edit_buf
uint8_t ap_mode_text_edit_len = 0;
int ap_mode_edit_target = 0;             // 1=SSID 2=Passwort
bool g_http_server_is_ap = false;        // true = Punkt 7 laeuft aktuell als eigener AP statt STA-Verbindung
void menu_enter_apmode_settings();       // Einstellungen > AP-Modus
void menu_enter_apmode_text_edit(int target);  // Textfeld (SSID/Passwort) eingeben

// ===================== NTP-Zeitsynchronisation =====================
void sync_ntp_time();                // beim Boot aufgerufen, holt die Uhrzeit falls aktiviert
time_t current_unix_time();          // aktuelle Unix-Zeit (Sekunden) oder 0 falls nicht synchronisiert
time_t current_unix_time_with_tz();  // NEU 2.12.0: mit Timezone-Offset, NEU 2.17.8 inkl. Auto-DST
// NEU 2.17.8: Automatische Sommer-/Winterzeit (Daylight Saving Time, EU-Regel)
long days_from_civil(int y, int m, int d);
time_t eu_dst_transition_utc(int year, int month);
bool eu_dst_active(time_t utc_now);
void menu_enter_ntp_settings();      // Einstellungen > NTP
void menu_enter_ntp_text_edit(int target);  // Textfeld (SSID/Passwort/Server) eingeben
void menu_enter_adc_settings();      // NEU 2.29.0: Einstellungen > ADC (Akkuspannung)
void menu_enter_ram_debug();         // NEU 2.30.34: Hidden Settings > Debug RAM Memory
void menu_enter_call_chain_view();   // NEU 2.30.35: Debug RAM Memory > Call-Chain anzeigen
uint16_t adc_read_voltage_mv();      // NEU 2.29.0: aktuelle Akkuspannung in mV (0 = nicht kalibriert)
void adc_voltage_monitor();          // NEU 2.29.0: periodische Ueberwachung + 3-fach-Bestaetigung

// ===================== Werkseinstellungen (Hidden Settings) =====================
void menu_enter_factory_reset_confirm();  // Sicherheitsabfrage
void menu_enter_esp_restart_confirm();    // NEU 2.20.0 FEATURE 4: ESP-Neustart-Sicherheitsabfrage
void perform_factory_reset();             // loescht LittleFS, setzt Defaults, Endlosschleife
// ============================================================================
// Szenario-Kompression v1 (CSZ1) - Forward-Declarations
// (Typen/Konstanten stehen jetzt ganz vorne im Sketch, siehe BUGFIX 2.30.51-
// Kommentar dort - Grund: Arduinos automatische Prototypen-Generierung.)
// ============================================================================
static bool scenario_encoder_flush(ScenarioEncoder &e);
static bool scenario_encoder_token(ScenarioEncoder &e, bool literal, uint8_t a, uint8_t b = 0);
static bool scenario_lzss_step(ScenarioEncoder &e);          // NEU 2.30.50: interner Helfer
static void scenario_dec_hist_put(ScenarioDecoder &d, uint8_t b);  // NEU 2.30.50: interner Helfer
static uint8_t scenario_hist_byte(const ScenarioEncoder &e, uint16_t back);
static void scenario_hist_put(ScenarioEncoder &e, uint8_t b);
static uint8_t scenario_find_match(ScenarioEncoder &e, uint16_t &best_off);
static bool scenario_lzss_push(ScenarioEncoder &e, uint8_t b);
static bool scenario_rle_emit(ScenarioEncoder &e, uint8_t b);
static bool scenario_rle_input(ScenarioEncoder &e, uint8_t b);
static bool scenario_encoder_finish(ScenarioEncoder &e);
static bool scenario_plain(ScenarioEncoder &e, const char *s);
static bool scenario_plain_P(ScenarioEncoder &e, PGM_P s);
static bool scenario_plain_fmt(ScenarioEncoder &e, const char *fmt, ...);
static bool scenario_decode_lzss(ScenarioDecoder &d, uint8_t &out);
static bool scenario_decode_rle(ScenarioDecoder &d, uint8_t &out);
static bool scenario_is_compressed_file(File &f);
static void scenario_decoder_init(ScenarioDecoder &d, File &f, uint8_t *w);
static int scenario_read_decompressed_byte(ScenarioDecoder &d);
static void scenario_reader_reset(ScenarioLineReader &r);
static bool scenario_reader_read_line(ScenarioLineReader &r, String &line);
static void scenario_print_file_content(const char *path);

int save_current_lists(const char* filename);  // Speichert APs + Clients, gibt Anzahl zurück
int write_scenario_plaintext(File &f, uint64_t now);  // NEU 2.30.63: gemeinsamer Schreibkern fuer save_current_lists() (Klartext-Zweig) und build_notif_attachment() (Modus 0)
void format_generation_timestamp(char *out, size_t outlen);
void write_generated_file_header(File &f);
// NEU 2.12.0: Auto-Save Funktionen
void perform_auto_save_with_timestamp();    // Mit NTP: Timestamp im Dateinamen
void perform_auto_save_without_timestamp(); // Ohne NTP: Clients-APs-Millis Format
// NEU 2.13.0: Channel-Filter Funktionen (noch zu implementieren)
bool is_channel_allowed(int channel); // Prueft ob Kanal im Filter liegt
bool load_scenario_file(const char* filename);  // laedt Datei als aktiven Scan-Zustand
void parse_mac_hex(const char* s, uint8_t* out);
void print_offline_banner_now();   // gibt OFFLINE-/Channel-Warnung sofort aus (roh, ohne Positionslogik)
void print_channel_filter_warning();  // NEU 2.20.4 BUG11: Warnung wenn Channel-Filter aktiv
uint64_t effective_now();      // "jetzt" fuer last-seen-Berechnung (eingefroren wenn offline)
void format_uptime_ddhhmmss(char *out, size_t outlen);  // NEU 2.30.65: Laufzeit als 8-stelliger Code "ddhhmmss"
void go_offline();
void go_online();
void toggle_online_mode();
bool input_field_active();     // true waehrend Text-/Zahleneingabe (blockiert Strg+O)
void refresh_current_screen(); // zeichnet den aktuellen Bildschirm neu (z.B. nach Strg+O)

// true, solange Live-Ausgaben (New DEVICE/BEACON/PROBE) angezeigt werden sollen
bool live_output_active();

// ===================== MAC-Watchlist =====================
bool is_watched_mac(uint8_t* mac);
// NEU 2.26.x: erkennt randomisierte ("locally administered") MAC-Adressen
// anhand von Bit 0x02 im ersten Oktett - reine Bit-Pruefung, kein Zustand.
bool is_randomized_mac(uint8_t* mac);
void print_mac(uint8_t* mac, const char* restore_sgr, Print* out = &Serial); // NEU 2.28.0: out-Parameter fuer Wiederverwendung bei ntfy-Datei-Ausgabe
void format_uint64_dec(uint64_t value, char* buf, size_t buflen); // NEU 2.30.32: 64-Bit-Wert (z.B. TSF) ohne 32-Bit-Ueberlauf als Dezimalstring
void menu_enter_watchlist();          // Punkt 4: Watchlist-Ansicht
void menu_enter_watchlist_add_mac();  // Punkt 4: neue MAC eingeben
void menu_enter_watchlist_add_desc(); // Punkt 4: Beschreibung dazu eingeben
void add_or_update_watchlist_entry(uint8_t* mac, const char* desc);
void save_watchlist();
void load_watchlist();

// ===================== Benachrichtigung (ntfy.sh) =====================
void menu_enter_notif_settings();          // Einstellungen > Benachrichtigung
void menu_enter_notif_text_edit(int target); // Textfeld (SSID/Passwort/Kanal/Filter) eingeben
int build_notif_attachment();              // erzeugt den Dateianhang, liefert Geraeteanzahl
void write_notif_client_section(File &f, uint16_t *indices, int count, uint64_t now, int *written); // NEU 2.28.0
void write_notif_ap_section(File &f, uint64_t now, int *written); // NEU 2.28.0
void build_notif_filename(char* out, size_t outlen); // NEU 2.28.0: Dateiname aus Message-Header + Listentyp
bool notif_send_now(const char* file_path = NULL); // ohne Pfad: bisheriger Listenanhang; mit Pfad: Datei senden
extern bool ntp_synced;
static char file_ts_encode_minsec(int v)
{ if(v==0)return '0'; if(v<=26)return (char)('a'+v-1); if(v<=52)return (char)('A'+v-27); return (char)('1'+v-53); }
static int file_ts_decode_minsec(char c)
{ if(c=='0')return 0; if(c>='a'&&c<='z')return c-'a'+1; if(c>='A'&&c<='Z')return c-'A'+27; if(c>='1'&&c<='7')return c-'1'+53; return -1; }
void build_file_timestamp(char *out, size_t len)
{
  if(!out||len<7)return; time_t now=ntp_synced?current_unix_time_with_tz():0;
  if(now>0){ struct tm *t=localtime(&now); if(t){ int m=t->tm_mon+1,d=t->tm_mday,h=t->tm_hour; out[0]='0'+((t->tm_year+1900)%10); out[1]=m<=9?'0'+m:'a'+m-10; out[2]=d<=9?'0'+d:'A'+d-10; out[3]=h<=9?'0'+h:'A'+h-10; out[4]=file_ts_encode_minsec(t->tm_min); out[5]=file_ts_encode_minsec(t->tm_sec); out[6]=0; return; }}
  uint32_t v=millis()/1000UL; out[0]='0'+((v/86400UL)%10); out[1]='0'+((v/3600UL)%10); out[2]='0'+((v/60UL)%10); out[3]='0'+((v/10UL)%10); out[4]=file_ts_encode_minsec(v%60); out[5]=file_ts_encode_minsec((v/60UL)%60); out[6]=0;
}
bool parse_file_timestamp(const char *in,char *out,size_t len)
{
  if(!in||!out||len<20)return false; const char *u=strrchr(in,'_'); if(!u||strlen(u+1)<10)return false; const char *t=u+1;
  int y=t[0]-'0',mo=(t[1]>='a'&&t[1]<='c')?t[1]-'a'+10:t[1]-'0'; int d=(t[2]>='A'&&t[2]<='V')?t[2]-'A'+10:t[2]-'0'; int h=(t[3]>='A'&&t[3]<='N')?t[3]-'A'+10:t[3]-'0'; int mi=file_ts_decode_minsec(t[4]),se=file_ts_decode_minsec(t[5]); if(y<0||mo<1||mo>12||d<1||d>31||h<0||h>23||mi<0||mi>59||se<0||se>59)return false; snprintf_P(out,len,PSTR("20x%d-%02d-%02d %02d:%02d:%02d"),y,mo,d,h,mi,se); return true;
}

bool make_collision_safe_path(const char *requested,char *out,size_t outlen)
{
  if(!requested||!out||outlen<8)return false; char original[40]; strncpy(original,requested,sizeof(original)-1);original[sizeof(original)-1]=0; strncpy(out,original,outlen-1);out[outlen-1]=0;if(!LittleFS.exists(out))return true;
  char base[40]; strncpy(base,original,sizeof(base)-1);base[sizeof(base)-1]=0; char *slash=strrchr(base,'/'); char *name=slash?slash+1:base; char *dot=strrchr(name,'.'); char ext[8]=""; if(dot){strncpy(ext,dot,sizeof(ext)-1);ext[sizeof(ext)-1]=0;*dot=0;}
  char ts[7];build_file_timestamp(ts,sizeof(ts)); size_t budget=31-strlen(ext)-1-6-1;
  if(strlen(name)>budget) {
    if(strncmp(name,"TR_",3)==0 && budget>4) {
      char ssid[36]; strncpy(ssid,name+3,sizeof(ssid)-1); ssid[sizeof(ssid)-1]=0;
      size_t sb=budget-3, left=(sb-1+1)/2, right=sb-1-left, sl=strlen(ssid);
      char shortened[40]; if(sl>left+right) snprintf(shortened,sizeof(shortened),"TR_%.*s^%s",(int)left,ssid,ssid+sl-right);
      else snprintf(shortened,sizeof(shortened),"TR_%s",ssid);
      strcpy(name,shortened);
    } else if ((strncmp(name,"PR_",3)==0 || strncmp(name,"BC_",3)==0) && budget>=18) {
      char macpart[16]; strncpy(macpart,name,15); macpart[15]=0; size_t remain=strlen(name)>16?strlen(name+16):0;
      char shortened[40]; snprintf(shortened,sizeof(shortened),"%s^%s",macpart,remain?name+16+((remain>3)?remain-3:0):""); strcpy(name,shortened);
    } else name[budget]=0;
  }
  for(int n=0;n<10;n++){char suffix[9];if(n)snprintf(suffix,sizeof(suffix),"_%s%d",ts,n);else snprintf(suffix,sizeof(suffix),"_%s",ts);snprintf(out,outlen,"/%s%s%s",name,suffix,ext);if(!LittleFS.exists(out))return true;} return false;
}

bool notif_send_file(const char *path);

// Merkt sich pro Client-Slot den zuletzt ANGEZEIGTEN RSSI-Wert, um beim
// naechsten Refresh die Tendenz (staerker/schwaecher) zu bestimmen.
// Definiert in wifi_monitor.ino, Groesse MAX_CLIENTS_TRACKED.
// NEU 2.17.9: RAM-Optimierung - prev_shown_rssi braucht nur int8_t (RSSI ist -128..127)
extern int8_t prev_shown_rssi[];
extern bool online_mode;
extern uint64_t offline_freeze_time;
// NEU beim Zusammenfuehren: In der Mehrdateien-Version standen diese
// Definitionen in functions.ino, das von Arduino IMMER nach der
// Haupt-Sketchdatei einsortiert wird - setup() (unten) kannte sie also
// schon vorher nur durch Arduinos Gesamt-Vorverarbeitung. In einer
// einzelnen Datei braucht es dafuer jetzt explizite extern-Deklarationen,
// die eigentlichen Definitionen (mit Startwert) stehen weiterhin weiter
// unten im ehemaligen functions.ino-Teil.
extern bool startup_online;
extern bool show_logo;

// ===================== NTP-Zeitsynchronisation - Zustand =====================
// Muss VOR current_unix_time()/sync_ntp_time() (weiter unten) stehen, da
// diese Funktionen ntp_synced/ntp_epoch_at_sync/millis_at_ntp_sync bzw.
// ntp_enabled/ntp_wifi_ssid/ntp_wifi_pass/ntp_server direkt verwenden -
// gleiche Fehlerklasse wie bei startup_online/show_logo (Arduino generiert
// automatische Prototypen nur fuer Funktionen, nicht fuer globale
// Variablen). Die eigentlichen Definitionen (mit Startwert) stehen
// weiterhin weiter unten im ehemaligen functions.ino-Teil.
extern bool ntp_enabled;
extern char ntp_wifi_ssid[];
extern char ntp_wifi_pass[];
extern char ntp_server[];
extern bool ntp_synced;
extern time_t ntp_epoch_at_sync;
extern uint32_t millis_at_ntp_sync;

// Version: 2.30.71      Generiert: 2026-10-03 (Dateiausgabe: Zeilenende und
//                        Ø-Ueberschriften korrigiert, Spaltenausrichtung
//                        angepasst; kompakte Statistik mit Gruppentrennern;
//                        Taste r nur in Hintergrundverkehr entfernt;
//                        FrameTrap-Hinweis gekuerzt; Dateilisten und
//                        Schutzliste auf 32 Eintraege erweitert.)
#define FIRMWARE_VERSION "2.30.81"
#define FIRMWARE_BUILD_DATE "2026-10-05"
// =====================================================================
// NEU 2.30.67: TimeWatch - fruehe Deklarationen/Globale
// =====================================================================
#define TIMEWATCH_MARKER " (TW)"

struct timewatch_state_entry {
  uint8_t mac[6];
  uint8_t prev_state;
  uint32_t last_log_time;
} __attribute__((packed));

timewatch_state_entry timewatch_state[32];
uint8_t pending_timewatch_mac[ETH_MAC_LEN];
int timewatch_return_to = 0;
bool ssid_select_timewatch_prefix = false;
bool ssid_select_timewatch_mode = false;
bool client_timewatch_mode = false;

bool watchlist_entry_is_timewatched(int idx);
void menu_enter_timewatch_add_desc();
int timewatch_get_state_slot(uint8_t *mac);
void timewatch_build_filename(const uint8_t *mac, const char *desc, char *out, size_t outlen);
void timewatch_build_timestamp(char *out, size_t outlen);
void timewatch_append_timestamp(uint8_t *mac, const char *desc);
void timewatch_check_and_log(uint8_t *mac, uint32_t age, uint64_t now);
int delete_old_empty_aps(uint64_t now);


// --- Schritt 1: angepasste Speichergrenzen (inzwischen weiter erhoeht, s. Aenderungsverlauf) ---
// NEU 2.30.32: RAM-Referenzwert fuer die Prozentberechnung der RAM-Anzeige,
// empirisch mit einem minimalen ESP8266-Testprogramm ermittelt (ESP.getFreeHeap()
// direkt nach dem Start, mit und ohne WiFi.mode(WIFI_OFF) - identisches Ergebnis).
// Ersetzt den bisherigen festen Wert 80.000.
#define RAM_REFERENCE_BYTES 49024UL
#define MAX_APS_TRACKED 200        // NEU 2.20.2 BUG4: reduziert (RAM-Optimierung)

// NEU 2.30.49: hierher vorgezogen (urspruenglich weiter unten bei den
// uebrigen Menue-3a-Variablen) - dieselbe Fehlerklasse wie schon mehrfach
// zuvor (z.B. watchlist_sighting, filter_has_mac): traffic_stats_ap_
// included() (siehe dort) wird aus promisc_cb() heraus pro Paket aufgerufen
// und braucht fuer Modus 3 lesenden Zugriff auf genau diese beiden
// Variablen - promisc_cb() steht aber VOR ihrer bisherigen Deklarationsstelle
// im Sketch. Bewusst nur diese zwei verschoben (nicht dupliziert), um keinen
// zusaetzlichen RAM-Verbrauch durch eine zweite Kopie zu erzeugen - die
// eigentliche Verwendung (Punkt 3a, Modus 3) bleibt an ihrer bisherigen
// Stelle unveraendert, der Speicherort der Deklaration ist dafuer irrelevant.
uint8_t selected_ap_indices[MAX_APS_TRACKED];  // NEU 2.21.1 OPTIMIZATION: int → uint8_t für Mode 3: Array der gewählten AP-Indizes
int selected_ap_count = 0;            // für Mode 3: Anzahl der gewählten APs
#define MAX_CLIENTS_TRACKED 1000   // NEU 2.21.0 OPTIMIZATION: Index-Arrays int → uint16_t
                                   // Ersparnis: ~2 KB RAM durch uint16_t Indizierung (sicherer als uint8_t, effizienter als int)
// Probes werden nicht mehr gespeichert - kein MAX_PROBES_TRACKED mehr noetig
// ------------------------------------------------

#define PERIODIC           // define this to get summary of new and expired entries periodically

beaconinfo aps_known[MAX_APS_TRACKED];
uint8_t aps_known_count = 0;  // NEU 2.17.9: RAM-Optimierung. NEU 2.29.10: jetzt High-Water-Mark, siehe Kommentar bei den Prototypen oben.
int nothing_new = 0;
clientinfo clients_known[MAX_CLIENTS_TRACKED];
uint16_t clients_known_count = 0;  // uint16_t wegen max 250, aber kleiner als int

// =====================================================================
// NEU 2.30.60: Versorgungsbereich-Erkennung (ereignisbasiert)
// Ein Roaming-Vorgang (gleiche Client-MAC an zwei verschiedenen APs) wird
// beim Entstehen in register_client() als ungeordnetes AP-Paar erfasst.
// Statisch 129 Byte (Paarliste) + 200 Byte (Union-Find), kein Heap.
// Bei Ueberlauf werden weitere Paare verworfen - die Gruppierung bleibt
// dann unvollstaendig, aber nie falsch.
// =====================================================================
#define ROAMING_PAIRS_MAX 64
static uint8_t roaming_pairs[ROAMING_PAIRS_MAX][2];
static uint8_t roaming_pair_count = 0;
static uint8_t roaming_parent[MAX_APS_TRACKED];

// Erfasst ein Roaming-Paar (a, b). AP_IDX_NONE (Client war noch keinem AP
// zugeordnet) ist kein Roaming-Zeuge und wird ignoriert. Duplikate werden
// unterdrueckt, damit wiederholtes Hin-und-Her-Wechseln desselben Clients
// die knappen 64 Plaetze nicht verbraucht.
static void roaming_record(uint8_t a, uint8_t b)
{
  if (a == b) return;
  if (a == AP_IDX_NONE || b == AP_IDX_NONE) return;
  if (a >= aps_known_count || b >= aps_known_count) return;
  if (ap_slot_free(a) || ap_slot_free(b)) return;
  for (int i = 0; i < roaming_pair_count; i++) {
    if ((roaming_pairs[i][0] == a && roaming_pairs[i][1] == b) ||
        (roaming_pairs[i][0] == b && roaming_pairs[i][1] == a)) return;
  }
  if (roaming_pair_count >= ROAMING_PAIRS_MAX) return;
  roaming_pairs[roaming_pair_count][0] = a;
  roaming_pairs[roaming_pair_count][1] = b;
  roaming_pair_count++;
}

// Union-Find ueber AP-Indizes (Pfad-Halbierung)
static uint8_t roaming_find(uint8_t x)
{
  while (roaming_parent[x] != x) {
    roaming_parent[x] = roaming_parent[roaming_parent[x]];
    x = roaming_parent[x];
  }
  return x;
}

static void roaming_union(uint8_t a, uint8_t b)
{
  uint8_t ra = roaming_find(a);
  uint8_t rb = roaming_find(b);
  if (ra != rb) roaming_parent[rb] = ra;
}

// BUGFIX 2.30.61: Entfernt aus roaming_pairs[] alle Eintraege, die den
// AP-Index 'idx' referenzieren. MUSS aufgerufen werden, bevor dieser Index
// einem anderen AP zugewiesen werden kann (siehe ap_slot_mark_free()) -
// roaming_pairs speichert reine Array-Indizes, keine BSSIDs, und wird sonst
// nach Wiederverwendung des Slots einem voellig anderen AP zugeordnet.
static void roaming_purge_ap(uint8_t idx)
{
  int w = 0;
  for (int i = 0; i < roaming_pair_count; i++) {
    if (roaming_pairs[i][0] == idx || roaming_pairs[i][1] == idx) continue;
    if (w != i) { roaming_pairs[w][0] = roaming_pairs[i][0]; roaming_pairs[w][1] = roaming_pairs[i][1]; }
    w++;
  }
  roaming_pair_count = w;
}

// NEU 2.29.10: siehe Kommentar bei den Prototypen weiter oben.
bool ap_slot_free(int idx)
{
  return aps_known[idx].last_heard == AP_SLOT_FREE_MARKER;
}

void ap_slot_mark_free(int idx)
{
  aps_known[idx].last_heard = AP_SLOT_FREE_MARKER;
  // Sicherheitsnetz zusaetzlich zum Marker: bssid auf 0 setzen, damit ein
  // versehentlich fehlender ap_slot_free()-Check vor einem memcmp() nicht
  // gegen die alten, stehengebliebenen bssid-Bytes des geloeschten APs
  // matchen kann (RAM-neutral, kein zusaetzlicher Speicher).
  memset(aps_known[idx].bssid, 0, ETH_MAC_LEN);
  // BUGFIX 2.30.61: siehe Kommentar bei roaming_purge_ap() - sonst
  // uebernimmt der naechste AP, der diesen Slot bekommt, fremde
  // Roaming-Paare von seinem Vorgaenger.
  roaming_purge_ap((uint8_t)idx);
}

int aps_known_live_count()
{
  int n = 0;
  for (int u = 0; u < aps_known_count; u++) {
    if (! ap_slot_free(u)) n++;
  }
  return n;
}

// ===================== NTP-Zeitsynchronisation (MUSS HIER SEIN!) =====================
bool ntp_synced = false;
time_t ntp_epoch_at_sync = 0;      // Unix-Zeit zum Sync-Zeitpunkt
uint32_t millis_at_ntp_sync = 0;   // millis() zum selben Zeitpunkt (fuer den Versatz)

// NEU 2.12.0: Timezone und Auto-Save
// NEU 2.17.8: -12 bis 12 frei einstellbar (Punkt 9), Standardwert 1 (MEZ/
// Mitteleuropa) bleibt wie bisher.
int ntp_timezone_hours = 1;        // UTC-Offset in Stunden (Standard: +1)

// NEU 2.17.6: Status-LED (Paket 7)
int status_led_pin = -1;           // -1 = deaktiviert (kein Pin konfiguriert)
bool status_led_test_state = false; // manueller Test-Toggle (Taste 't' in Hidden Settings)
// NEU 2.17.7: viele Onboard-LEDs sind aktiv-LOW verdrahtet (LED an, wenn
// der Pin LOW ist). true = invertierte Logik.
bool status_led_active_low = false;
bool led_boot_phase = true;        // true bis das Hauptmenue zum ersten Mal erreicht wird

// NEU 2.21.0: Signalisierungspin (ähnlich wie Status-LED, aber unabhängig)
int signal_pin = -1;                // -1 = deaktiviert (kein Pin konfiguriert)
bool signal_enabled = true;         // unabhängig von GPIO - kann aktiviert/deaktiviert sein
bool signal_test_state = false;     // manueller Test-Toggle (Taste 'b' in Hidden Settings)
bool signal_active_low = false;     // invertierte Logik (optional)
uint64_t signal_boot_pulse_time_ms = 0;  // Zeitstempel für Boot-Signal (500ms)
bool signal_boot_pulse_sent = false;     // Flag ob Boot-Signal schon gesendet wurde

// NEU 2.20.0 FEATURE 3: GPIO 0 Button (Flash-Button) für Auto-Save
uint32_t gpio0_last_press_time = 0;  // Debouncing: verhindert mehrfach-Trigger
bool gpio0_pressed = false;           // Current Button State

// NEU 2.29.0: ADC-Eingang zur Akkuspannungs-Ueberwachung. Einpunkt-
// Kalibrierung: adc_calib_raw haelt den rohen ADC-Wert (0-1023), der zum
// Zeitpunkt der Kalibrierung zusammen mit adc_calib_mv (vom Nutzer per
// Multimeter gemessene tatsaechliche Spannung, in Millivolt) erfasst wurde.
// Laufzeit-Spannung = adc_calib_mv * (aktueller ADC-Wert / adc_calib_raw) -
// setzt lineares Verhalten voraus (gilt fuer einen ohmschen Spannungsteiler
// an einem linearen ADC). adc_calib_raw==0 bedeutet "nicht kalibriert".
uint16_t adc_calib_raw = 0;     // ADC-Rohwert (0-1023) zum Kalibrierzeitpunkt
uint16_t adc_calib_mv = 0;      // vom Nutzer gemessene Spannung zum Kalibrierzeitpunkt, in mV
#define ADC_LOW_VOLTAGE_THRESHOLD_MV 3200  // Schwelle: 3,20 V
// Zustand der 3-fach-Bestaetigung (Messfehler-Vermeidung, s. Anforderung):
// 0 = keine Unterschreitung erkannt/in Bestaetigung; 1-2 = so viele
// aufeinanderfolgende Bestaetigungsmessungen (im 5s-Abstand) bereits unter
// der Schwelle. Bei 3 wird ausgeloest und sofort wieder auf 0 gesetzt.
uint8_t adc_low_confirm_count = 0;
uint32_t adc_low_confirm_last_ms = 0;
// Latch: verhindert wiederholtes Ausloesen, solange die Spannung unten
// bleibt. Wird erst zurueckgesetzt, wenn die Spannung wieder ueber die
// Schwelle steigt - erst dann kann das Ereignis erneut ausgeloest werden.
bool adc_low_event_fired = false;

// NEU 2.30.35: Erweiterte Akku-Unterspannungswarnung. Nutzt bewusst den
// bestehenden Latch (adc_low_event_fired) als "Warnung aktiv"-Zustand fuer
// die LED (siehe led_update()) - keine neue, parallele Zustandslogik. Der
// 5-fache Signalpin-Impuls ist dagegen ein einmaliges, zeitlich begrenztes
// Ereignis und braucht daher ein eigenes kleines Non-Blocking-Zeitfenster
// (analog zum bestehenden Rueckkehr-Puls), das GENAU EINMAL pro bestaetigtem
// Unterspannungsereignis abgespielt wird.
bool adc_low_pulse_active = false;
uint32_t adc_low_pulse_start_ms = 0;

// =====================================================================
// NEU 2.30.34: Passive RAM-/Stack-Diagnose ("Debug RAM Memory")
// =====================================================================
// Kernprinzip (siehe Kopf-Changelog fuer die vollstaendige Spezifikation):
// MESSEN -> mit bisherigem Extremwert VERGLEICHEN -> ggf. neuen Extremwert
// SPEICHERN. Rein beobachtend - greift NIE in den normalen Programmablauf
// ein (kein Abbruch, kein Ueberspringen/Deaktivieren von Funktionen, keine
// Speicherfreigabe, keine "Test"-Allokation, keine Aenderung an Timing/
// Timeouts/Netzwerk/Scan/ntfy/HTTP/Dateizugriffen, keine automatische
// Reaktion oder Bewertung, kein Neustart).
//
// Standardzustand nach jedem Neustart: AUS. Bei AUS erfolgt UEBERHAUPT
// keine Aufzeichnung (ram_debug_sample() kostet dann nur einen einzigen
// if-Vergleich). Keine Flash-Speicherung, keine Messwert-Historie - es
// werden ausschliesslich die aktuellen Extremwerte + zugehoerige Messpunkt-
// ID + ein Messzaehler gehalten (siehe RamDebugState - insgesamt nur wenige
// Byte gross, keine grossen globalen Arrays, keine dynamischen Puffer,
// keine String-Objekte fuer Messpunktnamen).

// Kompakte numerische Messpunkt-IDs statt dynamischer Strings. Reihenfolge
// muss zu RAM_DEBUG_POINT_NAMES (weiter unten) passen.
enum RamDebugPoint : uint8_t {
  RDP_NONE = 0,
  RDP_LOOP,              // Hauptloop
  RDP_MENU,              // Menueverarbeitung (Bildschirm neu zeichnen)
  RDP_INPUT,             // Eingabeverarbeitung (menu_handle_serial)
  RDP_NETWORK,           // zentrale Netzwerkfunktionen (WLAN-Verbindungsaufbau)
  RDP_WIFI_SCAN,         // Kanal-Hopping/Scanner
  RDP_AP_CAPTURE,        // AP-Erfassung/-Verarbeitung (Beacon-Zweig in promisc_cb)
  RDP_CLIENT_CAPTURE,    // Client-Erfassung/-Verarbeitung (Datenpaket-Zweig in promisc_cb)
  RDP_AP_LIST,           // AP-/SSID-Listenausgabe
  RDP_CLIENT_LIST,       // Client-Listenausgabe
  RDP_VENDOR_LOOKUP,     // Vendor-Lookup (Flash-Datenbank)
  RDP_VENDOR_CACHE,      // Vendor-Cache
  RDP_LITTLEFS,          // LittleFS-Zugriffe allgemein (Speichern/Laden)
  RDP_FILE_LIST,         // Dateiliste (Punkt 6)
  RDP_HTTP_SERVER,       // HTTP-Datei-Server (Punkt 7)
  RDP_HTTP_DOWNLOAD,     // HTTP-Upload/-Download (Browser <-> ESP)
  RDP_BEACON_ANALYSIS,   // Beacon-Rohanalyse (Punkt 3, "w"+Zahl)
  RDP_CLIENT_ANALYSIS,   // Client-/Probe-Request-Rohanalyse
  RDP_WATCHLIST,         // Watchlist-Verarbeitung
  RDP_NTFY_START,
  RDP_NTFY_FILE_OPEN,
  RDP_NTFY_FILE_READ,
  RDP_NTFY_REQUEST_BUILD,
  RDP_NTFY_HTTP_BEGIN,
  RDP_NTFY_SEND,
  RDP_NTFY_END,
  // NEU 2.30.37: tiefere Instrumentierung des Promiscuous-Callback-Pfads
  // (echte Funktionsgrenzen statt nur ein Punkt kurz vor register_beacon()/
  // register_client()) - siehe Entwickleranweisung Pkt.7/17.
  RDP_PROMISC_CALLBACK,  // Eintritt in den Promiscuous Callback selbst
  RDP_PARSE_BEACON,      // parse_beacon()
  RDP_REGISTER_BEACON,   // register_beacon()
  RDP_PARSE_DATA,        // parse_data()
  RDP_REGISTER_CLIENT,   // register_client()
  RDP_COUNT   // muss letzter Eintrag bleiben - Anzahl der IDs
};

// BUGFIX 2.30.47: explizite Deklaration direkt nach der Enum-Definition -
// gleicher Grund wie bei default_ascending_for() & Co. weiter oben (siehe
// dortiger Kommentar).
inline void ram_debug_sample(RamDebugPoint point);

// Statische Klartextnamen, ausschliesslich im Flash (PROGMEM) - kein RAM-
// Verbrauch im Ruhezustand. Reihenfolge MUSS zu RamDebugPoint passen.
static const char RDP_NAME_00[] PROGMEM = "-";
static const char RDP_NAME_01[] PROGMEM = "LOOP";
static const char RDP_NAME_02[] PROGMEM = "MENU";
static const char RDP_NAME_03[] PROGMEM = "INPUT";
static const char RDP_NAME_04[] PROGMEM = "NETWORK";
static const char RDP_NAME_05[] PROGMEM = "WIFI_SCAN";
static const char RDP_NAME_06[] PROGMEM = "AP_CAPTURE";
static const char RDP_NAME_07[] PROGMEM = "CLIENT_CAPTURE";
static const char RDP_NAME_08[] PROGMEM = "AP_LIST";
static const char RDP_NAME_09[] PROGMEM = "CLIENT_LIST";
static const char RDP_NAME_10[] PROGMEM = "VENDOR_LOOKUP";
static const char RDP_NAME_11[] PROGMEM = "VENDOR_CACHE";
static const char RDP_NAME_12[] PROGMEM = "LITTLEFS";
static const char RDP_NAME_13[] PROGMEM = "FILE_LIST";
static const char RDP_NAME_14[] PROGMEM = "HTTP_SERVER";
static const char RDP_NAME_15[] PROGMEM = "HTTP_DOWNLOAD";
static const char RDP_NAME_16[] PROGMEM = "BEACON_ANALYSIS";
static const char RDP_NAME_17[] PROGMEM = "CLIENT_ANALYSIS";
static const char RDP_NAME_18[] PROGMEM = "WATCHLIST";
static const char RDP_NAME_19[] PROGMEM = "NTFY_START";
static const char RDP_NAME_20[] PROGMEM = "NTFY_FILE_OPEN";
static const char RDP_NAME_21[] PROGMEM = "NTFY_FILE_READ";
static const char RDP_NAME_22[] PROGMEM = "NTFY_REQUEST_BUILD";
static const char RDP_NAME_23[] PROGMEM = "NTFY_HTTP_BEGIN";
static const char RDP_NAME_24[] PROGMEM = "NTFY_SEND";
static const char RDP_NAME_25[] PROGMEM = "NTFY_END";
static const char RDP_NAME_26[] PROGMEM = "CALLBACK";
static const char RDP_NAME_27[] PROGMEM = "PARSE_BEACON";
static const char RDP_NAME_28[] PROGMEM = "REGISTER_BEACON";
static const char RDP_NAME_29[] PROGMEM = "PARSE_DATA";
static const char RDP_NAME_30[] PROGMEM = "REGISTER_CLIENT";
static const char* const RAM_DEBUG_POINT_NAMES[RDP_COUNT] PROGMEM = {
  RDP_NAME_00, RDP_NAME_01, RDP_NAME_02, RDP_NAME_03, RDP_NAME_04,
  RDP_NAME_05, RDP_NAME_06, RDP_NAME_07, RDP_NAME_08, RDP_NAME_09,
  RDP_NAME_10, RDP_NAME_11, RDP_NAME_12, RDP_NAME_13, RDP_NAME_14,
  RDP_NAME_15, RDP_NAME_16, RDP_NAME_17, RDP_NAME_18, RDP_NAME_19,
  RDP_NAME_20, RDP_NAME_21, RDP_NAME_22, RDP_NAME_23, RDP_NAME_24,
  RDP_NAME_25, RDP_NAME_26, RDP_NAME_27, RDP_NAME_28, RDP_NAME_29,
  RDP_NAME_30
};

// Gesamter Speicherbedarf der Diagnose: nur diese eine kleine Struktur
// (keine Historie, keine Arrays je Messpunkt).
struct RamDebugState {
  bool enabled = false;               // Standard nach Neustart: AUS
  uint32_t measurement_count = 0;

  uint32_t min_free_heap = 0xFFFFFFFFUL;
  uint8_t  min_free_heap_point = RDP_NONE;

  uint32_t min_max_free_block = 0xFFFFFFFFUL;
  uint8_t  min_max_free_block_point = RDP_NONE;

  uint8_t  max_fragmentation = 0;
  uint8_t  max_fragmentation_point = RDP_NONE;

  uint32_t min_free_stack = 0xFFFFFFFFUL;
  uint8_t  min_free_stack_point = RDP_NONE;
};
RamDebugState ram_debug;

// Setzt ausschliesslich die RAM-Debug-Messwerte zurueck (Menuepunkt
// "Messwerte loeschen" bzw. neue Messperiode beim Einschalten) - veraendert
// keinerlei normale Programmparameter.
void ram_debug_reset()
{
  ram_debug.measurement_count = 0;
  ram_debug.min_free_heap = 0xFFFFFFFFUL;
  ram_debug.min_free_heap_point = RDP_NONE;
  ram_debug.min_max_free_block = 0xFFFFFFFFUL;
  ram_debug.min_max_free_block_point = RDP_NONE;
  ram_debug.max_fragmentation = 0;
  ram_debug.max_fragmentation_point = RDP_NONE;
  ram_debug.min_free_stack = 0xFFFFFFFFUL;
  ram_debug.min_free_stack_point = RDP_NONE;
}

// Kernfunktion: misst die vier Werte, vergleicht mit dem bisherigen Extrem-
// wert und speichert ggf. den neuen Extremwert + Messpunkt. Nutzt aus-
// schliesslich vorhandene Core-Funktionen (keine "Test"-Allokation). Wird
// nur bei eingeschalteter Analyse ausgefuehrt - im ausgeschalteten Zustand
// kostet der Aufruf nur den einen if-Vergleich, es findet keinerlei
// Aufzeichnung statt.
inline void ram_debug_sample(RamDebugPoint point)
{
  if (!ram_debug.enabled) return;

  ram_debug.measurement_count++;

  uint32_t heap = ESP.getFreeHeap();
  if (heap < ram_debug.min_free_heap) {
    ram_debug.min_free_heap = heap;
    ram_debug.min_free_heap_point = (uint8_t) point;
  }

  uint32_t block = (uint32_t) ESP.getMaxFreeBlockSize();
  if (block < ram_debug.min_max_free_block) {
    ram_debug.min_max_free_block = block;
    ram_debug.min_max_free_block_point = (uint8_t) point;
  }

  uint8_t frag = (uint8_t) ESP.getHeapFragmentation();
  if (frag > ram_debug.max_fragmentation) {
    ram_debug.max_fragmentation = frag;
    ram_debug.max_fragmentation_point = (uint8_t) point;
  }

  uint32_t stack = ESP.getFreeContStack();
  if (stack < ram_debug.min_free_stack) {
    ram_debug.min_free_stack = stack;
    ram_debug.min_free_stack_point = (uint8_t) point;
  }
}

// Kopiert den zu einer Messpunkt-ID gehoerenden Klartextnamen aus dem Flash
// in einen kleinen Stack-Puffer (kein dynamischer String) - Vorbild: das
// bestehende subtype_buf-Muster in print_beacon_or_proberesp().
void ram_debug_point_name(uint8_t point, char* buf, size_t buflen)
{
  if (point >= RDP_COUNT) point = RDP_NONE;
  strncpy_P(buf, (PGM_P) pgm_read_ptr(&RAM_DEBUG_POINT_NAMES[point]), buflen - 1);
  buf[buflen - 1] = '\0';
}
// =====================================================================
// ENDE Passive RAM-/Stack-Diagnose (Datenstruktur/Kernfunktionen) -
// Menue siehe menu_enter_ram_debug(), Messpunkt-Aufrufe siehe die
// jeweils markierten Stellen im restlichen Programm ("NEU 2.30.34").
// =====================================================================

// =====================================================================
// NEU 2.30.35/2.30.37: Call-Chain-Erweiterung der RAM-/Stack-Diagnose
// =====================================================================
// Rein ADDITIV zur bestehenden Diagnose oben - ram_debug_sample() und
// RamDebugState (Free Heap/Max Free Block/Fragmentation/Free Stack samt
// deren Minimum/Maximum-Messpunkt) werden NICHT veraendert (Vorgabe Pkt.19
// bzw. Pkt.3 der 2.30.37-Anweisung).
//
// KORREKTUR 2.30.37 (Entwickleranweisung "Call-Chain grundlegend
// korrigieren", Pkt.1/2/5): die urspruengliche v2.30.35-Umsetzung fuehrte
// EINE einzige globale aktive Kette. Da der Promiscuous Callback den
// Hauptprogrammablauf jederzeit unterbrechen kann (asynchron, nicht als
// normaler synchroner Unterfunktionsaufruf), wurde dadurch faelschlich der
// Eindruck erweckt, z.B. "INPUT -> AP_LIST -> VENDOR_LOOKUP -> AP_CAPTURE"
// sei eine echte Caller->Callee-Kette - tatsaechlich war das nur eine
// zufaellige Ueberlagerung von zwei UNABHAENGIGEN Ausfuehrungskontexten.
// Deshalb jetzt: ZWEI getrennte Ketten-Kontexte (Hauptprogramm/Menue vs.
// Promiscuous Callback), die niemals miteinander vermischt werden. Eine
// im Callback begonnene Kette startet IMMER bei Tiefe 0 und enthaelt
// ausschliesslich Funktionen, die tatsaechlich synchron innerhalb dieses
// einen Callback-Durchlaufs aufgerufen wurden.
#define CALL_CHAIN_MAX_DEPTH 8   // ausreichend fuer die real vorkommenden Verschachtelungen dieses Projekts

enum CallChainContext : uint8_t {
  CTX_MAIN = 0,      // Hauptprogramm/Menue/loop() - normaler synchroner Ablauf
  CTX_PROMISC = 1,   // Promiscuous Callback - eigener, unabhaengiger Kontext
  CTX_COUNT = 2
};

bool call_chain_enabled = false;

// Kompakte Momentaufnahme einer Aufrufkette: pro Ebene nur die numerische
// Funktions-ID (RamDebugPoint) + der beim Eintritt in diese Ebene noch freie
// Stack - keine Strings, keine Zeitstempel, keine variable Groesse. Zusaetzlich
// (NEU 2.30.37) der Kontext, aus dem die Kette stammt, damit die Anzeige klar
// zwischen Hauptprogramm und Callback unterscheiden kann (Vorgabe Pkt.15).
struct CallChainSnapshot {
  uint8_t depth = 0;
  uint8_t point[CALL_CHAIN_MAX_DEPTH] = {};
  uint32_t entry_stack[CALL_CHAIN_MAX_DEPTH] = {};
  CallChainContext context = CTX_MAIN;
};

// Aktuell aktive Kette JE Kontext (lebt nur waehrend der jeweiligen
// verschachtelten Aufrufe INNERHALB DESSELBEN Kontexts, siehe CallChainGuard
// weiter unten). Zwei kleine feste Arrays statt einem grossen - kein
// dynamischer Speicher, keine Vermischung der Kontexte.
struct ChainState {
  uint8_t depth = 0;
  uint8_t point[CALL_CHAIN_MAX_DEPTH] = {};
  uint32_t entry_stack[CALL_CHAIN_MAX_DEPTH] = {};
};
ChainState call_chain_state[CTX_COUNT];

// BUGFIX 2.30.47 (Codegroesse reduzieren, siehe "dangerous relocation"-
// Linkerfehler): die SP-Adress-Vergleichsdiagnose aus 2.30.38 war eine
// einmalige Untersuchungshilfe, um zu klaeren, ob Hauptprogramm und
// Promiscuous Callback denselben physischen Stack nutzen. Das ist laengst
// beantwortet (bestaetigt: zwei verschiedene Stacks) - fuer den laufenden
// Betrieb nicht mehr noetig, deshalb entfernt.

// Kompakter Aufrufzaehler je Funktions-ID (Vorgabe Pkt.11: EIN Zaehler
// pro ID statt einer vollen Caller->Callee-Matrix, die bei ~30 IDs bereits
// knapp 1000 Zellen haette - damit bewusst kein "grosses Array"). Die
// tatsaechliche Caller->Callee-Beziehung fuer die jeweils interessanteste
// Kette ergibt sich stattdessen direkt aus den gespeicherten Snapshots
// unten (Pkt.11 der Erstanweisung, Pkt.16 hier).
uint32_t call_chain_call_count[RDP_COUNT] = {};

// Maximale beobachtete ECHTE Verschachtelungstiefe (je Kontext getrennt
// gemessen, damit ein Callback-Aufruf nicht als "Fortsetzung" einer tiefen
// Hauptprogramm-Kette gezaehlt wird) + zugehoerige Kette.
uint8_t call_chain_max_depth = 0;
CallChainSnapshot call_chain_snapshot_max_depth;

// Kette zum bisher niedrigsten waehrend aktiver Call-Chain-Analyse
// beobachteten freien Stack - bewusst weiterhin GETRENNT von
// ram_debug.min_free_stack (das bleibt unangetastet, siehe oben). Wird jetzt
// (NEU 2.30.37) sowohl beim Eintritt in eine Funktion als auch bei gezielten
// Zwischen-Messungen ("Probes", siehe CallChainGuard::probe(), Vorgabe Pkt.9)
// aktualisiert, damit nicht nur der Eintrittswert, sondern der tatsaechliche
// Tiefpunkt WAEHREND der Ausfuehrung erfasst wird.
uint32_t call_chain_min_stack = 0xFFFFFFFFUL;
CallChainSnapshot call_chain_snapshot_min_stack;

// Setzt ausschliesslich die Call-Chain-Diagnosewerte zurueck (Teil des
// bestehenden Menuepunkts "Messwerte loeschen") - keine Benutzereinstellungen,
// keine normalen Programmdaten, kein Flash-Zugriff.
void call_chain_reset()
{
  for (uint8_t c = 0; c < CTX_COUNT; c++) call_chain_state[c] = ChainState();
  for (uint8_t i = 0; i < RDP_COUNT; i++) call_chain_call_count[i] = 0;
  call_chain_max_depth = 0;
  call_chain_snapshot_max_depth = CallChainSnapshot();
  call_chain_min_stack = 0xFFFFFFFFUL;
  call_chain_snapshot_min_stack = CallChainSnapshot();
}

// Kopiert die aktuell aktive Kette EINES Kontexts in eine Snapshot-Struktur -
// gemeinsame Hilfsfunktion fuer die Max-Tiefe- und Min-Stack-Erfassung unten.
void call_chain_copy_active(uint8_t ctx, uint8_t *dst_depth, uint8_t *dst_point, uint32_t *dst_entry_stack, uint8_t *dst_context)
{
  ChainState &cs = call_chain_state[ctx];
  *dst_depth = cs.depth;
  *dst_context = ctx;
  for (uint8_t i = 0; i < cs.depth; i++) {
    dst_point[i] = cs.point[i];
    dst_entry_stack[i] = cs.entry_stack[i];
  }
}

// NEU 2.30.37: zentrale Stack-Minimum-Pruefung, aufgerufen sowohl beim
// Betreten einer instrumentierten Funktion als auch bei gezielten
// Zwischen-Messungen waehrend ihrer Ausfuehrung (Vorgabe Pkt.8/9) - damit
// wird nicht nur der Eintrittswert, sondern der tatsaechliche Tiefpunkt
// erfasst, samt der Kette, in der er auftrat.
void call_chain_note_stack(uint8_t ctx, uint32_t stack_now)
{
  if (ctx >= CTX_COUNT) ctx = CTX_MAIN;
  if (stack_now < call_chain_min_stack) {
    call_chain_min_stack = stack_now;
    call_chain_copy_active(ctx, &call_chain_snapshot_min_stack.depth, call_chain_snapshot_min_stack.point, call_chain_snapshot_min_stack.entry_stack, (uint8_t*)&call_chain_snapshot_min_stack.context);
  }
}

// RAII-Guard (gleiches Prinzip wie OfflineBannerGuard weiter oben): eine an
// einer bereits instrumentierten Funktion deklarierte Instanz traegt sich
// beim Erstellen in die aktive Kette IHRES Kontexts ein und beim Verlassen
// des Gueltigkeitsbereichs (Funktionsende, auch bei vorzeitigem return)
// automatisch wieder aus. Bewusst NUR einfache Ganzzahl-Operationen +
// ESP.getFreeContStack() - kein Serial, kein malloc/new/String, nicht
// blockierend, daher auch innerhalb des Promiscuous Callbacks unbedenklich.
//
// WICHTIG (Vorgabe Pkt.5): der Kontext (CTX_MAIN oder CTX_PROMISC) wird
// explizit an jeder Aufrufstelle angegeben, NIE automatisch geerbt - dadurch
// kann eine im Callback begonnene Kette niemals an eine zufaellig zum selben
// Zeitpunkt im Hauptprogramm aktive Kette "andocken".
struct CallChainGuard {
  bool pushed = false;
  CallChainContext ctx = CTX_MAIN;

  CallChainGuard(RamDebugPoint point, CallChainContext context = CTX_MAIN)
  {
    ctx = context;
    // NEU 2.30.35: Vorgabe Pkt.2/13 - Call-Chain darf NUR laufen, wenn
    // zusaetzlich auch die RAM-Analyse selbst eingeschaltet ist, auch wenn
    // der Call-Chain-Schalter fuer sich genommen EIN ist.
    if (!call_chain_enabled || !ram_debug.enabled) return;
    ChainState &cs = call_chain_state[ctx];
    if (cs.depth >= CALL_CHAIN_MAX_DEPTH) return;  // feste Obergrenze, kein Ueberlauf

    uint32_t stack_now = ESP.getFreeContStack();
    cs.point[cs.depth] = (uint8_t) point;
    cs.entry_stack[cs.depth] = stack_now;
    cs.depth++;
    pushed = true;

    if ((uint8_t) point < RDP_COUNT) call_chain_call_count[(uint8_t) point]++;

    if (cs.depth > call_chain_max_depth) {
      call_chain_max_depth = cs.depth;
      call_chain_copy_active(ctx, &call_chain_snapshot_max_depth.depth, call_chain_snapshot_max_depth.point, call_chain_snapshot_max_depth.entry_stack, (uint8_t*)&call_chain_snapshot_max_depth.context);
    }

    call_chain_note_stack(ctx, stack_now);
  }

  // NEU 2.30.37 (Vorgabe Pkt.8/9): gezielte Zwischen-Messung waehrend die
  // Funktion noch laeuft - erfasst einen ggf. niedrigeren Stackwert
  // INNERHALB dieses Frames, ohne die Kette selbst zu veraendern und ohne
  // eine vollstaendige Verlaufshistorie zu speichern (nur das Minimum samt
  // Kette wird ggf. aktualisiert, wie beim Eintritt auch).
  void probe()
  {
    if (!pushed) return;
    call_chain_note_stack(ctx, ESP.getFreeContStack());
  }

  ~CallChainGuard()
  {
    if (pushed) {
      ChainState &cs = call_chain_state[ctx];
      if (cs.depth > 0) cs.depth--;
    }
  }
};
// =====================================================================
// ENDE Call-Chain-Erweiterung (Datenstruktur/Kernfunktionen) - Guard-
// Einsatz siehe die jeweils markierten Stellen ("NEU 2.30.35"/"2.30.37"),
// Anzeige siehe menu_enter_ram_debug()/menu_enter_call_chain_view().
// =====================================================================


// NEU 2.17.8: ersetzt das alte manuelle "ntp_use_mesz"-Umschalten (MEZ/
// MESZ) - dst_enabled bedeutet nur noch "automatische Sommer-/Winterzeit-
// Umstellung ist fuer diese Zeitzone aktiv", der aktuelle Zustand
// (gerade Sommer- oder Winterzeit) wird laufend automatisch berechnet
// (siehe eu_dst_active()). Bezeichnung bewusst englisch/allgemein statt
// "MESZ", da die Umstellung nicht nur in Europa existiert.
bool dst_enabled = false;
bool auto_save_enabled = false;    // Auto-Save täglich um 00:00 Uhr (NTP) oder 24h Timer
uint32_t auto_save_last_run_millis = 0;  // Zeitstempel des letzten Auto-Save
uint32_t auto_save_suppressed_until = 0;  // NEU 2.19.0: Speichern für 60s sperren nach erfolgreichem Save
uint32_t auto_save_last_run_day = 0;     // NEU 2.20.2 BUG2: Tages-Timestamp um 0:00 Uhr (verhindert mehrfaches Speichern)

char ntp_text_edit_buf[65];
uint8_t ntp_text_edit_len = 0;
int ntp_edit_target = 0;           // 1=SSID 2=Passwort 3=Server 4=Timezone (neu)

// ===================== Werkseinstellungen (Hidden Settings) =====================
// NEU 2.13.0: Channel-Filter und Scan-Verweilzeit
char channel_filter[32] = "alle";  // NEU 2.17.9: RAM-Opt ('1,6,11,36,40...')   // "alle" oder kommagetrennt "1,6,11"
uint16_t channel_dwell_ms = 100;    // Verweilzeit pro Kanal in Millisekunden

// NEU 2.16.0: Auto-Load Dateiname bei Neustart
char autoload_filename[32] = "";  // NEU 2.17.9: RAM-Opt ('autosave...' ~25 char)    // z.B. "autosave_260801_103727" oder leer
// NEU 2.31.00: Kompression beim Speichern EIN/AUS; Laden unterstuetzt beide Formate.
bool scenario_compression_enabled = true;
bool autoload_file_not_found = false;  // Flag: Datei existierte nicht beim Boot

char factory_reset_input_buf[12];
uint8_t factory_reset_input_len = 0;
// probes_known[] entfaellt (Schritt 1)

// Merkt sich pro Client-Slot den zuletzt angezeigten RSSI-Wert (Punkt 3:
// RSSI-Trend-Pfeile). -1000 = Sentinel "noch nie angezeigt".
// NEU 2.17.9: int8_t statt int (RSSI: -128..127), spart 750 Byte RAM
int8_t prev_shown_rssi[MAX_CLIENTS_TRACKED];

// Punkt "Einstellungen": Online = laufender Funkverkehr aktualisiert die
// Listen weiter; Offline = Listen werden eingefroren (z.B. um ein per
// Punkt 6 geladenes Szenario in Ruhe zu untersuchen).
bool online_mode = true;

// Ueberlaufschutz fuer aps_known[]/clients_known[] (Einstellungen 7/8):
// bisher wurden beide Listen beim Erreichen von MAX_APS_TRACKED/
// MAX_CLIENTS_TRACKED kommentarlos und komplett geleert. Jetzt wird
// zusaetzlich IMMER akustisch gewarnt (3x Bell), und optional kann vor
// dem Leeren automatisch gesichert und/oder auf Offline geschaltet
// werden (haelt die Aufzeichnung an, bewahrt die Liste unveraendert).
bool auto_save_on_overflow = false;
// NEU 2.29.9: Default auf true geaendert - bei Listenueberlauf soll ohne
// bewusstes manuelles Abschalten immer zuerst in den Offline-Modus
// gewechselt werden (Liste bleibt unangetastet erhalten). Nur wer das
// aktiv ausschaltet, bekommt die automatischen Ueberlauf-Faellmechanismen
// (aeltester Client / AP ohne Geraete).
bool auto_offline_on_overflow = true;
// NEU 2.29.1 BUGFIX: register_beacon()/register_client() laufen aus dem
// zeitkritischen wifi_set_promiscuous_rx_cb()-Kontext heraus (siehe
// Kommentar oben bei promisc_cb). Die fruehere Ueberlauf-Behandlung
// (handle_list_overflow()) rief direkt darin delay(150) dreifach sowie ggf.
// save_current_lists() (LittleFS-Dateizugriff ueber ggf. hunderte
// Eintraege) und go_offline() auf - all das blockierend, direkt im SDK-
// Callback. Das hungerte den WLAN-Stack aus und fuehrte zuverlaessig zu
// einem Reset. Jetzt setzt der Callback nur noch dieses leichte Flag
// (0=keiner, 1=AP-Liste, 2=Client-Liste) und kehrt sofort zurueck - die
// eigentliche (potenziell dauernde) Behandlung erfolgt sicher aus dem
// Hauptloop heraus (process_pending_overflow(), aufgerufen aus
// menu_periodic()), wo delay()/Datei-I/O unproblematisch sind.
volatile uint8_t pending_overflow_type = 0;
// NEU 2.29.2 BUGFIX: waehrend process_pending_overflow() laeuft (insbesondere
// waehrend des ggf. laengeren save_current_lists()-Aufrufs bei Auto-Save)
// bleibt die betroffene Liste bis zum Schluss noch bei MAX_*_TRACKED stehen -
// in dieser Zeit eintreffende echte Frames loesten in register_beacon()/
// register_client() ERNEUT signal_pending_overflow() aus, weil
// pending_overflow_type zu Beginn der Bearbeitung schon auf 0 zurueckgesetzt
// wird. Das fuehrte zu einer zweiten, ungewollten Verarbeitungsrunde direkt
// im Anschluss (doppelte Meldung, doppelte Sicherung mit dann nur noch
// wenigen frisch eingetroffenen Eintraegen). Dieses Flag unterdrueckt
// signal_pending_overflow() waehrend eine Bearbeitung bereits laeuft.
volatile bool overflow_processing_active = false;

// Zeitpunkt (in Sekunden seit Boot), an dem zuletzt in den Offline-Modus
// gewechselt wurde. Waehrend offline wird "last seen" gegen DIESEN
// eingefrorenen Zeitpunkt berechnet statt gegen die laufende Zeit, damit
// die Anzeige nicht weiterzaehlt.
uint64_t offline_freeze_time = 0;

#define disable 0
#define enable  1
#define MAX_CLIENT_AGE 1000
#define CHECK_INTERVAL 60

unsigned int channel = 1;
uint32_t last_check_time, next_check_time;

// Liefert die aktuelle Unix-Zeit (Sekunden seit 1.1.1970 UTC), sofern per
// NTP synchronisiert, sonst 0. Rechnet den seit der Synchronisation
// vergangenen millis()-Versatz mit ein, ohne dafuer bei jedem Aufruf neu
// mit dem NTP-Server zu kommunizieren.
time_t current_unix_time()
{
  if (!ntp_synced) return 0;
  return ntp_epoch_at_sync + (time_t)((millis() - millis_at_ntp_sync) / 1000);
}

// NEU 2.17.8: Automatische Sommer-/Winterzeit-Umstellung (Daylight Saving
// Time). Implementiert ist die EU-Regel (u.a. Deutschland): Umstellung
// jeweils am letzten Sonntag im Maerz und im letzten Sonntag im Oktober,
// zum Zeitpunkt 01:00 UTC. Andere Weltregionen mit DST (z.B. USA, die
// andere Umstellungstermine verwenden, oder die Suedhalbkugel mit
// umgekehrter Saison) werden davon NICHT korrekt abgebildet - dafuer
// muesste die Regel pro Land/Region eigens hinterlegt werden. Fuer den
// hier eingestellten Standardfall (Mitteleuropa) ist das aber korrekt.
//
// Tage seit 1970-01-01 fuer ein Kalenderdatum (proleptic Gregorian,
// Howard-Hinnant-Algorithmus) - vermeidet mktime()/timegm(), deren
// Verhalten je nach Zeitzonen-Konfiguration der Toolchain variieren kann.
long days_from_civil(int y, int m, int d)
{
  y -= (m <= 2) ? 1 : 0;
  long era = (y >= 0 ? y : y - 399) / 400;
  unsigned yoe = (unsigned)(y - era * 400);
  unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
  unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
  return era * 146097 + (long)doe - 719468;
}

// Liefert den UTC-Zeitstempel (01:00 UTC) des letzten Sonntags im
// angegebenen Monat/Jahr - das ist der EU-Umstellungszeitpunkt.
time_t eu_dst_transition_utc(int year, int month)
{
  long last_day_of_month = days_from_civil(year, month, 31);  // faellt bei Bedarf automatisch in den Folgemonat, daher:
  // 31 existiert nicht in jedem Monat - fuer Maerz/Oktober (beide 31 Tage)
  // ist das aber immer korrekt.
  int weekday = (int)(((last_day_of_month % 7) + 7) % 7 + 4) % 7;  // 0=So..6=Sa, 1970-01-01 war ein Donnerstag
  long last_sunday_days = last_day_of_month - weekday;
  return (time_t)last_sunday_days * 86400 + 1 * 3600;  // 01:00 UTC
}

// Ist zum angegebenen UTC-Zeitpunkt gerade Sommerzeit (nach EU-Regel)?
bool eu_dst_active(time_t utc_now)
{
  struct tm* t = gmtime(&utc_now);
  int year = t->tm_year + 1900;
  time_t dst_start = eu_dst_transition_utc(year, 3);   // letzter Sonntag Maerz
  time_t dst_end = eu_dst_transition_utc(year, 10);    // letzter Sonntag Oktober
  return (utc_now >= dst_start && utc_now < dst_end);
}

// NEU 2.12.0: Gibt aktuelle Zeit mit Timezone-Offset zurueck (inkl.
// automatischer Sommer-/Winterzeit, falls dst_enabled)
time_t current_unix_time_with_tz()
{
  if (!ntp_synced) return 0;
  time_t utc_now = ntp_epoch_at_sync + (time_t)((millis() - millis_at_ntp_sync) / 1000);
  
  // Addiere Timezone-Offset (in Sekunden)
  time_t tz_offset = (time_t)(ntp_timezone_hours * 3600);
  if (dst_enabled && eu_dst_active(utc_now)) tz_offset += 3600;
  
  return utc_now + tz_offset;
}
// die aktuelle Uhrzeit. Wird nur beim Boot aufgerufen (vor dem Aktivieren
// des Promiscuous-Sniffings), daher hier kein Pausieren/Reaktivieren des
// Sniffings noetig wie bei notif_send_now().
void sync_ntp_time()
{
  if (!ntp_enabled || ntp_wifi_ssid[0] == '\0') return;
  ram_debug_sample(RDP_NETWORK);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
  CallChainGuard __cc_guard(RDP_NETWORK);  // NEU 2.30.35: Call-Chain-Erweiterung

  Serial.println(F(" NTP: hole aktuelle Uhrzeit ..."));

  WiFi.mode(WIFI_OFF);
  delay(200);
  WiFi.mode(WIFI_STA);
  delay(100);
  WiFi.begin(ntp_wifi_ssid, ntp_wifi_pass);

  uint32_t start = millis();
  bool connected = false;
  while (millis() - start < 15000) {
    if (WiFi.status() == WL_CONNECTED) { connected = true; break; }
    delay(200);
    yield();
  }

  if (!connected) {
    Serial.println(F(" NTP: WLAN-Verbindung fehlgeschlagen (Timeout nach 15s)."));
  } else {
    configTime(0, 0, ntp_server);  // UTC, keine Sommerzeit-Verschiebung
    time_t now = 0;
    uint32_t sync_start = millis();
    while (millis() - sync_start < 10000) {
      now = time(nullptr);
      if (now > 1577836800) break;  // > 01.01.2020 00:00 UTC => synchronisiert
      delay(200);
      yield();
    }
    if (now > 1577836800) {
      ntp_epoch_at_sync = now;
      millis_at_ntp_sync = millis();
      ntp_synced = true;
      Serial.printf_P(PSTR(" NTP: Zeit synchronisiert (%s Server): %s"), ntp_server, ctime(&now));
    } else {
      Serial.println(F(" NTP: Zeitsynchronisation fehlgeschlagen (Timeout nach 10s)."));
    }
  }

  WiFi.disconnect(true);
  delay(100);

  // BUGFIX 2.12.0: Nach WiFi.disconnect() muss die Promiscuous-Init
  // komplett wiederholt werden. Der Funk-Chip war sonst in einem
  // Zwischenzustand "gehangen" und empfing keine Pakete mehr (Scanner taub).
  // Das gleiche Problem gab es in v2.8.3 beim ntfy-Versand (dort identische Loesung).
  wifi_promiscuous_enable(disable);
  delay(50);
  wifi_set_opmode(STATION_MODE);
  delay(50);
  wifi_set_channel(channel);
  delay(50);
  wifi_set_promiscuous_rx_cb(promisc_cb);
  wifi_promiscuous_enable(enable);
  nothing_new = 0;
}

// NEU 2.17.6: Status-LED (Paket 7)
// PWMRANGE ist in manchen ESP8266-Core-Versionen nicht als Konstante
// verfuegbar (Compiler-Fehler "use of undeclared identifier") - deshalb
// eigene, feste Range definieren und per analogWriteRange() aktivieren.
#define STATUS_LED_PWM_RANGE 1023
// NEU 2.17.7: maximale Helligkeit beim Auf-/Abschwellen, in Prozent der
// vollen Range (0-100). Auf Wunsch auf 50% begrenzt.
#define STATUS_LED_MAX_BRIGHTNESS_PCT 50
// GPIO16 hat auf dem ESP8266 keine PWM-Hardware (eigenes RTC-Register,
// kein Timer angebunden) - analogWrite() dort waere wirkungslos bzw.
// undefiniert. Fuer diesen Pin wird stattdessen manuell im Software
// per kurzem An/Aus-Zyklus (Software-PWM) geschwellt.
#define STATUS_LED_SW_PWM_PERIOD_MS 20

// Richtet pinMode(OUTPUT) fuer den aktuell konfigurierten Pin ein. Wird
// beim Booten (falls ein Pin gespeichert ist) und direkt nach Aenderung
// der Einstellung aufgerufen.
void led_apply_pin_config()
{
  if (status_led_pin >= 0) {
    pinMode(status_led_pin, OUTPUT);
    if (status_led_pin != 16) analogWriteRange(STATUS_LED_PWM_RANGE);
    led_write_digital(true);  // NEU 2.20.5 BUG7: true (war false!) - LED beim Boot AN
  }
}

// Schaltet die LED logisch EIN/AUS, beruecksichtigt dabei
// status_led_active_low (invertierte Onboard-LED-Logik).
void led_write_digital(bool on)
{
  if (status_led_pin < 0) return;
  bool level_high = status_led_active_low ? !on : on;
  digitalWrite(status_led_pin, level_high ? HIGH : LOW);
}

// Schaltet die LED auf eine Helligkeitsstufe (0..STATUS_LED_PWM_RANGE),
// beruecksichtigt Polaritaet UND das GPIO16-Sonderfall (Software-PWM statt
// analogWrite, da dort keine PWM-Hardware existiert).
void led_write_pwm(int level_0_to_range, uint32_t now_ms)
{
  if (status_led_pin < 0) return;
  if (status_led_pin == 16) {
    uint32_t phase = now_ms % STATUS_LED_SW_PWM_PERIOD_MS;
    uint32_t on_time_ms = (uint32_t)(((float)level_0_to_range / STATUS_LED_PWM_RANGE) * STATUS_LED_SW_PWM_PERIOD_MS);
    led_write_digital(phase < on_time_ms);
    return;
  }
  int level = status_led_active_low ? (STATUS_LED_PWM_RANGE - level_0_to_range) : level_0_to_range;
  analogWrite(status_led_pin, level);
}

// Schaltet die LED sofort aus. Fuer blockierende/zeitkritische Vorgaenge
// (Dateitransfer, lange Listenausgabe, ntfy-Versand) - da diese synchron
// ablaufen und led_update() waehrenddessen nicht erneut aufgerufen wird,
// genuegt ein einmaliger Aufruf vor Beginn des jeweiligen Vorgangs.
void led_force_off()
{
  led_write_digital(false);
}

// ============================================================================
// NEU 2.21.0: SIGNALISIERUNGSPIN FUNKTIONEN
// ============================================================================

void signal_apply_pin_config()
{
  if (signal_pin >= 0) {
    pinMode(signal_pin, OUTPUT);
    if (signal_pin != 16) analogWriteRange(STATUS_LED_PWM_RANGE);
    signal_write_digital(false);  // starte mit Signal aus
  }
}

void signal_write_digital(bool on)
{
  if (signal_pin < 0) return;
  if (!signal_enabled) {  // wenn deaktiviert, immer aus
    digitalWrite(signal_pin, LOW);
    return;
  }
  bool level_high = signal_active_low ? !on : on;
  digitalWrite(signal_pin, level_high ? HIGH : LOW);
}

void signal_force_off()
{
  signal_write_digital(false);
}

void signal_boot_pulse()
{
  if (signal_pin < 0 || !signal_enabled) return;
  signal_boot_pulse_time_ms = millis();
  signal_boot_pulse_sent = true;
  signal_write_digital(true);
}

// NEU 2.27.1 REQ-4: Rueckkehr-Signalisierung (Menue 4/Watchlist). Nutzt
// bewusst dieselbe Pin-Infrastruktur wie der Boot-Puls (signal_pin,
// signal_enabled, signal_active_low, signal_write_digital()) - KEINE
// parallele Signalisierung. Eigenes, unabhaengiges Non-Blocking-Zeitfenster
// (return_pulse_active/return_pulse_start_time_ms), da Dauer (5ms statt
// des Boot-Pulses) und Ausloeser komplett unterschiedlich sind und sich
// sonst gegenseitig ueberschreiben koennten, falls beide Fenster sich
// zeitlich ueberlappen sollten.
void signal_start_return_pulse()
{
  if (signal_pin < 0 || !signal_enabled) return;
  if (!enable_return_pulse) return;
  return_pulse_start_time_ms = millis();
  return_pulse_active = true;
  signal_write_digital(true);
}

// NEU 2.30.35: Startet die einmalige 5-fache Impulsfolge (100ms ein/100ms
// aus) auf dem vorhandenen Signalpin bei bestaetigtem ADC-Unterspannungs-
// ereignis. Dieselbe Pin-Infrastruktur, nicht blockierend - die eigentliche
// Ansteuerung erfolgt Schritt fuer Schritt in signal_update().
void adc_low_start_pulse()
{
  if (signal_pin < 0 || !signal_enabled) return;
  adc_low_pulse_active = true;
  adc_low_pulse_start_ms = millis();
  signal_write_digital(true);  // Schritt 0: EIN
}

// Nicht blockierend, wird aus dem Hauptloop aufgerufen
// Pflegt das Boot-Signal (500ms aktiv nach Startup) UND den Rueckkehr-Puls
// (NEU 2.27.1, 5ms) - zwei unabhaengige Zeitfenster auf demselben Pin. Der
// Pin wird nur ausgeschaltet, wenn KEINES der beiden Fenster mehr aktiv ist
// (falls sich beide Fenster in der Praxis einmal ueberlappen sollten, faengt
// das ab, dass eines das andere vorzeitig abschaltet).
void signal_update()
{
  if (signal_pin < 0 || !signal_enabled) return;

  uint32_t now_ms = millis();

  if (signal_boot_pulse_sent) {
    uint32_t elapsed = now_ms - signal_boot_pulse_time_ms;
    if (elapsed >= 20) {
      signal_boot_pulse_sent = false;
    }
  }

  if (return_pulse_active) {
    uint32_t elapsed = now_ms - return_pulse_start_time_ms;
    if (elapsed >= RETURN_PULSE_DURATION_MS) {
      return_pulse_active = false;
    }
  }

  // NEU 2.30.35: Akku-Warnimpuls - 5x 100ms ein/100ms aus (10 Halbschritte),
  // danach automatisch beendet. Gerade Schritte = EIN, ungerade = AUS.
  if (adc_low_pulse_active) {
    uint32_t elapsed = now_ms - adc_low_pulse_start_ms;
    uint32_t step = elapsed / 100;
    if (step >= 10) {
      adc_low_pulse_active = false;
    } else {
      signal_write_digital((step % 2) == 0);
    }
  }

  // NEU 2.29.6 BUGFIX: signal_update() kannte den manuellen Test-Zustand
  // (Taste 'b') bisher nicht und hat ihn im naechsten loop()-Durchlauf
  // sofort wieder ausgeschaltet, da weder Boot-Puls noch Rueckkehr-Puls
  // aktiv waren - daher der "sehr kurze Impuls" beim Testen.
  if (!signal_boot_pulse_sent && !return_pulse_active && !signal_test_state && !adc_low_pulse_active) {
    signal_write_digital(false);
  }
}

// Nicht blockierend, wird aus dem Hauptloop bei jedem Durchlauf
// aufgerufen. Prioritaet (von oben nach unten):
//   1) kein Pin konfiguriert -> nichts tun
//   2) Hidden-Settings-Testmodus (Taste 't') hat Vorrang vor der Automatik
//   3) Bootphase (bis Hauptmenue erreicht) -> durchgehend an
//   4) Offline -> kurzer Blitz (50ms) alle 2s
//   5) Online/Scan-Betrieb -> langsames Auf-/Abschwellen (PWM, max. 50%)
void led_update()
{
  if (status_led_pin < 0) return;
  // NEU 2.30.35: Akku-Unterspannungswarnung hat Vorrang vor JEDER normalen
  // Zustandsanzeige (Menue/Scan/HTTP/Test-Toggle/...), solange das bestehende
  // Latch (adc_low_event_fired) aktiv ist - endet automatisch, sobald die
  // vorhandene ADC-Ueberwachung das Latch wieder loest (Spannungserholung).
  // Deutlich hektischer (100ms) als alle regulaeren Blinkmuster.
  if (adc_low_event_fired) {
    uint32_t warn_ms = millis();
    bool should_blink = ((warn_ms / 100) % 2) == 0;
    led_write_digital(should_blink);
    return;
  }
  if (menu_state == STATE_HIDDEN_SETTINGS) return;  // Test-Toggle hat Vorrang

  uint32_t now_ms = millis();

  // BOOT-PHASE: Durchgehend AN
  if (led_boot_phase) {
    led_write_digital(true);
    return;
  }

  // OFFLINE-MODUS: Fade In/Fade Out (Breathing Animation wie bisher)
  if (!online_mode) {
    const uint32_t breathe_period_ms = 1333;
    uint32_t phase = now_ms % breathe_period_ms;
    float t = (float)phase / (float)breathe_period_ms;
    float brightness = (1.0f - cosf(2.0f * PI * t)) / 2.0f;  // 0..1, sanfte Kurve
    brightness *= (STATUS_LED_MAX_BRIGHTNESS_PCT / 100.0f);
    led_write_pwm((int)(brightness * STATUS_LED_PWM_RANGE), now_ms);
    return;
  }

  // ONLINE/SCAN-BETRIEB: Alle 4 Sekunden für 30ms aufblitzen
  const uint32_t online_period_ms = 4000;  // 4 Sekunden (NEU 2.20.2 BUG3)
  const uint32_t online_flash_duration_ms = 30;  // 30ms Blitz (NEU 2.20.2 BUG3)
  uint32_t phase = now_ms % online_period_ms;
  bool should_flash = (phase < online_flash_duration_ms);
  led_write_digital(should_flash);
}

// ===================== FILE PROTECTION Globale Variablen (v2.25.0) =====================
// Schutz-Liste /protected.txt mit Dateinamen, die nicht angezeigt/gelöscht werden können
// wenn show_hidden == false. Taste 'h' allein schaltet show_hidden um.
// Taste 'h' + Nummer markiert/demarkiert die Datei als geschützt.
#define PROTECTED_FILE "/protected.txt"
bool show_hidden = false;  // false = versteckte Dateien ausblenden, true = anzeigen
char protected_list[32][32];  // Cache der geschützten Dateinamen (max 20 wie file_list_names)
uint8_t protected_count = 0;  // Anzahl der geschützten Dateien
bool file_protect_mode = false;  // Taste 'h' + Nummer-Modus aktiv
char file_protect_input_buf[4];
int file_protect_input_len = 0;

// ===================== FILE PROTECTION Hilfsfunktionen (v2.25.0) =====================

// Liest /protected.txt und ladet die geschützten Dateinamen in protected_list[]
void read_protected_list()
{
  protected_count = 0;
  if (!LittleFS.exists(PROTECTED_FILE)) {
    return;  // Datei existiert nicht → kein Schutz definiert
  }
  
  File f = LittleFS.open(PROTECTED_FILE, "r");
  if (!f) return;
  
  while (f.available() && protected_count < 32) {
    String line = f.readStringUntil('\n');
    line.trim();
    if (line.length() > 0) {
      line.toCharArray(protected_list[protected_count], 32);
      protected_count++;
    }
  }
  f.close();
}

// Prüft, ob ein Dateiname in der Schutzliste steht
bool is_file_protected(const char* filename)
{
  if (protected_count == 0) return false;
  
  for (int i = 0; i < protected_count; i++) {
    if (strcmp(protected_list[i], filename) == 0) {
      return true;
    }
  }
  return false;
}

// Togglet Schutzstatus: fügt zur protected.txt hinzu oder entfernt
// Gibt true zurück wenn jetzt geschützt, false wenn nicht geschützt
bool toggle_file_protection(const char* filename)
{
  // Erst prüfen ob Datei bereits geschützt
  bool was_protected = is_file_protected(filename);
  
  // protected.txt neu schreiben: alle außer filename wenn war_protected, sonst mit filename hinzufügen
  File f = LittleFS.open(PROTECTED_FILE, "w");
  if (!f) {
    Serial.println(F("[ERROR] Konnte /protected.txt nicht schreiben!"));
    return was_protected;  // Zustand unverändert
  }
  
  for (int i = 0; i < protected_count; i++) {
    if (!was_protected || strcmp(protected_list[i], filename) != 0) {
      f.println(protected_list[i]);
    }
  }
  
  // Neu hinzufügen wenn nicht war_protected
  if (!was_protected) {
    f.println(filename);
  }
  
  f.close();
  
  // Cache aktualisieren
  read_protected_list();
  
  return !was_protected;  // Neuer Status
}

void setup() {
  Serial.begin(115200);
  // Kurze Stabilisierungspause: direkt nach dem Oeffnen der seriellen
  // Verbindung sind USB-Serial-Adapter/Terminalprogramme oft noch nicht
  // bereit, die ersten Bytes zuverlaessig zu empfangen.
  delay(300);
  
  // NEU 2.20.5 BUG4: Boot Logo ZUALLERERST anzeigen (bevor alles andere)
  led_boot_phase = true;  // LED beim Boot durchgehend an
  
  
  // Diagnose-Ausgabe nur fuer die serielle Log-Mitschrift gedacht
//  Serial.printf_P(PSTR("\n\nSDK version:%s\n\r"), system_get_sdk_version());

  wifi_set_opmode(STATION_MODE);
  wifi_set_channel(channel);

  // Flash-Diagnose: die in der IDE eingestellte "Flash Size" bestimmt, wo
  // SPIFFS seinen Bereich im Flash vermutet. Stimmt sie nicht mit der
  // tatsaechlichen Chipgroesse ueberein (haeufig bei Klonen/China-Modulen
  // mit falscher/fehlender Chip-ID), schlagen begin() UND format()
  // gleichermassen fehl, weil der berechnete Adressbereich nicht zum
  // echten Chip passt. getFlashChipSize() = was der Sketch/die IDE-
  // Einstellung annimmt, getFlashChipRealSize() = was am Chip selbst
  // ausgelesen wird - weichen die voneinander ab, ist das die Ursache.
//  Serial.printf_P(PSTR("Flash: konfiguriert=%u Byte, real erkannt=%u Byte, Chip-ID=0x%06X\n"),
//                ESP.getFlashChipSize(), ESP.getFlashChipRealSize(), ESP.getFlashChipId());

  // NEU 2.24.0: LittleFS statt SPIFFS. Wichtiger Unterschied zum bisherigen
  // Verhalten: SPIFFS formatierte bei einem leeren/unformatierten Flash
  // NICHT automatisch - der Fallback unten (bei Fehlschlag manuell
  // format() + erneutes begin()) war dafuer noetig. LittleFS formatiert
  // per Default (autoFormat) bereits BEIM ERSTEN begin() automatisch, wenn
  // es keine gueltige LittleFS-Struktur vorfindet - der Fallback unten
  // greift damit im Normalfall gar nicht mehr, bleibt aber als zusaetzliches
  // Sicherheitsnetz bestehen (z.B. falls autoFormat je deaktiviert wird).
  bool littlefs_ok = LittleFS.begin();
  if (!littlefs_ok) {
    Serial.println(F(" LittleFS: Mount fehlgeschlagen, versuche einmalige Formatierung..."));
    if (LittleFS.format()) {
      littlefs_ok = LittleFS.begin();
    }
  }

  // NEU 2.21.0: VendorLookup initialisieren (nach LittleFS.begin())
  VendorLookup::begin();

  load_all_settings();
  load_watchlist();
  // NEU 2.25.0: File Protection - Schutzliste laden
  read_protected_list();
  // NEU 2.17.6: Status-LED-Pin (falls konfiguriert) initialisieren
  led_apply_pin_config();
  // NEU 2.21.0: Signal-Pin (falls konfiguriert) initialisieren
  signal_apply_pin_config();
  if (show_logo) {
    vt_clear_screen();
    print_logo();
    delay(3000);  // NEU 2.20.5 BUG4: 3 Sekunden statt länger
  }
  // NEU 2.20.0 FEATURE 3: GPIO 0 Button (Flash-Button) für Auto-Save initialisieren
  pinMode(0, INPUT_PULLUP);  // GPIO 0 ist internal pull-up, LOW = Taste gedrückt
  gpio0_pressed = false;
  gpio0_last_press_time = 0;

  // NTP-Zeitsynchronisation (falls aktiviert) VOR dem Aktivieren des
  // Promiscuous-Sniffings: braucht kurzzeitig eine normale WLAN-
  // Verbindung, das vertraegt sich nicht mit gleichzeitigem Sniffing
  // (ein Funkchip kann nur eins von beidem). So muss das Sniffing dafuer
  // nicht extra pausiert/reaktiviert werden wie bei notif_send_now().
  sync_ntp_time();
  
  // NEU 2.16.0: Auto-Load Datei laden (falls konfiguriert)
  // WICHTIG: autoload_file_not_found wird bei jedem Boot auf false gesetzt
  autoload_file_not_found = false;
  
  if (autoload_filename[0] != '\0') {
    // Prüfe, ob Datei existiert
    char filepath[50];
    snprintf_P(filepath, sizeof(filepath), PSTR("/%s.txt"), autoload_filename);
    Serial.printf_P(PSTR(" [AUTO-LOAD] Prüfe auf Datei: '%s'\r\n"), filepath);
    if (LittleFS.exists(filepath)) {
      // Datei existiert - lade sie
      Serial.printf_P(PSTR(" [AUTO-LOAD] Datei gefunden! Lade '%s'...\r\n"), autoload_filename);
      load_scenario_file(autoload_filename);
      // WICHTIG: NICHT automatisch offline gehen (anders als manuelles Laden)
      // startup_online bleibt unverändert
      Serial.printf_P(PSTR(" [AUTO-LOAD] Datei '%s' erfolgreich geladen.\r\n"), autoload_filename);
    } else {
      // Datei nicht gefunden - Flag setzen für Hauptmenü-Meldung
      autoload_file_not_found = true;
      Serial.printf_P(PSTR(" [AUTO-LOAD] FEHLER: Datei '%s' nicht gefunden!\r\n"), filepath);
    }
  }

  wifi_promiscuous_enable(disable);
  wifi_set_promiscuous_rx_cb(promisc_cb);
  wifi_promiscuous_enable(enable);
  last_check_time = 0;
  next_check_time = last_check_time + CHECK_INTERVAL;

  // menu_state schon HIER auf STATE_MENU setzen (nicht erst in
  // menu_init() nach der Logo-Anzeige): der globale Default war
  // STATE_LIVE, wodurch live_output_active() waehrend der 5 Sekunden
  // Logo-Anzeige bereits "wahr" war und eintreffende Pakete unterhalb
  // des Logos mitgeschrieben wurden. Das Promiscuous-Sniffing selbst
  // (s.o.) laeuft unabhaengig davon schon im Hintergrund weiter.
  menu_state = STATE_MENU;

  if (!startup_online) {
    go_offline();
  }

  vt_clear_screen();
//  if (show_logo) {
//    print_logo();
//   delay(5000);
//  }

  if (!littlefs_ok) {
    vt_clear_screen();
    Serial.println(F("======================================================="));
    Serial.println(F(" ACHTUNG: LittleFS konnte nicht initialisiert werden!"));
    Serial.println(F(" Punkte 5/6 (Speichern/Laden) funktionieren nicht."));
    Serial.println(F("======================================================="));
    delay(2500);
  }

  // NEU 2.28.0: Rueckkehr-Signalisierungs-Zustand permanent initialisieren
  // (nicht erst bei Menue-4-Eintritt) - dadurch feuert das Signal ab sofort
  // unabhaengig davon, an welcher Stelle der Menuestruktur man sich befindet
  // (siehe watchlist_background_check(), aufgerufen aus menu_periodic()).
  watchlistPulse_begin();

  menu_init();
}

void loop() {
  channel = 1;
  
  // NEU 2.13.0: Wenn Channel-Filter aktiv, finde ersten erlaubten Kanal
  if (strcmp(channel_filter, "alle") != 0) {
    while (channel < 15 && !is_channel_allowed(channel)) {
      channel++;
    }
  }
  
  if (channel < 15 && menu_state != STATE_HTTP_SERVER) {
    wifi_set_channel(channel);
  }
  
  uint32_t channel_change_time = millis();  // Zeit des letzten Kanal-Wechsels
  
  while (true) {
    nothing_new++;
    
    // NEU 2.13.0: Kanal-Wechsel-Logik mit Filter und Verweilzeit
    bool should_hop = false;
    
    // Klassischer Trigger: keine neuen Pakete seit lange (nothing_new > 200)
    if (nothing_new > 200) {
      should_hop = true;
    }
    
    // NEU: Zeit-Trigger - Verweilzeit abgelaufen
    if ((uint32_t)(millis() - channel_change_time) >= channel_dwell_ms) {
      should_hop = true;
    }
    
    if (should_hop) {
      ram_debug_sample(RDP_WIFI_SCAN);  // NEU 2.30.34: passive RAM-/Stack-Diagnose (Kanalwechsel)
      nothing_new = 0;
      channel_change_time = millis();

      // BUGFIX 2.30.2: Waehrend Punkt 7 (HTTP-Datei-Server) aktiv ist, darf
      // der Kanal NICHT gewechselt werden - die STA-WLAN-Verbindung des
      // Servers haengt fest an einem einzigen Kanal (dem des Routers). Das
      // bisherige, vom Menuestatus unabhaengige Durchspringen aller Kanaele
      // hat genau diese Verbindung laufend unterbrochen (Ursache der vom
      // Nutzer beobachteten hohen Paketverlustrate/Nichterreichbarkeit).
      // Waehrend der Server laeuft, wird dieser Block deshalb komplett
      // uebersprungen - kein Kanalwechsel, kein "break" - das Sniffing ist
      // ohnehin per wifi_promiscuous_enable(disable) pausiert (siehe
      // menu_enter_http_server()), es gibt also nichts zu scannen.
      if (menu_state != STATE_HTTP_SERVER) {

      // Nächsten erlaubten Kanal finden
      int next_channel = channel + 1;
      if (next_channel >= 15) {
        break;  // Alle Kanäle fertig (oder alle erlaubten Kanäle)
      }
      
      // Überspringe Kanäle, die nicht im Filter liegen
      while (next_channel < 15 && strcmp(channel_filter, "alle") != 0 && !is_channel_allowed(next_channel)) {
        next_channel++;
      }
      
      if (next_channel >= 15) {
        break;  // Keine weiteren Kanäle im Filter
      }
      
      channel = next_channel;
      wifi_set_channel(channel);
      }  // Ende BUGFIX 2.30.2: menu_state != STATE_HTTP_SERVER
    }
    delay(1);  // kritisch fuer NONOS SDK! Kein delay(0)/yield()
    ram_debug_sample(RDP_LOOP);  // NEU 2.30.34: passive RAM-/Stack-Diagnose (Hauptloop)

    // Menue- und Eingabeverarbeitung (nicht blockierend).
    // Die Hintergrund-Aufzeichnung (promisc_cb) laeuft unabhaengig
    // davon in JEDEM Menue-Zustand unveraendert weiter.
    menu_handle_serial();
    menu_periodic();
    // NEU 2.17.6: Status-LED aktualisieren (nicht blockierend)
    led_update();
    // NEU 2.21.0: Signal-Pin aktualisieren
    signal_update();

    // NEU 2.20.0 FEATURE 3: GPIO 0 Button (Flash-Button) Auto-Save Check
    // Nur wenn Menü aktiv ist (nicht im Sniffing-Betrieb = STATE_LIVE)
    if (menu_state != STATE_MENU && menu_state != STATE_LIVE) {
      bool gpio0_now = digitalRead(0) == LOW;  // LOW = Taste gedrückt (internal pull-up)
      uint32_t now_ms = millis();
      
      if (gpio0_now && !gpio0_pressed && (now_ms - gpio0_last_press_time) > 500) {
        // Button gerade gedrückt (Debouncing: mind. 500ms seit letztem Press)
        gpio0_pressed = true;
        gpio0_last_press_time = now_ms;
        
        // Speichern triggern mit speziellem Dateiname: (Clients)_(APs)_(timestamp).txt
        if (clients_known_count > 0 || aps_known_live_count() > 0) {
          char gpio0_filename[50];
          if (ntp_synced) {
            time_t now = current_unix_time_with_tz();
            struct tm* timeinfo = localtime(&now);
            // NEU 2.20.10 BUG7: Format YY-MM-DD (nicht MM-DD-YY)
            snprintf_P(gpio0_filename, sizeof(gpio0_filename),
                     PSTR("Bttn_%d-%d_%02d%02d%02d_%02d%02d%02d"),
                     clients_known_count, aps_known_live_count(),
                     timeinfo->tm_year % 100, timeinfo->tm_mon + 1, timeinfo->tm_mday,
                     timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
          } else {
            // NEU 2.30.65: "offline_"+millis() -> "NoNtp_"+ddhhmmss
            char uptime[9];
            format_uptime_ddhhmmss(uptime, sizeof(uptime));
            snprintf_P(gpio0_filename, sizeof(gpio0_filename),
                     PSTR("Bttn_%d-%d_NoNtp_%s"),
                     clients_known_count, aps_known_live_count(),
                     uptime);
          }
          led_force_off();  // NEU 2.17.6: zeitkritisch - Status-LED aus
          Serial.printf_P(PSTR("\r\n [GPIO0] Auto-Save speichern als '%s.txt' ...\r\n"), gpio0_filename);
          int result = save_current_lists(gpio0_filename);
          if (result > 0) {
            Serial.printf_P(PSTR(" [GPIO0] erfolgreich: %d Eintraege gespeichert.\r\n"), result);
          } else {
            Serial.println(F(" [GPIO0] FEHLER beim Speichern!"));
          }
        } else {
          Serial.println(F("\r\n [GPIO0] Keine Geräte/APs aufgezeichnet - nicht gespeichert."));
        }
      } else if (!gpio0_now) {
        // Button losgelassen
        gpio0_pressed = false;
      }
    }

    // Benachrichtigung (ntfy.sh): laeuft unabhaengig vom aktuell
    // angezeigten Menue, damit auch im Hintergrund/autonomen Betrieb
    // regelmaessig gesendet wird.
    if (notif_send_pending) {
      notif_send_pending = false;
      notif_send_now();
    } else if (notif_enabled) {
      uint32_t now_min = millis() / 60000;
      if (now_min - last_notif_send_min >= (uint32_t)notif_interval_min) {
        notif_send_now();
        last_notif_send_min = now_min;
      }
    }

    // NEU 2.12.0: Auto-Save Funktionalitaet
    // Speichert taeglich um 00:00 Uhr (mit NTP) oder alle 24h (ohne NTP)
    // WICHTIG: Fehlerbehandlung verhindert Endlosschleifen!
    if (auto_save_enabled && (clients_known_count > 0 || aps_known_live_count() > 0)) {
      if (ntp_synced) {
        // Mit NTP: Pruefe auf Mitternacht (exakt 00:00:xx Uhr)
        time_t tz_now = current_unix_time_with_tz();
        struct tm* timeinfo = localtime(&tz_now);
        // NEU 2.20.2 BUG2: Speichern nur EINMAL pro Tag um 0:00 Uhr
        if (timeinfo->tm_hour == 0 && timeinfo->tm_min == 0 && timeinfo->tm_sec < 2) {
          // Berechne Tages-Timestamp (um 0:00 Uhr heute)
          uint32_t today_at_midnight = tz_now - (timeinfo->tm_sec);
          
          // Speichern nur wenn an DIESEM Tagesanfang noch nicht gespeichert
          if (auto_save_last_run_day < today_at_midnight) {
            perform_auto_save_with_timestamp();
            auto_save_last_run_day = today_at_midnight;
            Serial.println(F(" [Auto-Save] Daily save completed at 00:00"));
          }
        }
      } else {
        // Ohne NTP: Alle 24 Stunden (86400000 ms)
        if (millis() - auto_save_last_run_millis >= 86400000UL && millis() >= auto_save_suppressed_until) {
          // Dateizahl VORHER merken
          int files_before = 0;
          {
            Dir dir_count = LittleFS.openDir("/");
            while (dir_count.next()) files_before++;
          }
          
          // Speichern
          perform_auto_save_without_timestamp();
          
          // Dateizahl NACHHER prüfen
          int files_after = 0;
          {
            Dir dir_count = LittleFS.openDir("/");
            while (dir_count.next()) files_after++;
          }
          
          // Wenn neue Datei erstellt wurde: 60s sperren
          if (files_after > files_before) {
            auto_save_suppressed_until = millis() + 60000UL;  // 60 Sekunden Speichern unterdrücken
          }
          
          auto_save_last_run_millis = millis();
        }
      }
    }

#ifdef PERIODIC
    uint32_t now = millis()/1000;
    if (now >= next_check_time) {
      if (live_output_active()) {
        Serial.println(F("Periodic "));
      }

      for (int u = 0; u < clients_known_count; u++) {
        if ( !clients_known[u].reported && clients_known[u].last_heard >= last_check_time ) {
          if (live_output_active()) { Serial.print(F("New ")); print_client(clients_known[u]); }
          clients_known[u].reported=1;
        } else if ( clients_known[u].reported && now > MAX_CLIENT_AGE &&
                    clients_known[u].last_heard <= (last_check_time - MAX_CLIENT_AGE) ) {
          if (live_output_active()) { Serial.print(F("Old ")); print_client(clients_known[u]); }
          clients_known[u].reported=0;
        };
      };
      for (int u = 0; u < aps_known_count; u++) {
        if (ap_slot_free(u)) continue;  // NEU 2.29.10: sonst faelschlich "New" durch Sentinel-Wert
        if ( !aps_known[u].reported && aps_known[u].err == 0
             && aps_known[u].last_heard >= last_check_time ) {
          if (live_output_active()) { Serial.print(F("New ")); print_beacon(aps_known[u]); }
          aps_known[u].reported=1;
        } else if ( aps_known[u].reported && aps_known[u].err == 0 && now > MAX_CLIENT_AGE &&
                    aps_known[u].last_heard <= (last_check_time - MAX_CLIENT_AGE) ) {
          if (live_output_active()) { Serial.print(F("Old ")); print_beacon(aps_known[u]); }
          aps_known[u].reported=0;
        };
      };

      // Probes: kein "New/Old"-Tracking mehr, da nicht mehr gespeichert (Schritt 1)

      last_check_time = now;
      next_check_time = now + CHECK_INTERVAL;
    };
#endif
  }
}


// =====================================================================
// Ehemals functions.ino - Funktionsdefinitionen
// =====================================================================

// Muss vor der ersten Verwendung (print_client/print_beacon/print_probe)
// stehen, da Makros anders als Funktionen nicht automatisch vorwaerts-
// deklariert werden.
#define STALE_AGE_SEC 600             // ab dieser "last seen"-Zeit wird ausgegraut
#define AP_CELL_WIDTH 46
#define AP_CELL_SSID_WIDTH 16  // verkuerzte SSID-Breite fuer die zweispaltige Ansicht
bool color_enabled = true;            // Einstellungen: VT100+ (Farben) vs. reines VT100 (nur Text)
bool startup_online = true;           // in welchem Modus beim naechsten Boot gestartet wird
bool show_logo = true;                // Hidden-Einstellung: Boot-Logo anzeigen ja/nein



// Setzt SGR-Codes (z.B. "32" fuer gruen, "2" fuer gedimmt). Wird komplett
// uebersprungen, wenn Farben in den Einstellungen deaktiviert sind.
void vt_sgr(const char* codes)
{
  if (!color_enabled) return;
  Serial.write(27);
  Serial.printf_P(PSTR("[%sm"), codes);
}

void vt_color_reset()
{
  if (!color_enabled) return;
  Serial.write(27);
  Serial.print(F("[0m"));
}

// ===================== MAC-Watchlist =====================
// Frei einsehbare/ueberwachbare MAC-Adressen mit Beschreibung (Punkt 4).
// Muss vor print_beacon()/print_client()/print_probe() stehen, da diese
// print_mac() fuer die Faerbung verwenden.
#define MAX_WATCHLIST 32
struct watchentry {
  uint8_t mac[ETH_MAC_LEN];
  char desc[33];
};
watchentry watchlist[MAX_WATCHLIST];
uint8_t watchlist_count = 0;  // NEU 2.17.9: RAM-Optimierung
// NEU 2.30.67: TimeWatch-Marker in der Watchlist.
bool watchlist_entry_is_timewatched(int idx)
{
  if (idx < 0 || idx >= watchlist_count) return false;
  return strstr(watchlist[idx].desc, TIMEWATCH_MARKER) != NULL;
}


bool is_watched_mac(uint8_t* mac)
{
  for (int i = 0; i < watchlist_count; i++) {
    if (! memcmp(watchlist[i].mac, mac, ETH_MAC_LEN)) return true;
  }
  return false;
}

// NEU 2.26.x: Bit 0x02 im ersten Oktett = "locally administered address" -
// Standard-Kennzeichen fuer randomisierte/nicht-herstellervergebene MAC-
// Adressen (z.B. iOS/Android Privacy-Scan-MACs). Reine Bit-Pruefung, kein
// Zustand, kein RAM-Verbrauch.
bool is_randomized_mac(uint8_t* mac)
{
  return (mac[0] & 0x02) != 0;
}

// Druckt eine MAC-Adresse als 12 Hex-Zeichen. Steht sie auf der Watchlist,
// wird NUR die MAC-Adresse blau eingefaerbt (Code "34") - unabhaengig
// davon, in welcher Farbe die restliche Zeile gerade dargestellt wird
// (z.B. grau bei "stale" oder gruen/rot bei RSSI-Trend). Danach wird per
// restore_sgr wieder auf die Zeilenfarbe zurueckgeschaltet (NULL = die
// Zeile hatte keine eigene Farbe, also normaler Reset).
// NEU 2.26.x: Ist die MAC zusaetzlich als randomisiert erkannt, werden die
// ERSTEN 3 Byte (6 Hex-Zeichen) IMMER gelb (Code "33") dargestellt - das hat
// Vorrang vor "watched"/Blau und vor jeder Zeilenfarbe. Die hinteren 3 Byte
// folgen weiterhin der normalen Regel (blau falls watched, sonst wieder
// restore_sgr/Ambient-Farbe der Zeile).
// NEU 2.30.32: Formatiert einen uint64_t als Dezimalstring, ohne printf-%llu
// zu benoetigen (auf manchen ESP8266-Core-Versionen unzuverlaessig) und ohne
// zwischenzeitlich in eine 32-Bit-Variable zu casten.
void format_uint64_dec(uint64_t value, char* buf, size_t buflen)
{
  if (buflen == 0) return;
  char tmp[21];  // max. 20 Ziffern (uint64_t) + Reserve
  int i = 0;
  if (value == 0) {
    tmp[i++] = '0';
  } else {
    while (value > 0 && i < (int) sizeof(tmp)) {
      tmp[i++] = '0' + (char)(value % 10ULL);
      value /= 10ULL;
    }
  }
  size_t j = 0;
  while (i > 0 && j < buflen - 1) {
    buf[j++] = tmp[--i];
  }
  buf[j] = '\0';
}

void print_mac(uint8_t* mac, const char* restore_sgr, Print* out)
{
  // NEU 2.28.0: out erlaubt Wiederverwendung fuer die ntfy-Datei (LittleFS
  // File ist ebenfalls ein Print-Ziel). vt_sgr()/vt_color_reset() schreiben
  // fest auf Serial - Farbcodes werden deshalb nur gesetzt, wenn tatsaechlich
  // die Konsole das Ziel ist. Eine Textdatei/Notification soll keine rohen
  // ANSI-Escape-Sequenzen enthalten; die reinen Hex-Ziffern der MAC sind
  // dadurch trotzdem identisch zur Konsolenausgabe.
  bool to_console = (out == &Serial);
  bool watched = is_watched_mac(mac);
  bool randomized = is_randomized_mac(mac);

  if (to_console) {
    if (randomized) vt_sgr("33");       // Gelb erzwingen, hat Vorrang vor Blau
    else if (watched) vt_sgr("34");
  }
  for (int i = 0; i < 3; i++) out->printf_P(PSTR("%02x"), mac[i]);

  if (to_console && randomized) {
    // Zurueck zur "eigentlichen" Farbe der hinteren 3 Byte
    if (watched) vt_sgr("34");
    else if (restore_sgr && restore_sgr[0]) vt_sgr(restore_sgr);
    else vt_color_reset();
  }
  for (int i = 3; i < 6; i++) out->printf_P(PSTR("%02x"), mac[i]);

  if (to_console && watched) {
    if (restore_sgr && restore_sgr[0]) vt_sgr(restore_sgr);
    else vt_color_reset();
  }
}

// Zeigt eine rote Warnzeile, solange sich das System im Offline-Modus
// befindet (Einstellungen oder automatisch beim Laden einer Datei via
// Punkt 6 gesetzt). Erscheint dadurch automatisch auf jedem Bildschirm.
// Eingebautes Boot-Logo (Fallback, falls keine /logo.txt im Dateisystem
// liegt). Vorbereitet fuer kuenftigen Datei-Upload z.B. per Y-Modem.
const char BUILTIN_LOGO[] = 
    "\r\n"
    "\r\n"
    "\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x95\x97 \xE2\x96\x88\xE2\x96\x88\xE2\x95\x91 \xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x95\x97  \xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x95\x97 \xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x95\x97 \xE2\x96\x88\xE2\x96\x88\xE2\x95\x91    \xE2\x96\x88\xE2\x96\x88\xE2\x95\x91   \xE2\x96\x88\xE2\x96\x88\xE2\x95\x97\r\n"
    "\xE2\x96\x88\xE2\x96\x88\xE2\x95\x94\xE2\x95\x90\xE2\x95\x90\xE2\x95\x90\xE2\x95\x9D \xE2\x96\x88\xE2\x96\x88\xE2\x95\x91 \xE2\x96\x88\xE2\x96\x88\xE2\x95\x94\xE2\x95\x90\xE2\x96\x88\xE2\x96\x88\xE2\x95\x97 \xE2\x96\x88\xE2\x96\x88\xE2\x95\x94\xE2\x95\x90\xE2\x95\x90\xE2\x95\x90\xE2\x95\x9D \xE2\x96\x88\xE2\x96\x88\xE2\x95\x94\xE2\x95\x90\xE2\x95\x90\xE2\x95\x90\xE2\x95\x9D \xE2\x96\x88\xE2\x96\x88\xE2\x95\x91    \xE2\x95\x9A\xE2\x96\x88\xE2\x96\x88\xE2\x95\x97 \xE2\x96\x88\xE2\x96\x88\xE2\x95\x94\xE2\x95\x9D\r\n"
    "\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x95\x97  \xE2\x96\x88\xE2\x96\x88\xE2\x95\x91 \xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x95\x94\xE2\x95\x9D \xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x95\x97  \xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x95\x97  \xE2\x96\x88\xE2\x96\x88\xE2\x95\x91     \xE2\x95\x9A\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x95\x94\xE2\x95\x9D \r\n"
    "\xE2\x96\x88\xE2\x96\x88\xE2\x95\x94\xE2\x95\x90\xE2\x95\x90\xE2\x95\x9D  \xE2\x96\x88\xE2\x96\x88\xE2\x95\x91 \xE2\x96\x88\xE2\x96\x88\xE2\x95\x94\xE2\x95\x90\xE2\x96\x88\xE2\x96\x88\xE2\x95\x97 \xE2\x96\x88\xE2\x96\x88\xE2\x95\x94\xE2\x95\x90\xE2\x95\x90\xE2\x95\x9D  \xE2\x96\x88\xE2\x96\x88\xE2\x95\x94\xE2\x95\x90\xE2\x95\x90\xE2\x95\x9D  \xE2\x96\x88\xE2\x96\x88\xE2\x95\x91      \xE2\x95\x9A\xE2\x96\x88\xE2\x96\x88\xE2\x95\x94\xE2\x95\x9D  \r\n"
    "\xE2\x96\x88\xE2\x96\x88\xE2\x95\x91     \xE2\x96\x88\xE2\x96\x88\xE2\x95\x91 \xE2\x96\x88\xE2\x96\x88\xE2\x95\x91 \xE2\x96\x88\xE2\x96\x88\xE2\x95\x91 \xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x95\x97 \xE2\x96\x88\xE2\x96\x88\xE2\x95\x91     \xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x96\x88\xE2\x95\x97   \xE2\x96\x88\xE2\x96\x88\xE2\x95\x91   \r\n"
    "\xE2\x95\x9A\xE2\x95\x90\xE2\x95\x9D     \xE2\x95\x9A\xE2\x95\x90\xE2\x95\x9D \xE2\x95\x9A\xE2\x95\x90\xE2\x95\x9D \xE2\x95\x9A\xE2\x95\x90\xE2\x95\x9D \xE2\x95\x9A\xE2\x95\x90\xE2\x95\x90\xE2\x95\x90\xE2\x95\x90\xE2\x95\x90\xE2\x95\x9D \xE2\x95\x9A\xE2\x95\x90\xE2\x95\x9D     \xE2\x95\x9A\xE2\x95\x90\xE2\x95\x90\xE2\x95\x90\xE2\x95\x90\xE2\x95\x90\xE2\x95\x9D   \xE2\x95\x9A\xE2\x95\x90\xE2\x95\x9D   \r\n"
    "\r\n"
    "         S O F T W A R E   E N G I N E E R I N G\r\n";

// Zeigt das Logo an - bevorzugt aus /logo.txt (falls vorhanden, z.B.
// kuenftig per Y-Modem hochgeladen), sonst das eingebaute Fallback-Logo.
void print_logo()
{
  if (LittleFS.exists("/logo.txt")) {
    File f = LittleFS.open("/logo.txt", "r");
    if (f) {
      while (f.available()) {
        char c = f.read();
        if (c == '\n') Serial.write('\r');  // \r fehlt sonst -> "Treppenstufen"-Effekt
        Serial.write(c);
      }
      f.close();
      Serial.println();
      return;
    }
  }
  const char* p = BUILTIN_LOGO;
  while (*p) {
    if (*p == '\n') Serial.write('\r');
    Serial.write(*p);
    p++;
  }
  Serial.println();
}

// NEU 2.30.32: Gibt die OFFLINE-Warnung und/oder die Channel-Filter-Warnung
// unmittelbar aus (ohne Leerzeilen, in dieser Reihenfolge). Diese Funktion
// selbst entscheidet nicht ÜBER die Position innerhalb des Bildschirms -
// das übernimmt OfflineBannerGuard (siehe unten), der print_offline_banner_now()
// per RAII erst beim Verlassen der jeweiligen Bildschirmfunktion aufruft,
// sodass beide Meldungen (falls aktiv) immer ganz am Ende der aktuellen
// Ausgabe stehen, unabhängig davon, wie lang die eigentliche Ausgabe ist.
void print_offline_banner_now()
{
  if (!online_mode) {
    vt_sgr("31");
    Serial.println(F(" *** OFFLINE - Live-Aufzeichnung pausiert ***"));
    vt_color_reset();
  }
  if (traffic_stats_active
      && menu_state != STATE_TRAFFIC_STATS
      && menu_state != STATE_TRAFFIC_DETAIL) {
    char durbuf[12];
    format_duration_hms((millis() - traffic_stats_started_ms) / 1000, durbuf, sizeof(durbuf));
    vt_sgr("36");
    Serial.printf_P(PSTR(" *** Hintergrundverkehr laeuft (%s) ***\r\n"), durbuf);
    vt_color_reset();
  }
  // NEU 2.20.6 BUG2: Channel-Warnung IMMER anzeigen wenn Filter aktiv (in jedem Menue!)
  print_channel_filter_warning();
}

// Kompatibilitäts-Wrapper (falls an anderer Stelle noch unter dem alten Namen
// aufgerufen) - ruft ausschließlich print_offline_banner_now() auf.
void print_offline_banner()
{
  print_offline_banner_now();
}

// BUGFIX 2.30.44 (gemeldet vom Anwender): manche Bildschirme enden bewusst
// OHNE Zeilenumbruch auf einem Eingabe-Prompt (z.B. " Auswahl: "), damit die
// Eingabe des Anwenders auf derselben Zeile erscheint. Der OfflineBannerGuard
// feuert aber unveraendert am Ende der Funktion - landet dann direkt hinter
// dem Prompt auf derselben Zeile statt darunter. Diese Hilfsfunktion meldet,
// ob print_offline_banner_now() gleich tatsaechlich etwas ausgeben wird,
// damit genau in diesem Fall (und nur dann) ein Zeilenumbruch nach dem
// Prompt eingefuegt werden kann - im Normalfall (nichts zu melden) bleibt
// die Ausgabe wie gewohnt ohne zusaetzliche Leerzeile.
bool offline_banner_will_print()
{
  return !online_mode || strcmp(channel_filter, "alle") != 0;
}

// NEU 2.20.4 BUG11: Channel-Filter Warnung in Rot wenn aktiv
// NEU 2.30.32: umgebende Leerzeilen entfernt (Meldung steht jetzt direkt
// unterhalb der OFFLINE-Zeile bzw. direkt am Ende der Ausgabe, ohne Abstand).
void print_channel_filter_warning()
{
  if (strcmp(channel_filter, "alle") != 0) {
    vt_sgr("31");  // Rot
    Serial.printf_P(PSTR(" ⚠️ WiFi Scan nur Channel(s) %s ⚠️\r\n"), channel_filter);
    vt_color_reset();
  }
}

// NEU 2.30.32: RAII-Guard für die OFFLINE-/Channel-Warnung. Eine Instanz wird
// zu Beginn einer Bildschirmfunktion angelegt (an der Stelle, an der bisher
// print_offline_banner() direkt aufgerufen wurde); ihr Destruktor feuert beim
// Verlassen des umschließenden Gültigkeitsbereichs - also am Ende der jeweiligen
// Funktion, auch bei vorzeitigem return - und gibt die Warnzeile(n) dann erst
// aus. Dadurch stehen sie garantiert ganz unten, ohne dass jede einzelne
// Bildschirmfunktion einzeln umgebaut werden musste.
struct OfflineBannerGuard {
  ~OfflineBannerGuard() { print_offline_banner_now(); }
};

// Liefert die "aktuelle Zeit" fuer last-seen-Berechnungen: waehrend
// online die echte Laufzeit, waehrend offline den eingefrorenen
// Zeitpunkt vom Wechsel nach Offline (damit "last seen" nicht weiterlaeuft).
uint64_t effective_now()
{
  if (!online_mode) return offline_freeze_time;
  return millis() / 1000;
}

void go_offline()
{
  if (online_mode) {
    online_mode = false;
    offline_freeze_time = millis() / 1000;
  }
}

void go_online()
{
  // NEU 2.17.2 Bugfix: Waehrend Offline war die Anzeige eingefroren
  // (effective_now() lieferte konstant offline_freeze_time), aber
  // last_heard-Zeitstempel sind echte millis()-Werte, deren "Uhr" im
  // Hintergrund weiterlief. Ohne Kompensation wuerde beim Zurueckwechseln
  // die komplette Offline-Dauer auf einen Schlag zu allen Age-Times
  // addiert (falscher Sprung/Ausgrauen). Stattdessen alle last_heard-
  // Zeitstempel um die Offline-Dauer nach vorne verschieben, damit die
  // Age-Time nahtlos beim eingefrorenen Wert weiterlaeuft.
  if (!online_mode) {
    uint64_t now = millis() / 1000;
    uint64_t offline_duration = (now > offline_freeze_time) ? (now - offline_freeze_time) : 0;
    if (offline_duration > 0) {
      for (int i = 0; i < clients_known_count; i++) {
        clients_known[i].last_heard += (uint32_t)offline_duration;
      }
      for (int i = 0; i < aps_known_count; i++) {
        if (ap_slot_free(i)) continue;  // NEU 2.29.10: sonst Ueberlauf von 0xFFFFFFFF, Slot wuerde faelschlich wieder "belegt" aussehen
        aps_known[i].last_heard += (uint32_t)offline_duration;
      }
    }
  }
  online_mode = true;
}

void toggle_online_mode()
{
  if (online_mode) go_offline();
  else go_online();
}

//parse out details of client frame
struct clientinfo parse_data(uint8_t *frame, uint16_t framelen, signed rssi, unsigned channel, uint8_t *bssid_out)
{
  CallChainGuard __cc_guard(RDP_PARSE_DATA, CTX_PROMISC);  // NEU 2.30.37: echte Funktionsgrenze - lag bisher VOR dem CLIENT_CAPTURE-Messpunkt
  // takes 36 byte frame control frame
  struct clientinfo ci;
  ci.channel = channel;
  ci.err = 0;
  ci.rssi = rssi;
  ci.last_heard=millis()/1000;
  ci.reported=0;
  uint8_t *bssid;
  uint8_t *station;
  uint8_t *ap;
  uint8_t ds;
  ds = frame[1] & 3;
  switch (ds) {
    case 0:
      bssid = frame + 16;
      station = frame + 10;
      ap = frame + 4;
      break;
    case 1:
      bssid = frame + 4;
      station = frame + 10;
      ap = frame + 16;
      break;
    case 2:
      bssid = frame + 10;
      // BUGFIX 2.30.19: "||" zwischen drei "stimmt NICHT ueberein"-Pruefungen
      // ist so gut wie immer wahr (eine Adresse kann nicht gleichzeitig mit
      // drei verschiedenen Mustern uebereinstimmen) - der erste Zweig wurde
      // dadurch praktisch IMMER genommen, unabhaengig davon, ob Adresse 1
      // wirklich Broadcast/Multicast war. Muss "&&" heissen (alle drei
      // Muster gleichzeitig NICHT treffen = echte Unicast-Adresse). Nach
      // 802.11-Standard ist bei ds==2 (ToDS=0/FromDS=1, AP->Client) Adresse 1
      // die tatsaechliche Ziel-Client-Adresse (DA) - die Zweige wurden
      // entsprechend getauscht (vorher wurde im ueberwiegend genommenen
      // Zweig faelschlich Adresse 3 als "station" verwendet, was bei
      // typischem NAT-Verkehr meist die Adresse des Routers/APs selbst ist,
      // nicht die des Clients).
      // BUGFIX 2.30.23: Die drei einzeln aufgezaehlten Broadcast/Multicast-
      // Muster (broadcast1={01,00,5e}, broadcast2={ff,ff,ff,ff,ff,ff},
      // broadcast3={33,33,00}) deckten den IEEE-reservierten IPv6-Multicast-
      // Bereich nicht vollstaendig ab: broadcast3 traf NUR auf 33:33:00,
      // nicht aber auf 33:33:FF - genau das Muster von IPv6 "Solicited-Node"-
      // Multicast-Zieladressen (33:33:ff:xx:xx:xx), das bei praktisch jedem
      // Geraet mit aktivem IPv6 (Neighbor Discovery/MLD) regelmaessig auftritt
      // und dessen letzte 3 Byte oft mit der echten Client-MAC uebereinstimmen
      // - dadurch tauchten Phantom-Eintraege wie "3333ff..." als vermeintlich
      // eigenstaendige Clients in allen Listen auf (Nutzer-Meldung 2026-09-07).
      // Seit dem Zweig-Tausch in v2.30.19 wird dieser Pfad ueberhaupt erst
      // regelmaessig durchlaufen, deshalb trat der Fehler erst "seit gestern"
      // sichtbar in Erscheinung. Fix: statt drei fehleranfaelliger Einzelmuster
      // jetzt dasselbe Gruppenadress-Bit-Prinzip wie bei is_valid_ap_bssid()
      // (IEEE 802: LSB des ersten Oktetts gesetzt = Gruppen-/Multicast-/
      // Broadcast-Adresse) - deckt automatisch ALLE Multicast-Muster ab
      // (01:00:5e, ff:ff:ff:ff:ff:ff, 33:33:xx:xx:xx:xx mit JEDEM dritten
      // Byte, sowie jede sonstige, bisher nicht einzeln aufgelistete
      // Multicast-Kennung, z.B. 01:80:c2 STP, 01:00:0c CDP). broadcast1/2/3-
      // Arrays dadurch ueberfluessig geworden und entfernt (RAM-Ersparnis).
      if (! (frame[4] & 0x01)) {
        // Adresse 1 hat das Gruppenbit NICHT gesetzt -> echte Unicast-
        // Zieladresse, das ist der Client.
        station = frame + 4;
        ap = frame + 16;
      } else {
        // Adresse 1 ist eine Gruppenadresse (Broadcast/Multicast) - keine
        // eindeutige Zieladresse; Adresse 3 (urspruengliche Quelle) ist die
        // naechstbeste Zuordnung.
        station = frame + 16;
        ap = frame + 4;
      }
      break;
    case 3:
      bssid = frame + 10;
      station = frame + 4;
      ap = frame + 4;
      break;
  }

  memcpy(ci.station, station, ETH_MAC_LEN);
  // NEU 2.29.15 BUGFIX: bei ds==3 (4-Adress-/WDS-Modus, z.B. Mesh-/Repeater-
  // Backhaul-Verkehr zwischen zwei AP-Radios) gibt es KEIN echtes BSSID-Feld
  // im klassischen Sinn - "bssid" oben ist dort nur die Sender-Adresse (TA)
  // des weiterleitenden Knotens, nicht die BSSID, die der eigentliche AP in
  // seinem Beacon sendet. Das fuehrte zu einem AP-Platzhalter
  // (ensure_ap_index()), der NIE mit einem echten Beacon matchen konnte -
  // dauerhaft "...wartet auf Beacon", egal wie lange gewartet wird. Statt
  // dessen jetzt bewusst eine ungueltige (all-null) BSSID liefern - das
  // faengt is_valid_ap_bssid() beim Aufrufer automatisch ab (AP_IDX_NONE,
  // "??" beim Client statt eines nie aufloesbaren Phantom-Platzhalters).
  if (ds == 3) {
    memset(bssid_out, 0, ETH_MAC_LEN);
  } else {
    memcpy(bssid_out, bssid, ETH_MAC_LEN);
  }
  // NEU 2.29.11: ap_idx wird vom Aufrufer gesetzt (ensure_ap_index()),
  // sobald die BSSID zu einem Index in aps_known[] aufgeloest ist.

  // NEU 2.21.1 OPTIMIZATION: Entfernt (nicht genutzt): ci.ap, ci.header, ci.seq_n
  return ci;
}

struct beaconinfo parse_beacon(uint8_t *frame, uint16_t framelen, signed rssi)
{
  CallChainGuard __cc_guard(RDP_PARSE_BEACON, CTX_PROMISC);  // NEU 2.30.37: echte Funktionsgrenze statt nur Punkt vor register_beacon()
  struct beaconinfo bi;
  bi.ssid_len = 0;
  bi.channel = 0;
  bi.err = 0;
  bi.rssi = rssi;
  bi.last_heard=millis()/1000;
  bi.reported=0;
  // NEU 2.21.1 OPTIMIZATION: Entfernt (nicht genutzt): bi.header
  int pos = 36;
  uint8_t frame_type= (frame[0] & 0x0C)>>2;
  uint8_t frame_subtype= (frame[0] & 0xF0)>>4;
  if (frame[pos] == 0x00) {
    while (pos < framelen) {
      switch (frame[pos]) {
        case 0x00: //SSID
          bi.ssid_len = (int) frame[pos + 1];
          if (bi.ssid_len == 0) {
            memset(bi.ssid, '\x00', 33);
            break;
          }
          if (bi.ssid_len < 0) {
            bi.err = -1;
            break;
          }
          if (bi.ssid_len > 32) {
            bi.err = -2;
            break;
          }
          memset(bi.ssid, '\x00', 33);
          memcpy(bi.ssid, frame + pos + 2, bi.ssid_len);
          bi.err = 0;
          break;
        case 0x03: //Channel
          bi.channel = (int) frame[pos + 2];
          pos = -1;
          break;
        default:
          break;
      }
      if (pos < 0) break;
      pos += (int) frame[pos + 1] + 2;
    }
  } else {
    bi.err = -3;
  }

  // NEU 2.29.8: "Offenes WLAN"-Flag aus dem Capability-Info-Feld lesen
  // (2 Byte, Offset 34/35 im Frame - liegt VOR den Information-Elements,
  // die die obige Schleife ab pos=36 durchlaeuft, ist also unabhaengig
  // davon immer verfuegbar). Bit 4 von frame[34] ist das Privacy-Bit:
  // gesetzt = Verschluesselung aktiv, NICHT gesetzt = offenes WLAN.
  if (!(frame[34] & 0x10)) {
    bi.channel |= AP_OPEN_FLAG;
  }

  // NEU 2.21.1 OPTIMIZATION: Entfernt (nicht genutzt): bi.capa[0], bi.capa[1]
  memcpy(bi.bssid, frame + 10, ETH_MAC_LEN);
  return bi;
};

struct probeinfo parse_probe(uint8_t *frame, uint16_t framelen, signed rssi)
{
  struct probeinfo pi;
  pi.ssid_len = 0;
  pi.channel = 0;
  pi.err = 0;
  pi.rssi = rssi;
  pi.last_heard=millis()/1000;
  pi.reported=0;
  // NEU 2.21.1 OPTIMIZATION: Entfernt (nicht genutzt): pi.header
  int pos = 24;

  if (frame[pos] == 0x00) {
    pi.ssid_len = (int) frame[pos + 1];
    if (pi.ssid_len == 0) {
      memset(pi.ssid, '\x00', 33);
    }
    if (pi.ssid_len < 0) {
      pi.err = -1;
    }
    if (pi.ssid_len > 32) {
      pi.err = -2;
    }
    memset(pi.ssid, '\x00', 33);
    memcpy(pi.ssid, frame + pos + 2, pi.ssid_len);
    pi.err = 0;
  } else {
    pi.err = -3;
  }

  if (pi.err!=0){
    Serial.printf_P(PSTR("Error parsing PROBE %d"),(int)pi.err);
  }
  // NEU 2.21.1 OPTIMIZATION: Entfernt (nicht genutzt): pi.ap
  memcpy(pi.station, frame+10, ETH_MAC_LEN);
  memcpy(pi.bssid, frame+16, ETH_MAC_LEN);
  return pi;
}

// NEU 2.29.1: Wird aus register_beacon()/register_client() aufgerufen, also
// direkt aus dem zeitkritischen WLAN-Sniffer-Callback heraus - deshalb
// bewusst MINIMAL: setzt nur ein Flag, keinerlei delay()/Datei-I/O/Serial-
// Ausgabe. Wenn schon ein Ueberlauf-Ereignis auf Bearbeitung wartet, wird
// ein zweites (evtl. der jeweils anderen Liste) nicht ueberschrieben -
// process_pending_overflow() sichert/leert ohnehin beide Listen zusammen,
// verliert also nichts.
void signal_pending_overflow(uint8_t type)
{
  // NEU 2.29.2 BUGFIX: waehrend einer laufenden Bearbeitung (insbesondere
  // dem ggf. laengeren save_current_lists()-Aufruf) keine neuen Ereignisse
  // mehr annehmen - siehe Kommentar bei overflow_processing_active.
  if (overflow_processing_active) return;
  if (pending_overflow_type == 0) pending_overflow_type = type;
}

// NEU 2.29.1: Gibt auf dem Signalisierungspin das kurze Ereignis-Muster aus
// (20ms an, 100ms aus, 20ms an). Blockierend (140ms) - unproblematisch,
// da NICHT mehr aus dem WLAN-Callback aufgerufen (siehe Kommentar bei
// pending_overflow_type), sondern aus dem Hauptloop.
void signal_overflow_pattern()
{
  if (signal_pin < 0 || !signal_enabled) return;
  signal_write_digital(true);  delay(20);
  signal_write_digital(false); delay(100);
  signal_write_digital(true);  delay(20);
  signal_write_digital(false);
}

// NEU 2.29.9: Eigenes, laengeres Signalmuster fuer den Sonderfall
// "AP-Ueberlauf bei Auto-Save UND Auto-Offline aus, aber kein einziger
// AP mehr mit 0/0 Geraeten vorhanden" - erzwingt Offline-Wechsel trotz
// abgeschalteter Auto-Offline-Einstellung. Bewusst deutlich laenger/
// anders als signal_overflow_pattern(), damit dieser Sonderfall am
// Signalisierungspin von einem normalen Ueberlauf-Ereignis unterscheidbar
// ist (50ms an/100ms aus, dreimal). Blockierend (~440ms) - unproblematisch,
// da wie signal_overflow_pattern() nur aus dem Hauptloop heraus aufgerufen.
void signal_forced_offline_pattern()
{
  if (signal_pin < 0 || !signal_enabled) return;
  signal_write_digital(true);  delay(50);
  signal_write_digital(false); delay(100);
  signal_write_digital(true);  delay(50);
  signal_write_digital(false); delay(100);
  signal_write_digital(true);  delay(50);
  signal_write_digital(false);
}

// NEU 2.29.9: Sucht den ERSTEN Access Point ohne jemals gesehenen Client
// (0/0 in der Geraetezaehlung) - fuer den AP-Ueberlauf-Fallback (Fall 2:
// Auto-Save UND Auto-Offline beide aus). Bricht beim ersten Treffer ab,
// damit nicht fuer jeden AP im Array die Client-Liste durchsucht werden
// muss (vgl. Kostenwarnung im Kommentar zu BUGFIX 2.27.3 bei
// print_beacon_line/dev_count - dieselbe O(APs*Clients)-Falle, hier aber
// durch fruehen Abbruch entschaerft). Gibt den Index in aps_known[]
// zurueck, oder -1 wenn kein AP ohne Geraete existiert.
int find_first_empty_ap()
{
  for (int a = 0; a < aps_known_count; a++) {
    if (ap_slot_free(a)) continue;  // NEU 2.29.10: bereits freie Slots sind kein Kandidat
    bool has_client = false;
    for (int c = 0; c < clients_known_count; c++) {
      if ((c & 0x1F) == 0) yield();  // alle 32 Iterationen, wie bei dev_count
      if (clients_known[c].ap_idx == a) {
        has_client = true;
        break;
      }
    }
    if (!has_client) return a;
  }
  return -1;
}

// NEU 2.29.1: Bearbeitet ein wartendes Ueberlauf-Ereignis - aus
// menu_periodic() heraus aufgerufen (Hauptloop-Kontext, sicher fuer
// delay()/Datei-I/O). "Listenueberlauf" bezieht sich auf BEIDE Kriterien
// (Client- ODER AP-Liste voll) gleichermassen. NEU 2.29.2: Sind BEIDE
// Funktionen (Auto-Save UND Auto-Offline) gleichzeitig aktiviert, hat
// Auto-Offline Vorrang - es wird dann NUR in den Offline-Modus gewechselt,
// Auto-Save greift in diesem Fall nicht (verhindert widerspruechliches
// Verhalten: Liste gleichzeitig leeren und unangetastet lassen ergibt
// keinen Sinn). Bei Auto-Save (ohne Auto-Offline) wird immer die komplette
// Sicherung (Clients+APs) geschrieben und ANSCHLIESSEND BEIDE Listen
// komplett geleert, der Scan laeuft danach mit leeren Listen weiter. NEU
// 2.29.9: Sind BEIDE Funktionen aus, wird bei AP-Ueberlauf nicht mehr der
// aelteste AP entfernt, sondern der erste AP ohne jemals gesehenen Client
// (0/0) - existiert keiner mehr, wird zwangsweise (trotz abgeschalteter
// Einstellung) in den Offline-Modus gewechselt (Liste bleibt erhalten,
// eigenes Signalmuster signal_forced_offline_pattern() statt des
// normalen Ueberlauf-Signals).
void process_pending_overflow()
{
  if (pending_overflow_type == 0) return;
  uint8_t overflow_type = pending_overflow_type;  // sichern, bevor das Flag zurueckgesetzt wird
  const char* which = (overflow_type == 1) ? "Access-Point" : "Client";
  pending_overflow_type = 0;  // sofort zuruecksetzen, bevor die Bearbeitung beginnt
  // NEU 2.29.2 BUGFIX: ab hier werden neu eintreffende Ueberlauf-Signale
  // unterdrueckt (siehe Kommentar bei overflow_processing_active), bis
  // diese Bearbeitung komplett abgeschlossen ist - verhindert eine zweite,
  // ungewollte Verarbeitungsrunde waehrend save_current_lists() noch laeuft.
  overflow_processing_active = true;

  Serial.printf_P(PSTR("\r\n Warnung: %s-Liste ist voll!\r\n"), which);
  Serial.write(7); delay(150);
  Serial.write(7); delay(150);
  Serial.write(7);
  Serial.println();

  if (auto_offline_on_overflow) {
    // NEU 2.29.2: hat Vorrang vor Auto-Save, falls beide aktiviert sind.
    go_offline();
    Serial.println(F(" Automatisch offline geschaltet - Aufzeichnung angehalten, Liste bleibt erhalten."));
  } else if (auto_save_on_overflow) {
    // NEU 2.29.2: neues Dateinamensformat - Client_overflow/AP_overflow,
    // danach wie bei anderen Funktionen der NTP-Zeitstempel, falls
    // verfuegbar, sonst die aktuelle millis().
    char fname[48];
    // NEU 2.29.3 BUGFIX: "AP_overflow"/"Client_overflow" waren zu lang -
    // LittleFS auf dem ESP8266 erlaubt nur 32 Byte fuer den kompletten Pfad
    // (inkl. "/", ".txt" und Null-Terminator), das liess nur 26 Zeichen fuer
    // den Basisnamen. Im Offline-Fall (Praefix + "_offline_" + millis(), bis
    // zu 10 Stellen) reichte das nicht - LittleFS.open() schlug fehl
    // ("Datei konnte nicht angelegt werden"). Kurze Praefixe wie beim
    // bisherigen "autosave_"/"Bttn_"-Format halten das Limit sicher ein.
    const char* base = (overflow_type == 1) ? "AP_ovfl" : "Cl_ovfl";
    if (ntp_synced) {
      time_t now_t = current_unix_time_with_tz();
      struct tm* timeinfo = localtime(&now_t);
      snprintf_P(fname, sizeof(fname), PSTR("%s_%02d%02d%02d_%02d%02d%02d"),
               base,
               timeinfo->tm_year % 100, timeinfo->tm_mon + 1, timeinfo->tm_mday,
               timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    } else {
      // NEU 2.30.65: "_offline_"+millis() -> "_NoNtp_"+ddhhmmss (feste Laenge)
      char uptime[9];
      format_uptime_ddhhmmss(uptime, sizeof(uptime));
      snprintf_P(fname, sizeof(fname), PSTR("%s_NoNtp_%s"), base, uptime);
    }
    save_current_lists(fname);
    Serial.printf_P(PSTR(" Automatisch gesichert unter: %s.txt\r\n"), fname);
    // NEU 2.29.1: komplette Arbeitsliste leeren (beide Listen), Scan laeuft
    // mit leeren Listen weiter - statt wie bisher nur den aeltesten
    // Eintrag der ueberlaufenen Liste zu entfernen.
    clients_known_count = 0;
    aps_known_count = 0;
    roaming_pair_count = 0;  // BUGFIX 2.30.61: sonst zeigen alte Paare auf die neuen APs
    Serial.println(F(" Arbeitsliste geleert - Scan laeuft weiter."));
  } else {
    // Weder Auto-Save noch Auto-Offline aktiv (Fall 2).
    // NEU 2.29.9: Bei Client-Ueberlauf weiterhin wie bisher der aelteste
    // Eintrag. Bei AP-Ueberlauf NICHT mehr der aelteste AP, sondern der
    // erste AP ohne jemals gesehenen Client (0/0) - nur EIN Eintrag pro
    // Ereignis, genug um Platz zu schaffen. Existiert kein 0/0-Kandidat
    // mehr, wird zwangsweise in den Offline-Modus gewechselt (Liste
    // bleibt vollstaendig erhalten) und ueber ein eigenes, laengeres
    // Signalmuster signalisiert, damit dieser Sonderfall vom normalen
    // Ueberlauf-Ereignis unterscheidbar ist.
    bool forced_offline = false;
    if (overflow_type == 1 && aps_known_count > 0) {
      int empty_idx = find_first_empty_ap();
      if (empty_idx >= 0) {
        // NEU 2.29.10: nur noch markieren statt verschieben - register_beacon()
        // findet und nutzt diesen freien Slot beim naechsten neuen AP wieder.
        ap_slot_mark_free(empty_idx);
        Serial.println(F(" Access Point ohne Geraete (0/0) entfernt - Scan laeuft weiter."));
      } else {
        forced_offline = true;
        go_offline();
        Serial.println(F(" Kein Access Point ohne Geraete (0/0) mehr vorhanden - zwangsweise offline geschaltet, Liste bleibt erhalten."));
      }
    } else if (overflow_type == 2 && clients_known_count > 0) {
      int oldest_idx = 0;
      uint32_t oldest_heard = clients_known[0].last_heard;
      for (int u = 1; u < clients_known_count; u++) {
        if (clients_known[u].last_heard < oldest_heard) { oldest_heard = clients_known[u].last_heard; oldest_idx = u; }
      }
      for (int u = oldest_idx; u < clients_known_count - 1; u++) clients_known[u] = clients_known[u + 1];
      clients_known_count--;
      Serial.println(F(" Aeltester Client entfernt - Scan laeuft weiter."));
    }

    if (forced_offline) {
      // NEU 2.29.9: eigenes Signalmuster statt des normalen Ueberlauf-
      // Signals, siehe signal_forced_offline_pattern().
      signal_forced_offline_pattern();
      overflow_processing_active = false;
      return;
    }
  }

  // NEU 2.29.1: Ereignis-Signalmuster (20ms an, 100ms aus, 20ms an) - in
  // beiden Faellen (Auto-Save UND Auto-Offline), sowie beim regulaeren
  // Ueberlauf-Fallback (aeltester Client / erster 0/0-AP). NEU 2.29.9:
  // beim erzwungenen Offline-Wechsel (kein 0/0-AP mehr vorhanden) wird
  // stattdessen weiter oben bereits signal_forced_offline_pattern()
  // ausgegeben und die Funktion vorzeitig verlassen.
  signal_overflow_pattern();

  // NEU 2.29.2 BUGFIX: erst jetzt, nach Abschluss der kompletten
  // Bearbeitung, wieder neue Ueberlauf-Ereignisse zulassen.
  overflow_processing_active = false;
}

int register_beacon(beaconinfo beacon)
{
  CallChainGuard __cc_guard(RDP_REGISTER_BEACON, CTX_PROMISC);  // NEU 2.30.37: echte Funktionsgrenze
  int known = 0;
  int free_idx = -1;  // NEU 2.29.10: erster freier Slot, falls dieser AP neu ist
  for (int u = 0; u < aps_known_count; u++)
  {
    if (ap_slot_free(u)) {
      if (free_idx < 0) free_idx = u;
      continue;  // NEU 2.29.10: freie Slots nie vergleichen (stale bssid, siehe Kommentar bei ap_slot_free)
    }
    if (! memcmp(aps_known[u].bssid, beacon.bssid, ETH_MAC_LEN)) {
      known = 1;
      aps_known[u].last_heard = beacon.last_heard;
      aps_known[u].rssi = beacon.rssi;        // Bugfix: RSSI wurde bisher nie aktualisiert
      aps_known[u].channel = beacon.channel;
      break;
    }
  }
  __cc_guard.probe();  // NEU 2.30.37: Zwischen-Messung nach der Suchschleife (Vorgabe Pkt.8/9)
  if (! known)
  {
    if (free_idx >= 0) {
      // NEU 2.29.10: freien Slot (durch Loeschung entstanden) wiederverwenden
      // statt immer ans Ende anzuhaengen.
      memcpy(&aps_known[free_idx], &beacon, sizeof(beacon));
    } else if ((unsigned int) aps_known_count >=
        sizeof (aps_known) / sizeof (aps_known[0]) ) {
      // NEU 2.29.1 BUGFIX: keine Behandlung mehr direkt hier (dieser
      // Callback muss schnell zurueckkehren, siehe Kommentar bei
      // pending_overflow_type) - nur noch Flag setzen und den neuen
      // Eintrag verwerfen. Die eigentliche Behandlung (Eviction oder
      // Auto-Save/Auto-Offline) uebernimmt process_pending_overflow() im
      // naechsten Hauptloop-Durchlauf (typischerweise innerhalb weniger ms).
      signal_pending_overflow(1);
      return known;
    } else {
      memcpy(&aps_known[aps_known_count], &beacon, sizeof(beacon));
      aps_known_count++;
    }
  }
  return known;
}

int register_client(clientinfo ci, int *out_client_index)
{
  CallChainGuard __cc_guard(RDP_REGISTER_CLIENT, CTX_PROMISC);
  if (out_client_index != NULL) *out_client_index = -1;  // NEU 2.30.37: echte Funktionsgrenze
  int known = 0;
  int placeholder_idx = -1;  // BUGFIX 2.30.44: siehe Kommentar unten
  for (int u = 0; u < clients_known_count; u++)
  {
    if (! memcmp(clients_known[u].station, ci.station, ETH_MAC_LEN)) {
      if (clients_known[u].ap_idx == ci.ap_idx) {
        known = 1;
        clients_known[u].last_heard = ci.last_heard;
        clients_known[u].rssi = ci.rssi;
        clients_known[u].channel = ci.channel;
        if (out_client_index != NULL) *out_client_index = u;
        break;
      }
      // NEU 2.30.60: gleiche MAC, anderer ap_idx -> Roaming zwischen zwei
      // APs. roaming_record() filtert AP_IDX_NONE und freie Slots selbst.
      roaming_record(clients_known[u].ap_idx, ci.ap_idx);
      // BUGFIX 2.30.44 (Anwenderfehlerbericht: MAC-Nachschlagefunktion
      // zeigte "Angemeldet an: unbekannt", obwohl derselbe Client in der
      // Geraeteuebersicht seiner SSID korrekt gelistet war): wird ein Client
      // zuerst gesehen, BEVOR sein AP registriert ist, bekommt er ap_idx =
      // AP_IDX_NONE. Wird derselbe Client spaeter mit bekanntem ap_idx
      // erneut gesehen, griff die obige Pruefung ("gleiche MAC UND gleicher
      // ap_idx") nicht mehr, weil sich ap_idx geaendert hat - es entstand
      // ein ZWEITER, dauerhafter Eintrag mit dem korrekten ap_idx, waehrend
      // der alte Eintrag mit AP_IDX_NONE fuer immer bestehen blieb. Da
      // lookup_mac() (Punkt 2.3) den Client-Array linear nach der ERSTEN
      // passenden MAC durchsucht, fand es meist den aelteren "unbekannt"-
      // Eintrag, waehrend die Geraeteuebersicht einer SSID (die gezielt nach
      // ap_idx filtert) den neueren, korrekten Eintrag zeigte. Deshalb hier
      // vormerken: ein Eintrag derselben MAC mit noch AP_IDX_NONE, um ihn
      // unten zu AKTUALISIEREN statt einen zweiten anzulegen.
      if (clients_known[u].ap_idx == AP_IDX_NONE && placeholder_idx < 0) {
        placeholder_idx = u;
      }
    }
  }
  __cc_guard.probe();  // NEU 2.30.37: Zwischen-Messung nach der Suchschleife (bis zu 1000 Clients, Vorgabe Pkt.8/9)
  if (! known)
  {
    if (placeholder_idx >= 0 && ci.ap_idx != AP_IDX_NONE) {
      // BUGFIX 2.30.44: AP war beim ersten Sehen dieses Clients noch nicht
      // bekannt und ist es jetzt - bestehenden Eintrag nachtraeglich mit dem
      // jetzt bekannten AP verknuepfen, statt einen zweiten (weiterhin auf
      // "unbekannt" stehenden) Eintrag anzulegen.
      clients_known[placeholder_idx].ap_idx = ci.ap_idx;
      clients_known[placeholder_idx].last_heard = ci.last_heard;
      clients_known[placeholder_idx].rssi = ci.rssi;
      clients_known[placeholder_idx].channel = ci.channel;
      if (out_client_index != NULL) *out_client_index = placeholder_idx;
      return 1;
    }
    if ((unsigned int) clients_known_count >=
        sizeof (clients_known) / sizeof (clients_known[0]) ) {
      // NEU 2.29.1 BUGFIX: siehe register_beacon() - nur Flag setzen,
      // Eintrag verwerfen, Behandlung erfolgt sicher im Hauptloop.
      signal_pending_overflow(2);
      return known;
    }
    memcpy(&clients_known[clients_known_count], &ci, sizeof(ci));
    if (out_client_index != NULL) *out_client_index = clients_known_count;
    clients_known_count++;
  }
  return known;
}

// register_probe() entfaellt (Schritt 1) - Probes werden nicht mehr
// gespeichert, promisc_cb() ruft fuer Probes jetzt direkt print_probe() auf.

// NEU 2.30.58: Binaersuche jetzt ueber memcmp auf die MAC-Adresse (statt
// clients_known[]-Index) im kompakten, nach MAC sortierten Statistikblock.
// Der Last-Hit-Cache spart bei Bursts einer einzelnen MAC die Binaersuche.
int traffic_stats_find_client(const uint8_t *mac)
{
  if (traffic_client_storage == NULL) return -1;
  traffic_client_stat *st = (traffic_client_stat*) traffic_client_storage;
  int lo = 0, hi = traffic_stats_client_count - 1;
  while (lo <= hi) {
    int mid = lo + ((hi - lo) >> 1);
    int cmp = memcmp(st[mid].mac, mac, 6);
    if (cmp == 0) {
      traffic_stats_last_pos = mid;
      memcpy(traffic_stats_last_mac, mac, 6);
      traffic_stats_last_mac_valid = true;
      return mid;
    }
    if (cmp < 0) lo = mid + 1;
    else hi = mid - 1;
  }
  return -1;
}

// NEU 2.30.49: Prueft, ob ein AP-Index zur aktuell laufenden Statistik
// gehoert - je nach Modus (siehe Kommentar beim Struct-Block oben). Wird
// pro Paket aus promisc_cb() heraus aufgerufen (Modus 3 darum bewusst per
// einfacher linearer Suche ueber selected_ap_indices[], das Array ist klein
// - keine Notwendigkeit fuer eine Binaersuche wie bei den Clients).
bool traffic_stats_ap_included(int ap_idx)
{
  if (ap_idx < 0 || ap_idx >= aps_known_count || ap_slot_free(ap_idx)) return false;
  if (traffic_stats_mode == 1) {
    return ap_idx == traffic_stats_ap_idx;
  } else if (traffic_stats_mode == 2) {
    return strcmp((const char*)aps_known[ap_idx].ssid, traffic_stats_ssid) == 0;
  } else if (traffic_stats_mode == 3) {
    for (int k = 0; k < selected_ap_count; k++) {
      if (selected_ap_indices[k] == ap_idx) return true;
    }
    return false;
  }
  return false;
}

// NEU 2.30.39: Erfassung eines Data-Frames fuer die ausgewaehlten AP(s).
// Nur Zaehler werden aktualisiert; keine Paketdaten werden gespeichert.
// NEU 2.30.49: Guard jetzt ueber traffic_stats_ap_included() (Modus 1/2/3
// statt nur Modus 1), "AP gesamt" ist damit implizit die Summe ueber alle
// eingeschlossenen APs.
// NEU 2.30.58: Schluessel ist jetzt die MAC-Adresse statt client_idx, damit
// ein zwischen mehreren eingeschlossenen APs roamender Client EINE Zeile mit
// aufaddierten Werten bekommt statt einer Zeile pro AP-Wechsel (siehe Kommentar
// beim Struct-Block). last_client_idx wird bei jedem Aufruf aktualisiert, auch
// bei einem bereits vorhandenen Eintrag (Zeile 2 unten), damit die Anzeige/
// Detailstatistik immer den zuletzt bekannten Index dieser MAC verwendet.
void traffic_stats_record(int ap_idx, int client_idx, const uint8_t *mac, uint16_t frame_len, bool is_tx)
{
  if (traffic_ap_storage == NULL || !traffic_stats_ap_included(ap_idx)) return;
  traffic_ap_stat *ap = (traffic_ap_stat*)traffic_ap_storage;
  if (is_tx) { ap->packets_tx++; ap->bytes_tx += frame_len; }
  else { ap->packets_rx++; ap->bytes_rx += frame_len; }
  if (traffic_client_storage == NULL || mac == NULL) return;
  traffic_client_stat *st = (traffic_client_stat*)traffic_client_storage;
  int pos = -1;
  if (traffic_stats_last_mac_valid && traffic_stats_last_pos >= 0 && traffic_stats_last_pos < traffic_stats_client_count && memcmp(st[traffic_stats_last_pos].mac, mac, 6) == 0) pos = traffic_stats_last_pos;
  if (pos < 0) pos = traffic_stats_find_client(mac);
  if (pos >= 0) {
    if (is_tx) { st[pos].packets_tx++; st[pos].bytes_tx += frame_len; }
    else { st[pos].packets_rx++; st[pos].bytes_rx += frame_len; }
    st[pos].last_client_idx = (uint16_t)client_idx;
    traffic_stats_last_pos = pos; memcpy(traffic_stats_last_mac, mac, 6); traffic_stats_last_mac_valid = true; return;
  }
  if (traffic_stats_client_count >= TRAFFIC_STATS_MAX_CLIENTS) { traffic_stats_dropped_clients++; return; }
  int insert = traffic_stats_client_count;
  while (insert > 0 && memcmp(st[insert-1].mac, mac, 6) > 0) { st[insert] = st[insert-1]; insert--; }
  memset(&st[insert], 0, sizeof(traffic_client_stat)); memcpy(st[insert].mac, mac, 6);
  st[insert].last_client_idx = (uint16_t)client_idx;
  if (is_tx) { st[insert].packets_tx = 1; st[insert].bytes_tx = frame_len; }
  else { st[insert].packets_rx = 1; st[insert].bytes_rx = frame_len; }
  if (traffic_stats_last_pos >= insert) traffic_stats_last_pos++;
  traffic_stats_client_count++; memcpy(traffic_stats_last_mac, mac, 6); traffic_stats_last_mac_valid = true; traffic_stats_last_pos = insert;
}

// NEU 2.30.65: Formatiert eine Sekundenzahl als HH:MM:SS.
// HH darf groesser als 24 werden.
void format_duration_hms(uint32_t total_sec, char* buf, size_t buflen)
{
  uint32_t h = total_sec / 3600UL;
  uint32_t m = (total_sec % 3600UL) / 60UL;
  uint32_t s = total_sec % 60UL;
  snprintf_P(buf, buflen, PSTR("%02lu:%02lu:%02lu"),
             (unsigned long)h, (unsigned long)m, (unsigned long)s);
}

// NEU 2.30.65: Formatiert Boot-Uptime als <d>d HH:MM:SS.
void format_uptime_dhm(uint32_t total_sec, char* buf, size_t buflen)
{
  uint32_t d = total_sec / 86400UL;
  uint32_t h = (total_sec % 86400UL) / 3600UL;
  uint32_t m = (total_sec % 3600UL) / 60UL;
  uint32_t s = total_sec % 60UL;
  snprintf_P(buf, buflen, PSTR("%lud %02lu:%02lu:%02lu"),
             (unsigned long)d, (unsigned long)h,
             (unsigned long)m, (unsigned long)s);
}

void traffic_stats_release_lock()
{
  if (channel_lock_active) filter_channel_unlock_if_active();
}

void traffic_stats_reapply_lock()
{
  if (traffic_stats_locked_filter[0] == '\0') return;
  if (channel_lock_active) return;
  strncpy(saved_channel_filter, channel_filter, 32);
  saved_channel_filter[31] = '\0';
  strncpy(channel_filter, traffic_stats_locked_filter, 32);
  channel_filter[31] = '\0';
  channel_lock_active = true;
  for (int ch = 1; ch <= 14; ch++) {
    if (is_channel_allowed(ch)) { channel = ch; wifi_set_channel(channel); break; }
  }
}

void traffic_stats_stop()
{
  traffic_stats_locked_filter[0] = '\0';
  traffic_stats_started_ms = 0;
  traffic_stats_started_unix = 0;
  traffic_stats_active = false;
  traffic_stats_mode = 0;
  traffic_stats_ap_idx = -1;
  traffic_stats_ssid[0] = '\0';
  traffic_stats_client_count = 0;
  traffic_stats_last_mac_valid = false;  // NEU 2.30.58: ersetzt traffic_stats_last_client_idx = -1
  traffic_stats_last_pos = -1;
  traffic_stats_dropped_clients = 0;
  if (traffic_ap_storage != NULL) { free(traffic_ap_storage); traffic_ap_storage = NULL; }
  if (traffic_client_storage != NULL) { free(traffic_client_storage); traffic_client_storage = NULL; }

  // NEU 2.30.65 Schritt E: temporaeren Statistik-Kanal-Lock aufheben.
  filter_channel_unlock_if_active();
}

// NEU 2.30.49: "mode" = current_list_mode (1/2/3) des Aufrufers, "ap_idx"
// nur fuer Modus 1 ausgewertet, "ssid" nur fuer Modus 2 (wird kopiert, kein
// dauerhafter Verweis auf ssid_list_combined_ssid noetig). Modus 3 braucht
// keinen weiteren Parameter, da er direkt die bestehenden globalen
// selected_ap_indices[]/selected_ap_count nutzt (siehe traffic_stats_ap_
// included()).
void traffic_stats_request_start(int mode, int ap_idx, const char* ssid)
{
  if (!traffic_stats_active) { traffic_stats_start(mode, ap_idx, ssid); return; }
  traffic_stats_pending_mode = mode;
  traffic_stats_pending_ap_idx = ap_idx;
  strncpy(traffic_stats_pending_ssid, ssid ? ssid : "", sizeof(traffic_stats_pending_ssid)-1);
  traffic_stats_pending_ssid[sizeof(traffic_stats_pending_ssid)-1] = '\0';
  traffic_stats_start_confirm_pending = true;
  Serial.println();
  Serial.println(F(" ACHTUNG: Eine Hintergrundverkehr-Aufzeichnung laeuft bereits."));
  Serial.println(F(" Ein neuer Start beendet und ersetzt diese Aufzeichnung."));
  Serial.println(F(" Wirklich neue Aufzeichnung starten? j=Ja / n=Nein"));
  Serial.print(F(" Auswahl: "));
}

void traffic_stats_start(int mode, int ap_idx, const char* ssid)
{
  traffic_stats_stop();

  if (mode == 1) {
    if (ap_idx < 0 || ap_idx >= aps_known_count || ap_slot_free(ap_idx)) {
      Serial.println(F(" Ungueltige AP-Auswahl."));
      return;
    }
    traffic_stats_ap_idx = ap_idx;
  } else if (mode == 2) {
    if (ssid == NULL || ssid[0] == '\0') {
      Serial.println(F(" Ungueltige SSID-Auswahl."));
      return;
    }
    strncpy(traffic_stats_ssid, ssid, 32);
    traffic_stats_ssid[32] = '\0';
  } else if (mode == 3) {
    if (selected_ap_count <= 0) {
      Serial.println(F(" Keine APs gewaehlt."));
      return;
    }
  } else {
    Serial.println(F(" Ungueltiger Modus."));
    return;
  }

  traffic_ap_storage = (uint8_t*) malloc(sizeof(traffic_ap_stat));
  traffic_client_storage = (uint8_t*) malloc(sizeof(traffic_client_stat) * TRAFFIC_STATS_MAX_CLIENTS);
  if (traffic_ap_storage == NULL || traffic_client_storage == NULL) {
    if (traffic_ap_storage != NULL) { free(traffic_ap_storage); traffic_ap_storage = NULL; }
    if (traffic_client_storage != NULL) { free(traffic_client_storage); traffic_client_storage = NULL; }
    Serial.println(F(" Fehler: kein Speicher fuer die Verkehrstatistik verfuegbar."));
    return;
  }
  memset(traffic_ap_storage, 0, sizeof(traffic_ap_stat));
  memset(traffic_client_storage, 0, sizeof(traffic_client_stat) * TRAFFIC_STATS_MAX_CLIENTS);
  traffic_stats_mode = mode;
  traffic_stats_active = true;
  traffic_stats_last_refresh = millis();

  // NEU 2.30.65: Startzeitpunkt der Statistik-Sitzung merken.
  traffic_stats_started_ms = millis();
  traffic_stats_started_unix = ntp_synced ? current_unix_time_with_tz() : 0;

  // NEU 2.30.65 Schritt E: Scan auf die relevanten AP-Kanaele begrenzen.
  if (!channel_lock_active) {
    uint16_t seen = 0;

    if (mode == 1) {
      uint8_t ch = aps_known[traffic_stats_ap_idx].channel & AP_CHANNEL_MASK;
      if (ch >= 1 && ch <= 14) seen |= ((uint16_t)1 << ch);
    } else if (mode == 2) {
      for (int a = 0; a < aps_known_count; a++) {
        if (!ap_slot_free(a) &&
            strcmp((const char*)aps_known[a].ssid, traffic_stats_ssid) == 0) {
          uint8_t ch = aps_known[a].channel & AP_CHANNEL_MASK;
          if (ch >= 1 && ch <= 14) seen |= ((uint16_t)1 << ch);
        }
      }
    } else if (mode == 3) {
      for (int k = 0; k < selected_ap_count; k++) {
        int idx = selected_ap_indices[k];
        if (idx >= 0 && idx < aps_known_count && !ap_slot_free(idx)) {
          uint8_t ch = aps_known[idx].channel & AP_CHANNEL_MASK;
          if (ch >= 1 && ch <= 14) seen |= ((uint16_t)1 << ch);
        }
      }
    }

    int count = 0;
    for (int ch = 1; ch <= 14; ch++) {
      if (seen & ((uint16_t)1 << ch)) count++;
    }

    if (count > 0 && count < 14) {
      char new_filter[32];
      new_filter[0] = '\0';
      bool first = true;

      for (int ch = 1; ch <= 14; ch++) {
        if (seen & ((uint16_t)1 << ch)) {
          if (!first) {
            strncat(new_filter, ",", sizeof(new_filter) - strlen(new_filter) - 1);
          }
          char tmp[4];
          snprintf_P(tmp, sizeof(tmp), PSTR("%d"), ch);
          strncat(new_filter, tmp, sizeof(new_filter) - strlen(new_filter) - 1);
          first = false;
        }
      }

      strncpy(saved_channel_filter, channel_filter, 32);
      saved_channel_filter[31] = '\0';
      channel_lock_active = true;
      strncpy(channel_filter, new_filter, 32);
      channel_filter[31] = '\0';
      strncpy(traffic_stats_locked_filter, new_filter, sizeof(traffic_stats_locked_filter) - 1);
      traffic_stats_locked_filter[sizeof(traffic_stats_locked_filter) - 1] = '\0';

      for (int ch = 1; ch <= 14; ch++) {
        if (seen & ((uint16_t)1 << ch)) {
          channel = ch;
          wifi_set_channel(channel);
          break;
        }
      }
      Serial.printf_P(PSTR(" Kanal-Scan begrenzt auf: %s\r\n"), channel_filter);
    }
  }

  menu_state = STATE_TRAFFIC_STATS;
  traffic_stats_redraw();
}

// NEU 2.30.49: Kopfzeile jetzt modusabhaengig (Modus 1: einzelner AP wie
// bisher; Modus 2: SSID-Buendel-Name + Anzahl zugehoeriger APs; Modus 3:
// Kommaliste der gewaehlten AP-Indizes/SSIDs, analog zur Kopfzeile in
// menu_enter_ssid_list_multi()). Die Client-Zeile bekommt bei Modus 2/3
// zusaetzlich eine AP-Spalte (clients_known[].ap_idx, aktueller Stand zum
// Anzeigezeitpunkt - siehe Kommentar bei traffic_client_stat oben), da dort
// mehrere APs im Spiel sind und genau DAS der interessante Unterschied zu
// Modus 1 ist.
void format_pkt_field(uint32_t pkt, char *buf, size_t buflen)
{
  if (!buf || buflen == 0) return;
  if (pkt < 1000000UL) snprintf_P(buf, buflen, PSTR("%lu"), (unsigned long)pkt);
  else { uint32_t thousands=pkt/1000UL; snprintf_P(buf, buflen, PSTR("%luk%03lu"), (unsigned long)(thousands/1000UL), (unsigned long)(thousands%1000UL)); }
}

void format_kb_3char(uint32_t kb, char* buf, size_t buflen)
{
  if (kb < 1000) snprintf_P(buf, buflen, PSTR("%3lu"), (unsigned long)kb);
  else if (kb < 10000) snprintf_P(buf, buflen, PSTR("%luk%lu"), (unsigned long)(kb/1000), (unsigned long)((kb%1000)/100));
  else if (kb < 100000) snprintf_P(buf, buflen, PSTR("%luk"), (unsigned long)(kb/1000));
  else if (kb < 1000000) snprintf_P(buf, buflen, PSTR("M%02lu"), (unsigned long)(kb/10000UL));
  else if (kb < 10000000) snprintf_P(buf, buflen, PSTR("%luM%lu"), (unsigned long)(kb/1000000), (unsigned long)((kb%1000000)/100000));
  else if (kb < 100000000) snprintf_P(buf, buflen, PSTR("%luM"), (unsigned long)(kb/1000000));
  else if (kb < 1000000000UL) snprintf_P(buf, buflen, PSTR("G%02lu"), (unsigned long)(kb/1000000));
  else snprintf_P(buf, buflen, PSTR("OVL"));
}

void traffic_stats_print_header(Print &out)
{
  out.println(F("======================================================="));
  out.println(traffic_stats_detailed_view ? F(" Hintergrundverkehr   (Ansicht: ERWEITERT)") : F(" Hintergrundverkehr   (Ansicht: KOMPAKT)"));
  out.println(F("======================================================="));
  char gen_ts[32]; format_generation_timestamp(gen_ts,sizeof(gen_ts));
  out.printf_P(PSTR(" Erzeugt: %s | Programmversion: v%s\r\n"),gen_ts,FIRMWARE_VERSION);

  char timebuf[24], durbuf[12];
  uint32_t elapsed_sec = (millis() - traffic_stats_started_ms) / 1000UL;
  format_duration_hms(elapsed_sec, durbuf, sizeof(durbuf));
  if (traffic_stats_started_unix != 0) {
    time_t stime = traffic_stats_started_unix; struct tm* ti = localtime(&stime);
    snprintf_P(timebuf, sizeof(timebuf), PSTR("%04d-%02d-%02d %02d:%02d:%02d"), ti->tm_year+1900,ti->tm_mon+1,ti->tm_mday,ti->tm_hour,ti->tm_min,ti->tm_sec);
    out.printf_P(PSTR(" Start: %s   Laufzeit: %s\r\n"),timebuf,durbuf);
  } else {
    format_uptime_dhm(traffic_stats_started_ms/1000UL,timebuf,sizeof(timebuf));
    out.printf_P(PSTR(" Start: boot+%s   Laufzeit: %s\r\n"),timebuf,durbuf);
  }
  if (traffic_stats_mode == 1) {
    if (traffic_stats_ap_idx >= aps_known_count || ap_slot_free(traffic_stats_ap_idx)) return;
    out.printf_P(PSTR(" AP #%d  SSID: %s\r\n"),traffic_stats_ap_idx,aps_known[traffic_stats_ap_idx].ssid);
    out.print(F(" AP-MAC: ")); for(int b=0;b<6;b++) out.printf_P(PSTR("%02x"),aps_known[traffic_stats_ap_idx].bssid[b]); out.println();
  } else if (traffic_stats_mode == 2) {
    int member_count=0; for(int a=0;a<aps_known_count;a++) if(traffic_stats_ap_included(a)) member_count++;
    out.printf_P(PSTR(" SSID-Buendel: %s  (%d APs)\r\n"),traffic_stats_ssid,member_count);
  } else if (traffic_stats_mode == 3) {
    out.print(F(" Multi-AP: ")); for(int k=0;k<selected_ap_count;k++){if(k)out.print(',');int a=selected_ap_indices[k];if(a>=0&&a<aps_known_count&&!ap_slot_free(a))out.printf_P(PSTR("%d (%s)"),a,(const char*)aps_known[a].ssid);else out.printf_P(PSTR("%d"),a);} out.println();
  }
  if(channel_lock_active) out.printf_P(PSTR(" Kanal-Scan: %s (gesperrt)\r\n"),channel_filter);
  out.printf_P(PSTR(" Geraete gelistet: %d\r\n"), traffic_stats_client_count);

  // Gesamtwerte aus den erfassten Client-Datensaetzen bilden.
  // Der Header wird auch beim Dateiexport ohne lokale AP-Variable verwendet.
  traffic_client_stat *st = (traffic_client_stat*) traffic_client_storage;
  uint32_t ptx=0,prx=0;
  uint64_t btx_bytes=0,brx_bytes=0;
  for(int i=0;i<traffic_stats_client_count;i++) {
    ptx += st[i].packets_tx;
    prx += st[i].packets_rx;
    btx_bytes += st[i].bytes_tx;
    brx_bytes += st[i].bytes_rx;
  }
  uint32_t btx=(uint32_t)(btx_bytes/1024ULL),brx=(uint32_t)(brx_bytes/1024ULL);
  char a[20],b[20],c[20],d[20],e[20],f[20];
  strncpy(a,format_number_with_dots(ptx+prx),sizeof(a)-1);a[sizeof(a)-1]=0;
  strncpy(b,format_number_with_dots(btx+brx),sizeof(b)-1);b[sizeof(b)-1]=0;
  strncpy(c,format_number_with_dots(ptx),sizeof(c)-1);c[sizeof(c)-1]=0;
  strncpy(d,format_number_with_dots(btx),sizeof(d)-1);d[sizeof(d)-1]=0;
  strncpy(e,format_number_with_dots(prx),sizeof(e)-1);e[sizeof(e)-1]=0;
  strncpy(f,format_number_with_dots(brx),sizeof(f)-1);f[sizeof(f)-1]=0;
  out.println();
  int w1=max((int)strlen(a),(int)strlen(c)); w1=max(w1,(int)strlen(e));
  int w2=max((int)strlen(b),(int)strlen(d)); w2=max(w2,(int)strlen(f));
  out.printf_P(PSTR(" Gesamt: %*s Pakete / %*s kB\r\n"),w1,a,w2,b);
  out.printf_P(PSTR(" TX:     %*s Pakete / %*s kB\r\n"),w1,c,w2,d);
  out.printf_P(PSTR(" RX:     %*s Pakete / %*s kB\r\n"),w1,e,w2,f);
}

void traffic_stats_print_table(Print &out)
{
  if (!traffic_stats_active || traffic_ap_storage == NULL) return;
  traffic_ap_stat *ap = (traffic_ap_stat*) traffic_ap_storage;
  traffic_client_stat *st = (traffic_client_stat*) traffic_client_storage;

  traffic_stats_print_header(out);
  out.println(F("-------------------------------------------------------"));

  int wptx=7,wprx=7,wkb=3,wps=3;
  if(traffic_stats_detailed_view){
    for(int i=0;i<traffic_stats_client_count;i++){
      char z[12]; format_pkt_field(st[i].packets_tx,z,sizeof(z)); if((int)strlen(z)>wptx)wptx=strlen(z);
      format_pkt_field(st[i].packets_rx,z,sizeof(z)); if((int)strlen(z)>wprx)wprx=strlen(z);
      char x[8],y[8];format_kb_3char(st[i].bytes_tx/1024UL,x,sizeof(x));format_kb_3char(st[i].bytes_rx/1024UL,y,sizeof(y));
      if((int)strlen(x)>wkb)wkb=strlen(x);if((int)strlen(y)>wkb)wkb=strlen(y);
      if(st[i].packets_tx){format_kb_3char(st[i].bytes_tx/st[i].packets_tx,x,sizeof(x));if((int)strlen(x)>wps)wps=strlen(x);} 
      if(st[i].packets_rx){format_kb_3char(st[i].bytes_rx/st[i].packets_rx,y,sizeof(y));if((int)strlen(y)>wps)wps=strlen(y);}
    }
    if(wkb>3)wkb=3;if(wps>3)wps=3;
    out.printf_P(PSTR("  #  MAC           AP %*s %*s | %*s | %*s %s\r\n"),wptx,"Pkt TX",wprx,"Pkt RX",wkb+1,"kB T/RX",wps+1,"PS T/RX","Vol-Verh");
  } else out.println(F("  #  MAC             AP    Pkt | kB T/RX | PS T/RX"));
  out.println(F("-------------------------------------------------------"));
  for(int i=0;i<traffic_stats_client_count;i++){
    int ci=st[i].last_client_idx;int ap_col=(ci>=0&&ci<clients_known_count)?clients_known[ci].ap_idx:-1;
    char tx[8],rx[8],mt[8],mr[8],ratio[16],ptxbuf[12],prxbuf[12],ptotalbuf[12];
    format_pkt_field(st[i].packets_tx,ptxbuf,sizeof(ptxbuf)); format_pkt_field(st[i].packets_rx,prxbuf,sizeof(prxbuf)); format_pkt_field(st[i].packets_tx+st[i].packets_rx,ptotalbuf,sizeof(ptotalbuf));
    format_kb_3char(st[i].bytes_tx/1024UL,tx,sizeof(tx));format_kb_3char(st[i].bytes_rx/1024UL,rx,sizeof(rx));
    if(st[i].packets_tx)format_kb_3char(st[i].bytes_tx/st[i].packets_tx,mt,sizeof(mt));else strcpy(mt,"---");
    if(st[i].packets_rx)format_kb_3char(st[i].bytes_rx/st[i].packets_rx,mr,sizeof(mr));else strcpy(mr,"---");
    if(!st[i].bytes_tx&&!st[i].bytes_rx)strcpy(ratio,"0:0");else if(!st[i].bytes_rx)strcpy(ratio,"0:1");else if(!st[i].bytes_tx)strcpy(ratio,"1:0");else if(st[i].bytes_rx>st[i].bytes_tx){uint32_t r=(uint32_t)(((uint64_t)st[i].bytes_rx+st[i].bytes_tx/2)/st[i].bytes_tx);snprintf(ratio,sizeof(ratio),"1:%lu",(unsigned long)r);}else{uint32_t r=(uint32_t)(((uint64_t)st[i].bytes_tx+st[i].bytes_rx/2)/st[i].bytes_rx);snprintf(ratio,sizeof(ratio),"%lu:1",(unsigned long)r);}
    if(traffic_stats_detailed_view){
      out.printf_P(PSTR("%3d  "),ci);print_mac(st[i].mac,NULL,&out);
      out.printf_P(PSTR(" %3d %*s %*s | %*s/%-*s | %*s/%-*s %8s\r\n"),ap_col,wptx,ptxbuf,wprx,prxbuf,wkb,tx,wkb,rx,wps,mt,wps,mr,ratio);
    }else{out.printf_P(PSTR("%3d  "),ci);print_mac(st[i].mac,NULL,&out);out.printf_P(PSTR("   %3d %6s | %3s/%-3s | %3s/%-3s\r\n"),ap_col,ptotalbuf,tx,rx,mt,mr);}
    if((i&0x0f)==0)yield();
  }
  if(traffic_stats_client_count==0)out.println(F("(noch kein Client-Verkehr erfasst)"));
  if(traffic_stats_dropped_clients>0){char dropped_buf[20];strncpy(dropped_buf,format_number_with_dots(traffic_stats_dropped_clients),sizeof(dropped_buf)-1);dropped_buf[sizeof(dropped_buf)-1]=0;out.printf_P(PSTR("! Statistiklimit: %s Frames von nicht erfassten MACs.\r\n"),dropped_buf);}
  out.println(F("-------------------------------------------------------"));
}

void traffic_stats_redraw()
{
  if (menu_state != STATE_TRAFFIC_STATS || !traffic_stats_active || traffic_ap_storage == NULL) return;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;

  traffic_stats_print_table(Serial);

  Serial.println(F(" Nur Data-Frames werden gezaehlt. Refresh: alle 5 s"));
  Serial.println(F(" d = Detailstatistik eines Clients (d + Zahl)"));
  Serial.println(F(" s = Statistik als Datei speichern (TR_<SSID>.txt)"));
  Serial.println(F(" x = Ansicht wechseln"));
  Serial.println(F(" Backspace = zur Geraeteliste, ESC = Hauptmenue"));
  Serial.println(F(" e = Aufzeichnung beenden"));
  traffic_stats_last_refresh = millis();
}

void traffic_stats_get_primary_ssid(char* out, size_t outlen)
{
  if (out == NULL || outlen == 0) return;
  out[0] = '\0';

  if (traffic_stats_mode == 1) {
    if (traffic_stats_ap_idx >= 0 && traffic_stats_ap_idx < aps_known_count &&
        !ap_slot_free(traffic_stats_ap_idx))
      strncpy(out, (const char*)aps_known[traffic_stats_ap_idx].ssid, outlen - 1);
  } else if (traffic_stats_mode == 2) {
    strncpy(out, traffic_stats_ssid, outlen - 1);
  } else if (traffic_stats_mode == 3) {
    if (selected_ap_count > 0) {
      int idx = selected_ap_indices[0];
      if (idx >= 0 && idx < aps_known_count && !ap_slot_free(idx))
        strncpy(out, (const char*)aps_known[idx].ssid, outlen - 1);
    }
  }

  out[outlen - 1] = '\0';
  if (out[0] == '\0') strncpy(out, "unbekannt", outlen - 1);
  out[outlen - 1] = '\0';
}

void traffic_stats_print_file_table(Print &out)
{
  if (!traffic_stats_active || traffic_ap_storage == NULL || traffic_client_storage == NULL) return;
  traffic_client_stat *st = (traffic_client_stat*)traffic_client_storage;
  out.println(F("   #  MAC           AP   Pkt TX   Pkt RX   Bytes TX   Bytes RX   � TX  � RX  Vol-Verh"));
  out.println(F("-------------------------------------------------------------------------------"));
  for (int i = 0; i < traffic_stats_client_count; i++) {
    int ci = st[i].last_client_idx;
    int ap_col = (ci >= 0 && ci < clients_known_count) ? clients_known[ci].ap_idx : -1;
    char ratio[24];
    if (!st[i].bytes_tx && !st[i].bytes_rx) strcpy(ratio,"0:0");
    else if (!st[i].bytes_rx) strcpy(ratio,"0:1");
    else if (!st[i].bytes_tx) strcpy(ratio,"1:0");
    else if (st[i].bytes_rx > st[i].bytes_tx) {
      uint32_t r=(uint32_t)(((uint64_t)st[i].bytes_rx+st[i].bytes_tx/2)/st[i].bytes_tx);
      snprintf(ratio,sizeof(ratio),"1:%lu",(unsigned long)r);
    } else {
      uint32_t r=(uint32_t)(((uint64_t)st[i].bytes_tx+st[i].bytes_rx/2)/st[i].bytes_rx);
      snprintf(ratio,sizeof(ratio),"%lu:1",(unsigned long)r);
    }
    char mean_tx[16], mean_rx[16];
    if (st[i].packets_tx) snprintf(mean_tx,sizeof(mean_tx),"%lu",(unsigned long)(st[i].bytes_tx/st[i].packets_tx)); else strcpy(mean_tx,"-");
    if (st[i].packets_rx) snprintf(mean_rx,sizeof(mean_rx),"%lu",(unsigned long)(st[i].bytes_rx/st[i].packets_rx)); else strcpy(mean_rx,"-");
    out.printf_P(PSTR("%4d  "),ci); print_mac(st[i].mac,NULL,&out);
    out.printf_P(PSTR(" %3d %8lu %8lu %10lu %10lu %6s %6s %6s\r\n"),ap_col,
      (unsigned long)st[i].packets_tx,(unsigned long)st[i].packets_rx,
      (unsigned long)st[i].bytes_tx,(unsigned long)st[i].bytes_rx,mean_tx,mean_rx,ratio);
    if ((i & 0x0f)==0) yield();
  }
}

void traffic_stats_save_to_file()
{
  if (!traffic_stats_active) {
    Serial.println(F(" Keine aktive Statistik - nichts zu speichern."));
    return;
  }
  if (ESP.getFreeHeap() < 2500) {
    Serial.println(F(" Heap zu knapp - Speichern uebersprungen."));
    return;
  }

  char ssid_full[33];
  traffic_stats_get_primary_ssid(ssid_full, sizeof(ssid_full));
  char ssid_short[11];
  int sn = 0;

  for (int i = 0; ssid_full[i] != '\0' && sn < 10; i++) {
    char ch = ssid_full[i];
    if (isalnum((unsigned char)ch) || ch == '_' || ch == '-')
      ssid_short[sn++] = ch;
  }
  ssid_short[sn] = '\0';
  if (sn == 0) strcpy(ssid_short, "unbekannt");

  char path[40];
  snprintf_P(path, sizeof(path), PSTR("/TR_%s.txt"), ssid_short);

  if (!make_collision_safe_path(path,path,sizeof(path))) { Serial.println(F(" Fehler: kollisionsfreier Dateiname nicht verfuegbar.")); return; }
  File f = LittleFS.open(path, "w");
  if (!f) {
    Serial.println(F(" Datei konnte nicht angelegt werden."));
    return;
  }

  traffic_stats_print_header(f);
  f.println(F("-------------------------------------------------------"));

  traffic_stats_print_file_table(f);
  f.close();
  Serial.printf_P(PSTR(" Gespeichert: %s\r\n"), path);
}


// NEU 2.30.42: Liefert die Adressfelder eines 802.11-Rahmens fuer den
// Client-Match. Es werden nur Header-Adressen betrachtet, niemals Payload.
bool traffic_detail_address_match(uint8_t *frame, uint16_t frame_len,
                                   uint8_t frame_type, uint8_t frame_subtype,
                                   const uint8_t *mac)
{
  if (frame == NULL || mac == NULL) return false;

  if (frame_type == 0) { // Management: DA/SA/BSSID liegen in den ersten 24 Byte.
    if (frame_len < 22) return false;
    if (!memcmp(frame + 4, mac, ETH_MAC_LEN)) return true;
    if (!memcmp(frame + 10, mac, ETH_MAC_LEN)) return true;
    if (!memcmp(frame + 16, mac, ETH_MAC_LEN)) return true;
    return false;
  }

  if (frame_type == 1) { // Control: Adressanzahl haengt vom Subtyp ab.
    if (frame_len < 10) return false;
    if (!memcmp(frame + 4, mac, ETH_MAC_LEN)) return true;
    switch (frame_subtype) {
      case 4: case 5: case 7: case 8: case 9: case 10: case 11:
        if (frame_len >= 16 && !memcmp(frame + 10, mac, ETH_MAC_LEN)) return true;
        break;
      default:
        break;
    }
    return false;
  }

  if (frame_type == 2) { // Data: bis zu vier Adressfelder, je nach DS-Bits.
    if (frame_len < 16) return false;
    if (!memcmp(frame + 4, mac, ETH_MAC_LEN)) return true;
    if (!memcmp(frame + 10, mac, ETH_MAC_LEN)) return true;
    if (frame_len >= 22 && !memcmp(frame + 16, mac, ETH_MAC_LEN)) return true;
    if (frame_len >= 30 && !memcmp(frame + 22, mac, ETH_MAC_LEN)) return true;
  }
  return false;
}

void traffic_detail_stop()
{
  traffic_detail_started_ms = 0;
  traffic_detail_started_unix = 0;
  traffic_detail_client_idx = -1;
  traffic_detail_selecting = false;
  traffic_detail_input_len = 0;
  traffic_detail_input_buf[0] = '\0';
  traffic_detail_last_refresh = 0;
  if (traffic_detail_storage != NULL) {
    free(traffic_detail_storage);
    traffic_detail_storage = NULL;
  }
}

void traffic_detail_start(int client_idx)
{
  if (client_idx < 0 || client_idx >= clients_known_count) {
    Serial.println(F(" Ungueltige Client-Auswahl."));
    return;
  }
  // Der Detailmodus ist bewusst an einen tatsaechlich vorhandenen Client
  // gebunden. Ein vorhandener clients_known[]-Index bleibt waehrend der
  // Anzeige der Statistik der Referenzpunkt.
  traffic_detail_stop();
  traffic_detail_storage = (uint8_t*) malloc(sizeof(traffic_detail_stat));
  if (traffic_detail_storage == NULL) {
    Serial.println(F(" Fehler: kein Speicher fuer die Detailstatistik verfuegbar."));
    return;
  }
  memset(traffic_detail_storage, 0, sizeof(traffic_detail_stat));
  memcpy(((traffic_detail_stat*)traffic_detail_storage)->mac,
         clients_known[client_idx].station, ETH_MAC_LEN);
  traffic_detail_client_idx = client_idx;
  menu_state = STATE_TRAFFIC_DETAIL;
  traffic_detail_last_refresh = millis();
  traffic_detail_started_ms = millis();
  traffic_detail_started_unix = ntp_synced ? current_unix_time_with_tz() : 0;
  traffic_detail_redraw();
}

void traffic_detail_record(uint8_t *frame, uint16_t frame_len,
                           uint8_t frame_type, uint8_t frame_subtype)
{
  if (traffic_detail_storage == NULL || traffic_detail_client_idx < 0) return;
  if (frame == NULL || frame_len == 0 || frame_type > 2 || frame_subtype > 15) return;
  traffic_detail_stat *d = (traffic_detail_stat*)traffic_detail_storage;
  if (!traffic_detail_address_match(frame, frame_len, frame_type, frame_subtype, d->mac)) return;
  d->packets_total++;
  d->bytes_total += frame_len;
  d->packets[frame_type][frame_subtype]++;
  d->bytes[frame_type][frame_subtype] += frame_len;
}

void traffic_detail_print_table(Print &out)
{
  if (traffic_detail_storage == NULL || traffic_detail_client_idx < 0) return;
  if (traffic_detail_client_idx >= clients_known_count) return;

  traffic_detail_stat *d = (traffic_detail_stat*)traffic_detail_storage;
  int ci = traffic_detail_client_idx;
  int ap_idx = clients_known[ci].ap_idx;
  out.println(F("======================================================="));
  out.println(F(" Detailverkehr Client"));
  out.println(F("======================================================="));

  char timebuf[24], durbuf[12];
  uint32_t elapsed_sec = (millis() - traffic_detail_started_ms) / 1000UL;
  format_duration_hms(elapsed_sec, durbuf, sizeof(durbuf));
  if (traffic_detail_started_unix != 0) {
    time_t stime = traffic_detail_started_unix;
    struct tm* ti = localtime(&stime);
    snprintf_P(timebuf, sizeof(timebuf), PSTR("%04d-%02d-%02d %02d:%02d:%02d"),
               ti->tm_year + 1900, ti->tm_mon + 1, ti->tm_mday,
               ti->tm_hour, ti->tm_min, ti->tm_sec);
    out.printf_P(PSTR(" Start: %s   Laufzeit: %s\r\n"), timebuf, durbuf);
  } else {
    format_uptime_dhm(traffic_detail_started_ms / 1000UL, timebuf, sizeof(timebuf));
    out.printf_P(PSTR(" Start: boot+%s   Laufzeit: %s\r\n"), timebuf, durbuf);
  }
  if (ap_idx >= 0 && ap_idx < aps_known_count && !ap_slot_free(ap_idx))
    out.printf_P(PSTR(" SSID: %s   %d db\r\n"), (const char*)aps_known[ap_idx].ssid, (int)aps_known[ap_idx].rssi);
  else out.println(F(" SSID: unbekannt"));
  out.printf_P(PSTR(" Client-Index: %d  %d db\r\n"), ci, (int)clients_known[ci].rssi);
  out.print(F(" MAC:  "));
  print_mac(d->mac, NULL, &out);
  out.println();
  out.println();

  char total_pkt_buf[20], total_kb_buf[20];
  strncpy(total_pkt_buf, format_number_with_dots(d->packets_total), sizeof(total_pkt_buf)-1);
  total_pkt_buf[sizeof(total_pkt_buf)-1] = '\0';
  strncpy(total_kb_buf, format_number_with_dots(d->bytes_total / 1024UL), sizeof(total_kb_buf)-1);
  total_kb_buf[sizeof(total_kb_buf)-1] = '\0';
  out.printf_P(PSTR(" Gesamt: %s Pakete  %s kB\r\n"), total_pkt_buf, total_kb_buf);
  out.println(F("-------------------------------------------------------"));
  out.printf_P(PSTR(" %-7s%8s  %10s  %s\r\n"), "Typ", "Pakete", "kB", "Bezeichnung");
  out.println(F("-------------------------------------------------------"));

  for (uint8_t t = 0; t < 3; t++) {
    for (uint8_t st = 0; st < 16; st++) {
      if (d->packets[t][st] == 0) continue;
      const char *name = ie_frame_subtype_name(t, st);
      char pkt_buf[20], kb_buf[20];
      strncpy(pkt_buf, format_number_with_dots(d->packets[t][st]), sizeof(pkt_buf)-1);
      pkt_buf[sizeof(pkt_buf)-1] = '\0';
      strncpy(kb_buf, format_number_with_dots(d->bytes[t][st] / 1024UL), sizeof(kb_buf)-1);
      kb_buf[sizeof(kb_buf)-1] = '\0';
      out.printf_P(PSTR(" %-7s%8s  %10s  %s\r\n"),
                   t == 0 ? "Mgmt" : (t == 1 ? "Control" : "Data"),
                   pkt_buf, kb_buf, name);
    }
  }
  if (d->packets_total == 0) out.println(F(" (noch kein Verkehr dieses Clients erfasst)"));
  out.println(F("-------------------------------------------------------"));
}

void traffic_detail_redraw()
{
  if (menu_state != STATE_TRAFFIC_DETAIL || traffic_detail_storage == NULL || traffic_detail_client_idx < 0) return;
  if (traffic_detail_client_idx >= clients_known_count) return;

  vt_clear_screen();
  OfflineBannerGuard __banner_guard;

  traffic_detail_print_table(Serial);

  Serial.println(F(" Erfasst werden nur Header-Adressen; keine Paketdaten."));
  Serial.println(F(" Erfassung: laufend | Anzeige: alle 5 s | r = sofort neu zeichnen"));
  Serial.println(F(" s = Detailstatistik als Datei speichern (TR_<MAC>.txt)"));
  Serial.println(F(" Backspace = zurueck zur Verkehrsuebersicht, ESC = Hauptmenue"));
  traffic_detail_last_refresh = millis();
}

void traffic_detail_save_to_file()
{
  if (traffic_detail_storage == NULL || traffic_detail_client_idx < 0) {
    Serial.println(F(" Keine aktive Detailstatistik - nichts zu speichern."));
    return;
  }
  if (ESP.getFreeHeap() < 2500) {
    Serial.println(F(" Heap zu knapp - Speichern uebersprungen."));
    return;
  }

  traffic_detail_stat *d = (traffic_detail_stat*)traffic_detail_storage;
  char macstr[13];
  for (int b = 0; b < 6; b++)
    sprintf_P(macstr + b * 2, PSTR("%02x"), d->mac[b]);
  macstr[12] = '\0';

  char path[40];
  snprintf_P(path, sizeof(path), PSTR("/TR_%s.txt"), macstr);

  if (!make_collision_safe_path(path,path,sizeof(path))) { Serial.println(F(" Fehler: kollisionsfreier Dateiname nicht verfuegbar.")); return; }
  File f = LittleFS.open(path, "w");
  if (!f) {
    Serial.println(F(" Datei konnte nicht angelegt werden."));
    return;
  }

  char timebuf[24], durbuf[12];
  write_generated_file_header(f);
  uint32_t elapsed_sec = (millis() - traffic_detail_started_ms) / 1000UL;
  format_duration_hms(elapsed_sec, durbuf, sizeof(durbuf));

  if (traffic_detail_started_unix != 0 && ntp_synced) {
    time_t stime = traffic_detail_started_unix;
    struct tm* ti = localtime(&stime);
    f.printf_P(PSTR(" Start : %04d-%02d-%02d %02d:%02d:%02d\r\n"),
               ti->tm_year + 1900, ti->tm_mon + 1, ti->tm_mday,
               ti->tm_hour, ti->tm_min, ti->tm_sec);
    time_t en = current_unix_time_with_tz();
    struct tm* te = localtime(&en);
    f.printf_P(PSTR(" Ende  : %04d-%02d-%02d %02d:%02d:%02d\r\n"),
               te->tm_year + 1900, te->tm_mon + 1, te->tm_mday,
               te->tm_hour, te->tm_min, te->tm_sec);
  } else {
    format_uptime_dhm(traffic_detail_started_ms / 1000UL, timebuf, sizeof(timebuf));
    f.printf_P(PSTR(" Start : boot +%s\r\n"), timebuf);
    format_uptime_dhm(millis() / 1000UL, timebuf, sizeof(timebuf));
    f.printf_P(PSTR(" Ende  : boot +%s\r\n"), timebuf);
  }
  f.printf_P(PSTR(" Dauer : %s\r\n"), durbuf);
  f.println(F("======================================================="));

  traffic_detail_print_table(f);
  f.close();
  Serial.printf_P(PSTR(" Gespeichert: %s\r\n"), path);
}



void print_beacon(beaconinfo beacon)
{
  uint64_t now = effective_now();
  if (beacon.err != 0) {
    Serial.printf_P(PSTR("BEACON ERR: (%d)  \r\n"), beacon.err);
  } else {
    bool stale = ((now - beacon.last_heard) > STALE_AGE_SEC);
    bool is_open = (beacon.channel & AP_OPEN_FLAG) != 0;  // NEU 2.29.8
    if (stale) vt_sgr("90");
    if (is_open) {
      Serial.printf_P(PSTR("BEACON: <=============== (%32s)  "), beacon.ssid);
    } else {
      Serial.printf_P(PSTR("BEACON: <=============== [%32s]  "), beacon.ssid);
    }
    print_mac(beacon.bssid, stale ? "90" : NULL);
    Serial.printf_P(PSTR(" %3d"), beacon.channel & AP_CHANNEL_MASK);  // NEU 2.29.8: Flag-Bit ausmaskieren
    Serial.printf_P(PSTR("   %d"), (now - beacon.last_heard));
    Serial.printf_P(PSTR("   %d"), (beacon.reported));
    Serial.printf_P(PSTR("   %4d"), beacon.rssi);
    if (stale) vt_color_reset();
    Serial.println();
  }
}

void print_client(clientinfo ci)
{
  int known = 0;
  uint64_t now = effective_now();
  if (ci.err != 0) {
    Serial.printf_P(PSTR("ci.err %02d"), ci.err);
    Serial.printf_P(PSTR("\r\n"));
  } else {
    bool stale = ((now - ci.last_heard) > STALE_AGE_SEC);
    if (stale) vt_sgr("90");
    Serial.printf_P(PSTR("DEVICE: "));
    print_mac(ci.station, stale ? "90" : NULL);
    Serial.printf_P(PSTR(" ==> "));

    // NEU 2.29.11 (Etappe 3): ap_idx zeigt direkt auf den Eintrag - keine
    // Suchschleife mehr noetig (vorher O(n) per BSSID-Vergleich).
    if (ci.ap_idx < aps_known_count && ! ap_slot_free(ci.ap_idx)) {
      bool is_open = (aps_known[ci.ap_idx].channel & AP_OPEN_FLAG) != 0;  // NEU 2.29.8
      if (is_open) {
        Serial.printf_P(PSTR("(%32s)  "), aps_known[ci.ap_idx].ssid);
      } else {
        Serial.printf_P(PSTR("[%32s]  "), aps_known[ci.ap_idx].ssid);
      }
      known = 1;
    }

    if (! known)  {
      Serial.printf_P(PSTR("[%32s]  "), "??");
    };
    if (known) {
      print_mac(aps_known[ci.ap_idx].bssid, stale ? "90" : NULL);
    } else {
      Serial.printf_P(PSTR("????????????"));
    }
    Serial.printf_P(PSTR(" %3d"), ci.channel);
    Serial.printf_P(PSTR("   %d"), (now - ci.last_heard));
    Serial.printf_P(PSTR("   %d"), (ci.reported));
    Serial.printf_P(PSTR("   %4d"), ci.rssi);
    if (stale) vt_color_reset();
    Serial.println();
  }
}

void print_probe(probeinfo ci)
{
  uint64_t now = effective_now();
  if (ci.err != 0) {
    Serial.printf_P(PSTR("ci.err %02d"), ci.err);
    Serial.printf_P(PSTR("\r\n"));
  } else {
    bool stale = ((now - ci.last_heard) > STALE_AGE_SEC);
    if (stale) vt_sgr("90");
    Serial.printf_P(PSTR("PROBE:  "));
    print_mac(ci.station, stale ? "90" : NULL);
    Serial.printf_P(PSTR(" ==> "));
    Serial.printf_P(PSTR("[%32s]  "), ci.ssid);
    print_mac(ci.bssid, stale ? "90" : NULL);
    Serial.printf_P(PSTR(" %3d"), ci.channel);
    Serial.printf_P(PSTR("   %d"), (now - ci.last_heard));
    Serial.printf_P(PSTR("   %d"), (ci.reported));
    Serial.printf_P(PSTR("   %4d"), ci.rssi);
    if (stale) vt_color_reset();
    Serial.println();
  }
};

// NEU 2.30.24: Punkt 2.1/2.2 - gibt einen einzelnen, gegen die Filterkriterien
// getroffenen Rahmen formatiert aus (Option A/C aus der Absprache: TA -> RA,
// SSID wo zuverlaessig lokalisierbar, Kanal, RSSI). "label" ist bereits der
// fertige Klartextname (aus ie_frame_subtype_name() oder den Sonderfaellen
// Beacon/Probe Request/Probe Response).
void print_filtered_frame(uint8_t *frame, uint16_t len, uint8_t frame_type, uint8_t frame_subtype,
                           uint8_t *ta, uint8_t *ra, int8_t rssi, uint8_t channel,
                           const char *label)
{
  // NEU 2.30.44: Zeitstempel-Praefix wie in Punkt 2.4 (dort "+%6lums" seit
  // Teststart) - hier seit Betreten dieses Live-Filters (filter_live_start_ms,
  // siehe menu_enter_filter_live()).
  Serial.printf_P(PSTR("+%6lums "), (unsigned long)(millis() - filter_live_start_ms));
  // NEU 2.30.28: Nutzerwunsch - Label OHNE feste Auffuell-Breite (spart auf
  // einem schmalen Handybildschirm sehr viel horizontalen Platz, siehe
  // Screenshot mit "Data" + 20 Leerzeichen bis zum ":").
  Serial.printf_P(PSTR("%s: "), label);
  for (int n = 0; n < ETH_MAC_LEN; n++) Serial.printf_P(PSTR("%02x"), ta[n]);
  Serial.print(F(" -> "));
  for (int n = 0; n < ETH_MAC_LEN; n++) Serial.printf_P(PSTR("%02x"), ra[n]);

  // SSID nur bei Beacon/Probe Request/Probe Response zuverlaessig direkt aus
  // dem Rahmen lokalisierbar (feste IE-Position, siehe print_pkt_header()
  // oben - bewusst NICHT auf weitere Subtypen wie Association Request
  // ausgeweitet, da deren vorangehende Festfelder eine andere Laenge haben
  // und hier noch nicht recherchiert/getestet wurden).
  // BUGFIX 2.30.27: zusaetzlich frame_type==0 verlangen, siehe dortiger
  // Kommentar (Subtyp-Zahlen ueberschneiden sich zwischen den Frametypen).
  // BUGFIX 2.30.31: Nutzer meldete kryptische Zeichen wie "[0H`l]" statt der
  // echten SSID. Ursache: die Positionswerte 37/49 sind bei print_pkt_
  // header() auf den KOMPLETTEN Rohpuffer INKLUSIVE der 12 Byte langen
  // RxControl-Kopfzeile kalibriert (12 RxControl + 24 MAC-Header + 1 = 37
  // fuer Probe Request; +12 Beacon/ProbeResp-Fixfelder = 49). Hierher
  // (print_filtered_frame()) kommt aber "frame" = sniffer->buf, das schon
  // OHNE die 12 RxControl-Byte beginnt (Frame Control direkt @ frame+0) -
  // die uebernommenen Positionswerte lasen dadurch 12 Byte zu weit und
  // landeten mitten in nachfolgenden IEs (z.B. Supported Rates) statt in
  // der SSID. Fix: um die 12 Byte RxControl-Versatz korrigiert (25/37).
  if (frame_type == 0 && (frame_subtype == 4 || frame_subtype == 5 || frame_subtype == 8)) {
    int pos = (frame_subtype == 4) ? 25 : 37;
    if (len > (uint16_t)(pos + 1)) {
      int ssid_len = (int) frame[pos];
      if (ssid_len >= 0 && ssid_len <= 32 && (uint16_t)(pos + 1 + ssid_len) <= len) {
        if (ssid_len == 0) {
          Serial.print(F(" [offen/versteckt]"));
        } else {
          char ssid_name[33];
          memset(ssid_name, '\x00', 33);
          memcpy(ssid_name, &frame[pos + 1], ssid_len);
          Serial.printf_P(PSTR(" [%s]"), ssid_name);
        }
      }
    }
  } else {
    // NEU 2.30.28: Nutzerwunsch - bei allen anderen Frametypen (insbesondere
    // Punkt 2 mit Data/Action/Null etc.) traegt der Rahmen selbst keine SSID.
    // Stattdessen im bereits vorhandenen AP-Cache nachschlagen (TA oder RA
    // als BSSID) - so bleibt trotzdem erkennbar, MIT WELCHEM Netz da
    // kommuniziert wird. Bewusst in Kauf genommen, dass das Format dadurch
    // laenger wird (ausdruecklicher Nutzerwunsch trotz Handybildschirm).
    int ap_idx = find_ap_index_by_bssid(ta);
    if (ap_idx < 0) ap_idx = find_ap_index_by_bssid(ra);
    if (ap_idx >= 0 && aps_known[ap_idx].ssid[0] != '\0') {
      Serial.printf_P(PSTR(" [%s]"), aps_known[ap_idx].ssid);
    }
  }

  // NEU 2.30.28: Nutzerwunsch - Einheit "dBm" entfaellt, der (immer negative)
  // Zahlenwert ist als Signalstaerke selbsterklaerend.
  Serial.printf_P(PSTR("  Ch%2d  %4d\r\n"), channel, rssi);
}

// NEU 2.30.28: Klartextnamen fuer die Category-/Action-Bytes eines Action-
// Frames (Management-Subtyp 13). Liegen direkt hinter dem 24-Byte-MAC-Header
// (Category @ frame+24, Action @ frame+25) - stehen also schon im ohnehin
// bereits eingelesenen Management-Puffer, kein zusaetzlicher Erfassungs-
// aufwand. Kategorien-Tabelle per IEEE 802.11 recherchiert und verifiziert.
// RAM-FIX 2.30.29: strcpy_P()-Muster statt roher String-Literale, siehe
// ausfuehrlicher Kommentar bei ie_frame_subtype_name() oben.
const char* action_category_name(uint8_t cat)
{
  static char buf[27];  // laengster Eintrag "Vendor Specific Protected" = 26 Zeichen
  switch (cat) {
    case 0: strcpy_P(buf, PSTR("Spectrum Mgmt")); break;
    case 1: strcpy_P(buf, PSTR("QoS")); break;
    case 2: strcpy_P(buf, PSTR("DLS")); break;
    case 3: strcpy_P(buf, PSTR("Block Ack")); break;
    case 4: strcpy_P(buf, PSTR("Public")); break;
    case 5: strcpy_P(buf, PSTR("Radio Measurement")); break;
    case 6: strcpy_P(buf, PSTR("Fast BSS Transition")); break;
    case 7: strcpy_P(buf, PSTR("HT")); break;
    case 8: strcpy_P(buf, PSTR("SA Query")); break;
    case 9: strcpy_P(buf, PSTR("Protected Dual Public")); break;
    case 10: strcpy_P(buf, PSTR("WNM")); break;
    case 11: strcpy_P(buf, PSTR("Unprotected WNM")); break;
    case 12: strcpy_P(buf, PSTR("TDLS")); break;
    case 13: strcpy_P(buf, PSTR("Mesh")); break;
    case 14: strcpy_P(buf, PSTR("Multihop")); break;
    case 15: strcpy_P(buf, PSTR("Self-Protected")); break;
    case 17: strcpy_P(buf, PSTR("DMG")); break;
    case 18: strcpy_P(buf, PSTR("Fast Session Transfer")); break;
    case 20: strcpy_P(buf, PSTR("Unprotected DMG")); break;
    case 21: strcpy_P(buf, PSTR("VHT")); break;
    case 126: strcpy_P(buf, PSTR("Vendor Specific Protected")); break;
    case 127: strcpy_P(buf, PSTR("Vendor Specific")); break;
    default: strcpy_P(buf, PSTR("Reserved")); break;
  }
  return buf;
}

// Liefert den Action-Namen NUR fuer die Kategorien, die bei einem
// gewoehnlichen WLAN-Client realistischerweise vorkommen (siehe Absprache) -
// aktuell Block Ack, da das der Hauptverdaechtige fuer "chattende" Geraete
// ist. NULL = kein bekannter Name, dann bleibt es beim reinen Kategorienamen.
// RAM-FIX 2.30.29: eigener statischer Puffer (siehe ie_frame_subtype_name()),
// bewusst GETRENNT vom Puffer in action_category_name() - beide Rueckgaben
// werden gemeinsam in einem snprintf() verwendet (siehe apply_live_filter()),
// ein gemeinsamer Puffer wuerde sich dabei selbst ueberschreiben.
const char* action_specific_name(uint8_t cat, uint8_t act)
{
  static char buf[16];  // laengster Eintrag "ADDBA Response" = 14 Zeichen
  if (cat == 3) {  // Block Ack
    switch (act) {
      case 0: strcpy_P(buf, PSTR("ADDBA Request")); return buf;
      case 1: strcpy_P(buf, PSTR("ADDBA Response")); return buf;
      case 2: strcpy_P(buf, PSTR("DELBA")); return buf;
      default: return NULL;
    }
  }
  return NULL;
}

// NEU 2.30.24: Punkt 2.1/2.2 - prueft einen eintreffenden Rohrahmen gegen die
// aktuell eingestellten Filterkriterien (filter_*, siehe Deklaration weiter
// oben) und gibt ihn bei Treffer sofort aus. Wird von promisc_cb() nur
// aufgerufen, wenn menu_state == STATE_FILTER_LIVE ist (billige Pruefung
// liegt beim jeweiligen Aufrufer, siehe dort). "frame" zeigt auf den Beginn
// des 802.11-MAC-Headers (Frame Control @ frame+0/+1, wie auch bei
// parse_data() weiter oben).
void apply_live_filter(uint8_t *frame, uint16_t len, int8_t rssi, uint8_t channel)
{
  // NEU 2.30.28 BUGFIX: Bei sehr hoher Paketrate (z.B. aktivierte Daten-
  // rahmen) kann promisc_cb() so dicht aufeinanderfolgend aufgerufen werden,
  // dass loop() (und damit menu_handle_serial()) kaum noch zum Zug kommt -
  // Backspace/ESC/Strg+O liefen dadurch ins Leere, die Ausgabe liess sich
  // nicht mehr stoppen (Nutzer-Meldung). Fix: hier, wo ohnehin JEDES
  // verarbeitete Paket durchlaeuft, selbst und sofort nach Eingaben schauen,
  // statt auf loop() zu warten - genau die Stelle, die bei einer Paketflut
  // am haeufigsten laeuft.
  if (Serial.available() > 0) {
    int k = Serial.peek();
    if (k == 8 || k == 127 || k == 27) {   // Backspace/DEL/ESC
      Serial.read();
      // BUGFIX 2.30.30: fehlte hier - dieser Schnellweg umging beim Verlassen
      // waehrend einer Paketflut komplett die Kanal-Lock-Wiederherstellung
      // (die sonst nur in menu_go_back() bzw. im ESC-Handler in menu_handle_
      // serial() aufgerufen wird, hier aber nie erreicht wird, weil der
      // Tastendruck schon hier per Serial.read() konsumiert wird). channel_
      // filter blieb dadurch dauerhaft auf den gesperrten Einzelkanal
      // gesetzt (Nutzer-Meldung).
      filter_channel_unlock_if_active();
      menu_enter_filter_criteria();
      return;
    } else if (k == 15) {                  // Strg+O - Online/Offline umschalten
      Serial.read();
      toggle_online_mode();
      refresh_current_screen();
      return;
    }
  }

  uint8_t frame_type = (frame[0] & 0x0C) >> 2;
  uint8_t frame_subtype = (frame[0] & 0xF0) >> 4;

  // Adresse 2 ist nach 802.11-Standard IMMER die Sendestation (Transmitter
  // Address), Adresse 1 IMMER die Empfangsstation (Receiver Address) -
  // unabhaengig von ToDS/FromDS und unabhaengig davon, ob es sich um einen
  // Management-, Control- oder Datenrahmen handelt (einzige Einschraenkung:
  // reine Empfangsbestaetigungen wie ACK/CTS haben laut Standard gar keine
  // TA - die dort ohnehin bedeutungslosen Fuellbytes an dieser Position
  // schaden hier nicht, sie matchen dann einfach nie als "abgehend").
  uint8_t *ta = frame + 10;
  uint8_t *ra = frame + 4;

  // 1) MAC-Filter (Punkt 2.1) inkl. Richtung. Laut Absprache: MAC-Treffer in
  // JEDER Adressposition zulassen, "insofern nicht ueber die Richtungsauswahl
  // eingeschraenkt" - da TA/RA bereits rollenunabhaengig (AP oder Client)
  // sind, deckt der TA/RA-Vergleich das ab, ohne Adresse 3 (BSSID) separat
  // pruefen zu muessen (bei Infrastruktur-Rahmen ist TA ohnehin praktisch
  // immer identisch mit der BSSID, wenn der Sender die AP selbst ist).
  if (filter_has_mac) {
    bool out_match = filter_dir_out && (! memcmp(ta, filter_mac, ETH_MAC_LEN));
    bool in_match  = filter_dir_in  && (! memcmp(ra, filter_mac, ETH_MAC_LEN));
    if (! out_match && ! in_match) return;
  }

  // 2) Pakettyp-Filter (Punkt 2.1 UND 2.2 gemeinsam). Beacon/Probe Request/
  // Probe Response haben eigene, uebergeordnete Checkboxen (siehe Kommentar
  // bei den filter_*-Deklarationen) - die Management-Maske deckt bewusst
  // NUR die uebrigen Subtypen ab, daher keine Ueberschneidung/Doppeltreffer.
  bool match = false;
  const char *label = NULL;
  if (frame_type == 0 && frame_subtype == 8 && filter_sel_beacon) {
    match = true; label = "Beacon";
  } else if (frame_type == 0 && frame_subtype == 4 && filter_sel_probe_req) {
    match = true; label = "Probe Request";
  } else if (frame_type == 0 && frame_subtype == 5 && filter_sel_probe_resp) {
    match = true; label = "Probe Response";
  } else if (frame_type == 0 && (filter_mgmt_mask & ((uint16_t)1 << frame_subtype))) {
    match = true; label = ie_frame_subtype_name(0, frame_subtype);
  } else if (frame_type == 1 && (filter_ctrl_mask & ((uint16_t)1 << frame_subtype))) {
    match = true; label = ie_frame_subtype_name(1, frame_subtype);
  } else if (frame_type == 2 && (filter_data_mask & ((uint16_t)1 << frame_subtype))) {
    match = true; label = ie_frame_subtype_name(2, frame_subtype);
  }
  if (! match) return;

  // NEU 2.30.28: Action-Frames (Management-Subtyp 13) zusaetzlich nach
  // Category/Action aufschluesseln (siehe action_category_name()/
  // action_specific_name() oben) - macht z.B. sichtbar, ob es sich um eine
  // Block-Ack-Aushandlung (ADDBA/DELBA) handelt statt nur "Action" pauschal.
  char action_label_buf[40];
  if (frame_type == 0 && frame_subtype == 13 && len > 25) {
    uint8_t cat = frame[24];
    uint8_t act = frame[25];
    const char *catname = action_category_name(cat);
    const char *actname = action_specific_name(cat, act);
    if (actname != NULL) {
      snprintf_P(action_label_buf, sizeof(action_label_buf), PSTR("Action (%s: %s)"), catname, actname);
    } else {
      snprintf_P(action_label_buf, sizeof(action_label_buf), PSTR("Action (%s)"), catname);
    }
    label = action_label_buf;
  }

  print_filtered_frame(frame, len, frame_type, frame_subtype, ta, ra, rssi, channel, label);
}

// NEU 2.30.32: Punkt 2.4 Diagnose - siehe ausfuehrlichen Kommentar bei den
// timing_test_*-Variablen weiter oben. Bewusst KEIN Aufruf gemeinsamer
// Hilfsfunktionen mit dem Rest des Programms (kein find_ap_index_by_bssid(),
// kein AP-Cache-Nachschlag, kein ie_frame_subtype_name() waehrend der
// Messung) - Adressen/Struct-Layout hier bewusst eigenstaendig dupliziert,
// damit diese Routine wirklich von nichts anderem im Programm beeinflusst
// werden kann. Einzige Ausnahme: der Serial.available()-Check fuer einen
// vorzeitigen Abbruch per Backspace/ESC (siehe Ruecksprache - explizit
// gewuenscht, minimaler Overhead).
void timing_test_process_packet(uint8_t *buf, uint16_t len)
{
  if (Serial.available() > 0) {
    int k = Serial.peek();
    if (k == 8 || k == 127 || k == 27) {
      Serial.read();
      timing_test_finish();
      return;
    }
  }

  if (millis() - timing_test_start_ms >= timing_test_duration_s * 1000UL) {
    timing_test_finish();
    return;
  }

  uint8_t *frame;
  if (len == 128) {
    struct sniffer_buf2 *sniffer = (struct sniffer_buf2*) buf;
    frame = sniffer->buf;
  } else if (len >= 48) {
    struct sniffer_buf *sniffer = (struct sniffer_buf*) buf;
    frame = sniffer->buf;
  } else {
    return;  // len==12: reines RxControl, keine Adressen auswertbar
  }

  uint8_t *ta = frame + 10;  // Adresse 2 - immer die Sendestation
  uint8_t *ra = frame + 4;   // Adresse 1 - immer die Empfangsstation
  bool ta_match = (! memcmp(ta, timing_test_mac, ETH_MAC_LEN));
  bool ra_match = (! memcmp(ra, timing_test_mac, ETH_MAC_LEN));
  if (! ta_match && ! ra_match) return;

  if (timing_test_count < TIMING_TEST_MAX_ENTRIES) {
    struct sniffer_buf *generic = (struct sniffer_buf*) buf;  // RxControl-Layout ist bei beiden Struct-Varianten identisch
    timing_test_log[timing_test_count].t_ms = millis() - timing_test_start_ms;
    timing_test_log[timing_test_count].role = (ta_match ? 1 : 0) | (ra_match ? 2 : 0);
    timing_test_log[timing_test_count].fc_byte = frame[0];
    timing_test_log[timing_test_count].rssi = generic->rx_ctrl.rssi;
    timing_test_log[timing_test_count].channel = generic->rx_ctrl.channel;
    timing_test_count++;
  }
}

void promisc_cb(uint8_t *buf, uint16_t len)
{
  // NEU 2.30.32: greift VOR dem online_mode-Guard - der Test soll auch dann
  // funktionieren, wenn die normale Aufzeichnung gerade pausiert ist.
  if (timing_test_active) {
    timing_test_process_packet(buf, len);
    return;
  }

  if (!online_mode) return;  // Einstellungen: Offline = Listen einfrieren

  // NEU 2.30.37: eigener Wurzel-Messpunkt fuer den Promiscuous-Callback-
  // Kontext (CTX_PROMISC) - alles was ab hier in diesem Durchlauf synchron
  // aufgerufen wird (parse_beacon/register_beacon bzw. parse_data/
  // register_client) haengt an DIESER Kette, niemals an einer zufaellig im
  // Hauptprogramm zum selben Zeitpunkt aktiven Kette (Vorgabe Pkt.5).
  CallChainGuard __cc_guard_callback(RDP_PROMISC_CALLBACK, CTX_PROMISC);

  // NEU 2.30.59: Age-Touch. Addr2 (buf+22) ist bei jedem 802.11-Frame mit
  // ausreichender Laenge die Sendestation (TA). Ist sie eine bereits
  // bekannte Client-MAC, wird deren last_heard aktualisiert - unabhaengig
  // vom Frame-Typ. Kein neuer Eintrag: der Lookup laeuft nur ueber
  // bestehende clients_known[]-Eintraege. Der AP selbst und fremde Geraete
  // stehen dort nicht, ihre Frames loesen daher nichts aus.
  if (len >= 28) {
    uint32_t n = millis() / 1000;
    for (int u = 0; u < clients_known_count; u++) {
      if (!memcmp(clients_known[u].station, buf + 22, 6)) {
        clients_known[u].last_heard = n;
        break;
      }
    }
  }

  if (len == 12) {
    struct RxControl *sniffer = (struct RxControl*) buf;
  } else if (len == 128) {
    uint8_t frame_control_pkt = buf[12];
    uint8_t frame_type = (frame_control_pkt & 0x0C) >> 2;
    uint8_t frame_subtype = (frame_control_pkt & 0xF0) >> 4;
    struct sniffer_buf2 *sniffer = (struct sniffer_buf2*) buf;
    // NEU 2.30.42: Detailstatistik fuer den ausgewaehlten Client.
    traffic_detail_record(sniffer->buf, sniffer_frame_length(sniffer->rx_ctrl), frame_type, frame_subtype);
    // NEU 2.30.24: Punkt 2.1/2.2 Live-Filter - unabhaengig von der uebrigen
    // Verarbeitung dieses Zweigs (Beacon-/Probe-Registrierung, Client-Frame-
    // Analyse), billige Pruefung (nur ein Enum-Vergleich) fuer den Normalfall.
    if (menu_state == STATE_FILTER_LIVE) apply_live_filter(sniffer->buf, 112, sniffer->rx_ctrl.rssi, sniffer->rx_ctrl.channel);
    // NEU 2.30.8: Client-Frame-Analyse (Menue 3a, "w"+Zahl) - wartet auf das
    // NAECHSTE Paket JEDER Art des gewaehlten Clients, nicht mehr nur auf
    // Probe Requests (siehe Kommentar bei den client_capture_*-Variablen
    // oben). Fuer alle Management-Frames (frame_type==0, dieser 128-Byte-
    // Zweig) steht die Sender-MAC IMMER an Adresse 2 (Byte 10), unabhaengig
    // vom Subtyp - deshalb hier EIN gemeinsamer Match-Block fuer den
    // gesamten Zweig, statt wie zuvor nur innerhalb des Probe-Request-Falls.
    // Schnell (nur memcmp+memcpy, kein Print/Delay) - unbedenklich im
    // zeitkritischen Callback, analog zu register_beacon()/register_client().
    if (frame_type == 0 && client_capture_armed && !client_capture_done && client_capture_buf != NULL) {
      if (! memcmp(sniffer->buf + 10, client_capture_target_station, ETH_MAC_LEN)) {
        memcpy(client_capture_buf, sniffer->buf, 112);
        client_capture_buf_capacity = 112;
        client_capture_reallen = sniffer_frame_length(sniffer->rx_ctrl);  // BUGFIX 2.30.13: legacy_length allein reicht nicht (HT-Frames)
        client_capture_rssi = sniffer->rx_ctrl.rssi;
        client_capture_done = true;
        client_capture_armed = false;
      }
    }
    if (frame_type == 0 && (frame_subtype == 8 || frame_subtype == 5))
      {
        ram_debug_sample(RDP_AP_CAPTURE);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
        CallChainGuard __cc_guard(RDP_AP_CAPTURE, CTX_PROMISC);  // NEU 2.30.37: eigener Kontext (Promiscuous Callback), keine Vermischung mit Hauptprogramm-Kette
        struct beaconinfo beacon = parse_beacon(sniffer->buf, 112, sniffer->rx_ctrl.rssi);
        if (register_beacon(beacon) == 0)
        {
          if (live_output_active()) print_beacon(beacon);
          nothing_new = 0;
        };
        // NEU 2.29.17: Beacon-Frame-Analyse (Punkt 3, "w"+Zahl) - nur echte
        // Beacons (subtype 8), keine Probe-Responses (subtype 5). Schnell
        // (nur memcmp+memcpy, kein Print/Delay) - unbedenklich hier im
        // zeitkritischen Callback, analog zu register_beacon()/register_client().
        if (frame_subtype == 8 && beacon_capture_armed && !beacon_capture_done && beacon_capture_buf != NULL) {
          if (! memcmp(sniffer->buf + 10, beacon_capture_target_bssid, ETH_MAC_LEN)) {
            memcpy(beacon_capture_buf, sniffer->buf, 112);
            beacon_capture_reallen = sniffer_frame_length(sniffer->rx_ctrl);  // BUGFIX 2.30.13: legacy_length allein reicht nicht (HT-Frames)
            beacon_capture_rssi = sniffer->rx_ctrl.rssi;
            beacon_capture_done = true;
            beacon_capture_armed = false;
          }
        }
        // NEU 2.30.46: Beacon-FrameTrap jetzt ueber die Watchlist (wie beim
        // Client-FrameTrap oben bei den Probe Requests) - nur memcmp/memcpy
        // hier (sys-Kontext), keine Watchlist-Aenderung/Datei-I/O.
        if (frame_subtype == 8) {
          for (int wi = 0; wi < watchlist_count; wi++) {
            if (! watchlist_entry_is_beacon_trapped(wi)) continue;
            if (memcmp(sniffer->buf + 10, watchlist[wi].mac, ETH_MAC_LEN)) continue;
            bool already_pending = false;
            int free_slot = -1;
            for (int s = 0; s < FRAMETRAP_BEACON_MAX_PENDING; s++) {
              if (frametrap_beacon_catches[s].buf != NULL) {
                if (! memcmp(frametrap_beacon_catches[s].bssid, watchlist[wi].mac, ETH_MAC_LEN)) { already_pending = true; break; }
              } else if (free_slot < 0) {
                free_slot = s;
              }
            }
            if (already_pending || free_slot < 0) break;
            uint8_t *cbuf = (uint8_t*) malloc(112);
            if (cbuf == NULL) break;
            memcpy(cbuf, sniffer->buf, 112);
            memcpy(frametrap_beacon_catches[free_slot].bssid, watchlist[wi].mac, ETH_MAC_LEN);
            frametrap_beacon_catches[free_slot].buf = cbuf;
            frametrap_beacon_catches[free_slot].reallen = sniffer_frame_length(sniffer->rx_ctrl);
            frametrap_beacon_catches[free_slot].rssi = sniffer->rx_ctrl.rssi;
            break;  // diese eine Watchlist-Uebereinstimmung reicht, BSSID ist eindeutig
          }
        }
      } else if (frame_type ==0 && frame_subtype==4) {
        struct probeinfo probe = parse_probe(sniffer->buf, 112, sniffer->rx_ctrl.rssi);
        // Schritt 1: Probes werden nur noch live ausgegeben, nicht gespeichert
        if (live_output_active()) print_probe(probe);
        nothing_new = 0;
        // NEU 2.30.11: "Mausefalle" - nur memcmp/memcpy hier (sys-Kontext,
        // siehe Kommentar bei den Mousetrap-Deklarationen), keine Watchlist-
        // Aenderung/Datei-I/O. Quell-MAC (Byte 10, wie bei der uebrigen
        // Client-Erfassung) gegen alle scharfen Watchlist-Eintraege pruefen;
        // bei Treffer in einen freien Puffer-Slot kopieren, falls fuer
        // diese MAC nicht schon ein unverarbeiteter Fang wartet.
        for (int wi = 0; wi < watchlist_count; wi++) {
          if (! watchlist_entry_is_trapped(wi)) continue;
          if (memcmp(sniffer->buf + 10, watchlist[wi].mac, ETH_MAC_LEN)) continue;
          bool already_pending = false;
          int free_slot = -1;
          for (int s = 0; s < FRAMETRAP_CLIENT_MAX_PENDING; s++) {
            if (frametrap_client_catches[s].buf != NULL) {
              if (! memcmp(frametrap_client_catches[s].station, watchlist[wi].mac, ETH_MAC_LEN)) { already_pending = true; break; }
            } else if (free_slot < 0) {
              free_slot = s;
            }
          }
          if (already_pending || free_slot < 0) break;
          uint8_t *cbuf = (uint8_t*) malloc(112);
          if (cbuf == NULL) break;
          memcpy(cbuf, sniffer->buf, 112);
          memcpy(frametrap_client_catches[free_slot].station, watchlist[wi].mac, ETH_MAC_LEN);
          frametrap_client_catches[free_slot].buf = cbuf;
          frametrap_client_catches[free_slot].reallen = sniffer_frame_length(sniffer->rx_ctrl);  // BUGFIX 2.30.13: legacy_length allein reicht nicht (HT-Frames)
          frametrap_client_catches[free_slot].rssi = sniffer->rx_ctrl.rssi;
          break;  // diese eine Watchlist-Uebereinstimmung reicht, MAC ist eindeutig
        }
      };
  } else {
    // Bugfix (seit 2.5.0 kritisch, siehe Changelog Client-Roaming):
    // Bisher wurde JEDES Paket, dessen Laenge weder 12 noch 128 war,
    // ungeprueft als Client-Datenpaket interpretiert. Mesh-Management-
    // bzw. Action-Frames (frame_type==0) fremder Access Points haben
    // praktisch nie exakt 128 Byte und landeten deshalb hier - ihre
    // Nutzdaten wurden faelschlich als station/bssid-MAC gelesen.
    // Seit die Client-Erkennung ueber Station+BSSID matcht (2.5.0),
    // erzeugt das bei jedem Paket einen neuen Eintrag und laeuft die
    // Liste in Sekunden voll.
    // Fix: genau wie im len==128-Zweig den echten frame_type aus dem
    // Frame-Control-Byte pruefen - nur echte Data-Frames (Typ 2)
    // duerfen ueberhaupt als Client registriert werden.
    if (len < 48) {
      // zu kurz, um sicher als sniffer_buf geparst zu werden
      return;
    }
    struct sniffer_buf *sniffer = (struct sniffer_buf*) buf;
    uint8_t frame_control_pkt = buf[12];
    uint8_t frame_type = (frame_control_pkt & 0x0C) >> 2;
    uint8_t frame_subtype = (frame_control_pkt & 0xF0) >> 4;
    // NEU 2.30.42: Detailstatistik fuer alle im variablen SDK-Pfad
    // ankommenden Frame-Typen. Der Match betrachtet nur Header-Adressen.
    traffic_detail_record(sniffer->buf, (uint16_t)(len - 12), frame_type, frame_subtype);
    // NEU 2.30.24: Punkt 2.1/2.2 Live-Filter - bewusst VOR dem
    // "frame_type != 2 -> return"-Sprung unten platziert, sonst waeren
    // Control-Rahmen (RTS/CTS/ACK/PS-Poll/...), die genau wie Datenrahmen
    // in diesem "sonstige Laenge"-Zweig ankommen, fuer den Filter unsichtbar.
    if (menu_state == STATE_FILTER_LIVE) apply_live_filter(sniffer->buf, len - 12, sniffer->rx_ctrl.rssi, sniffer->rx_ctrl.channel);
    if (frame_type != 2) {
      return;
    }
    uint8_t raw_bssid[ETH_MAC_LEN];
    struct clientinfo ci = parse_data(sniffer->buf, 36, sniffer->rx_ctrl.rssi, sniffer->rx_ctrl.channel, raw_bssid);
    // NEU 2.30.8: Client-Frame-Analyse (Menue 3a, "w"+Zahl) - Match auf die
    // schon oben berechnete ci.station (dieselbe ToDS/FromDS-abhaengige
    // Adresslogik wie die normale Client-Erkennung, siehe parse_data()) -
    // stellt sicher, dass exakt das gleiche Geraet erkannt wird wie in der
    // Geraeteliste. Nur 36 statt 112 Byte Kapazitaet, da das SDK fuer
    // Datenframes von vornherein nur einen kleineren Puffer liefert.
    if (client_capture_armed && !client_capture_done && client_capture_buf != NULL) {
      if (! memcmp(ci.station, client_capture_target_station, ETH_MAC_LEN)) {
        memcpy(client_capture_buf, sniffer->buf, 36);
        client_capture_buf_capacity = 36;
        client_capture_reallen = sniffer_frame_length(sniffer->rx_ctrl);  // BUGFIX 2.30.13: legacy_length allein reicht nicht (HT-Frames)
        client_capture_rssi = sniffer->rx_ctrl.rssi;
        client_capture_done = true;
        client_capture_armed = false;
      }
    }
    // NEU 2.29.11 (Etappe 3): BSSID wird nicht mehr im Client gespeichert,
    // nur noch der Index in aps_known[]. NEU 2.29.16: kein Platzhalter mehr
    // fuer noch unbekannte BSSIDs (siehe Kommentar bei find_ap_index_by_bssid-
    // Prototyp) - einfach AP_IDX_NONE ("??"), bis der AP ganz regulaer ueber
    // seinen eigenen Beacon entdeckt wird (register_beacon()). Eine
    // ungueltige BSSID (all-null/Multicast, z.B. aus einem fehlerhaft
    // geparsten Frame) bekommt ebenfalls AP_IDX_NONE.
    int found_idx = is_valid_ap_bssid(raw_bssid) ? find_ap_index_by_bssid(raw_bssid) : -1;
    ci.ap_idx = (found_idx >= 0) ? (uint8_t) found_idx : AP_IDX_NONE;
    ram_debug_sample(RDP_CLIENT_CAPTURE);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
    CallChainGuard __cc_guard(RDP_CLIENT_CAPTURE, CTX_PROMISC);  // NEU 2.30.37: eigener Kontext (Promiscuous Callback), keine Vermischung mit Hauptprogramm-Kette
    int registered_client_idx = -1;
    int client_known_result = register_client(ci, &registered_client_idx);
    // NEU 2.30.39: Auftrag 1 nutzt exakt das Ergebnis der vorhandenen
    // Client-Registrierung; keine zweite clients_known[]-Suche im Callback.
    if (traffic_stats_active && traffic_stats_ap_included(ci.ap_idx)) {
      uint8_t ds = sniffer->buf[1] & 0x03;
      if (ds == 1 || ds == 2) {
        bool is_tx = (ds == 1);
        traffic_stats_record(ci.ap_idx, registered_client_idx, ci.station, sniffer_frame_length(sniffer->rx_ctrl), is_tx);
      }
    }
    if (client_known_result == 0) {
      if (live_output_active()) print_client(ci);
      nothing_new = 0;
    }
  }
}

// =====================================================================
// Menue-System (VT100), reduzierte Testversion
// =====================================================================

// (menu_state selbst ist bereits weiter oben, direkt nach dem enum
// MenuState, deklariert - siehe dortigen Kommentar.)
int ssid_select_cursor_count = 0;    // Anzahl waehlbarer APs beim letzten Zeichnen
char ssid_input_buf[20];             // Eingabepuffer fuer Zahleneingabe (SSID-Auswahl) - vergrößert für Kommas
bool ssid_select_combined = false;   // 'S'-Praefix wurde vor der Zahl eingegeben (Punkt 3a)
int ssid_input_len = 0;
// NEU 2.17.5: 'd'-Praefix wurde vor der Zahl eingegeben (Punkt 3, gezielt
// einen einzelnen AP aus der Hauptliste loeschen, analog zu Punkt 6/Datei-Loeschen)
bool ssid_select_delete_mode = false;
// NEU 2.29.17: 'w'-Praefix wurde vor der Zahl eingegeben (Punkt 3,
// Beacon-Frame-Rohanalyse des gewaehlten APs)
bool ssid_select_analyze_mode = false;

// NEU 2.12.0: Modus-Verfolgung für Punkt 3b (Anzeigeliste)
//   1 = einzelner AP (nur Clients dieses APs)
//   2 = SSID-Bündelung (alle APs mit gleicher SSID)
//   3 = Multi-AP (kommagetrennte APs, z.B. s1,5,7)
int current_list_mode = 0;
int current_list_ap_index = -1;      // für Mode 1: welcher AP wird angezeigt
char ssid_list_combined_ssid[33] = ""; // für Mode 2: die betroffene SSID

bool ssid_list_combined = false;         // DEPRECATED aber behalten für Kompatibilität
uint32_t last_list_refresh_time = 0; // fuer Auto-Refresh

// NEU 2.17.2: Ignore-Filter (Taste 'i'), nur relevant fuer Modus 2 (S5) und
// Modus 3 (S<n,n,...>). Blendet Clients aus, die den AP gewechselt haben
// (">n") oder "out" sind - rein visuell, clients_known bleibt unveraendert.
bool list_hide_inactive = false;
int list_refresh_sec = 10;   // NEU 2.30.14: Standard jetzt 10s (einheitlich); einstellbar per Taste + (+5s) / - (-5s), Minimum 5s

// NEU 2.27.4: Auto-Refresh fuer Menue 3 (SSID-/AP-Uebersicht). Eigene
// Variablen statt Wiederverwendung von list_refresh_sec/last_list_refresh_time,
// da Menue 3 ein eigenstaendiger Zustand (STATE_SSID_SELECT) ist, unabhaengig
// von Menue 3a/3b (STATE_SSID_LIST). Einstellbar per Taste +/- statt u/d,
// da u/d in Menue 3 bereits belegt sind (u=unsortiert, d=Loeschmodus).
int ssid_select_refresh_sec = 10;  // NEU 2.30.14: Standard jetzt 10s (einheitlich)
uint32_t last_ssid_select_refresh_time = 0;

SortField current_sort_field = SORT_MAC;
bool sort_ascending = true;          // Bedeutung haengt vom Feld ab, siehe default_ascending_for()

// NEU 2.17.4: Sortierzustand fuer die AP-Uebersichtsliste (Liste 3)
ApSortField current_ap_sort_field = AP_SORT_NONE;
bool ap_sort_ascending = true;

int rssi_trend_threshold = 10;       // dB, einstellbar (Taste 't')

// Zweispaltige Darstellung: 0 = immer einspaltig. Getrennte Werte, da
// die Zeilenbreite in Punkt 3 (Geraeteliste) und Punkt 3a (SSID-Liste)
// unterschiedlich ist.
int two_col_threshold_devices = 30;
int two_col_threshold_ssids = 40;

bool settings_input_active = false;
int settings_input_target = 0;  // 3 = Geraeteliste, 4 = SSID-Liste
char settings_input_buf[6];
int settings_input_len = 0;
bool threshold_input_active = false;
char threshold_input_buf[4];
int threshold_input_len = 0;

// NEU 2.17.5: Punkt m - alte Eintraege (Clients/APs) nach Alter loeschen.
// Ablauf: erst Alter in Sekunden eingeben (cleanup_age_phase=true), dann
// Tastendruck c/a/b fuer den Umfang (cleanup_age_phase=false).
bool cleanup_age_phase = true;
char cleanup_input_buf[8];
int cleanup_input_len = 0;
int cleanup_age_threshold = 0;

// STALE_AGE_SEC und color_enabled sind bereits am Dateianfang definiert
// (werden schon in print_client()/print_beacon()/print_probe() benoetigt)

char save_filename_buf[25];
int save_filename_len = 0;

// NEU 2.17.9: RAM-Opt: [16][32]=512 → [12][28]=336 Byte, spart 176 Byte
char file_list_names[32][32];  // NEU 2.22.0: 12 → 20 Dateien (kostet zusaetzliches RAM, gewuenscht); [32] fuer 24-char-Namen + ".txt" + Null-Terminator
uint8_t file_list_count = 0;  // NEU 2.17.9: RAM-Optimierung
char file_input_buf[6];
int file_input_len = 0;
bool file_delete_mode = false;
bool file_load_mode = false;
bool file_send_mode = false;
bool file_view_waiting = false;

// ===================== NTP-Zeitsynchronisation =====================
bool ntp_enabled = false;
char ntp_wifi_ssid[33] = "";
char ntp_wifi_pass[65] = "";
char ntp_server[65] = "pool.ntp.org";

// (Alle anderen NTP-Variablen sind jetzt oben bei den globalen Variablen - nicht mehr hier wiederholen!)

// ===================== Watchlist-UI-Zustand (Punkt 4) =====================
// watchlist[]/watchlist_count/is_watched_mac()/print_mac() sind bereits
// weiter oben definiert (werden schon in print_client() etc. gebraucht).
int watchlist_refresh_sec = 10;       // NEU 2.30.14: Standard jetzt 10s (einheitlich); einstellbar per Taste u (+5s) / d (-5s)
uint32_t last_watchlist_refresh_time = 0;

bool watch_delete_mode = false;       // Taste 'x' gedrueckt, wartet auf Nummer
char watch_delete_input_buf[4];
int watch_delete_input_len = 0;

char watch_mac_input_buf[13];         // Eingabe von 12 Hex-Zeichen
int watch_mac_input_len = 0;
uint8_t pending_watch_mac[ETH_MAC_LEN]; // zwischengespeichert zwischen MAC- und Beschreibungs-Eingabe

char watch_desc_input_buf[33];        // frei beschreibbares Beschreibungsfeld
int watch_desc_input_len = 0;

bool live_output_active()
{
  return (menu_state == STATE_LIVE);
}

void vt_clear_screen()
{
  Serial.write(27);       // ESC
  Serial.print(F("[2J"));    // Bildschirm loeschen
  Serial.write(27);
  Serial.print(F("[H"));     // Cursor Home
}

void vt_cursor_home()
{
  Serial.write(27);
  Serial.print(F("[H"));
}

// Setzt SGR-Codes (z.B. "32" fuer gruen, "2" fuer gedimmt, "2;31" kombiniert).
// (Definition weiter oben, vor der ersten Verwendung in print_client() etc.)

void menu_init()
{
  for (int i = 0; i < MAX_CLIENTS_TRACKED; i++) {
    prev_shown_rssi[i] = -128;   // Sentinel: "noch nie angezeigt" (int8_t minimum)
  }
  menu_state = STATE_MENU;
  // NEU 2.17.6: Bootphase der Status-LED endet hier - das Hauptmenue ist
  // jetzt erreicht.
  led_boot_phase = false;
  // NEU 2.21.0: Boot-Signal (500ms aktiv) auslösen
  signal_boot_pulse();
  menu_draw();
}

void menu_draw()
{
  ram_debug_sample(RDP_MENU);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
  CallChainGuard __cc_guard(RDP_MENU);  // NEU 2.30.35: Call-Chain-Erweiterung
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" ESP8266 WiFi-Monitor - Hauptmenue  (v%s)\r\n"), FIRMWARE_VERSION);
  Serial.println(F("======================================================="));
  // NEU 2.20.10 BUG10: print_channel_filter_warning() entfernt (wird bereits in print_offline_banner() aufgerufen!)
  Serial.println(F(" 1  Standardausgabe (Return = Liste)"));
  Serial.println(F(" 2  Funkverkehr gezielt untersuchen (Filter-Untermenue)"));
  Serial.println(F(" 3  Alle SSID mit Geräteanzahl anzeigen"));
  Serial.println(F(" 4  MAC-Adress-Watchlist"));
  Serial.println(F(" 5  Aktuelle Scanliste im Flash speichern"));
  Serial.println(F(" 6  Flashinhalt anzeigen/laden/loeschen"));
  Serial.println(F(" 7  HTTP-Datei-Server (Browser-Zugriff auf Flash)"));  // NEU 2.30.0
  Serial.println();
  Serial.println(F(" e  Einstellungen"));
  Serial.println(F(" i  Info"));
  Serial.println(F(" h  Hilfe"));
  Serial.println(F(" m  Alte Eintraege loeschen (nach Alter)"));
  Serial.println(F(" v  Versorgungsbereiche anzeigen (Roaming-Gruppen)"));  // NEU 2.30.60
  Serial.println();
  if (traffic_stats_active) {
    char durbuf[12];
    format_duration_hms((millis() - traffic_stats_started_ms) / 1000, durbuf, sizeof(durbuf));
    Serial.printf_P(PSTR(" b  Hintergrundverkehr anzeigen (%s)\r\n"), durbuf);
  }
  Serial.println();
  Serial.printf_P(PSTR(" Aktuell registriert: %d Geräte, %d Access Points\r\n"), clients_known_count, aps_known_live_count());
  // NEU 2.16.0: Auto-Load Error-Meldung anzeigen
  if (autoload_file_not_found) {
    Serial.println(F(" ⚠ Auto-load Datei wurde nicht gefunden!"));
  }
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" ESC/Backspace jederzeit zurueck."));
  Serial.println(F("======================================================="));
}

// NEU 2.17.5: Punkt m - alte Eintraege (Clients und/oder Access Points)
// aus der Hauptliste nach Alter loeschen. Zweistufiger Ablauf: erst Alter
// in Sekunden eingeben, dann den Umfang waehlen (c/a/b).
void menu_enter_cleanup()
{
  menu_state = STATE_CLEANUP;
  cleanup_age_phase = true;
  cleanup_input_len = 0;
  cleanup_input_buf[0] = '\0';
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Alte Eintraege loeschen"));
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" Aktuell registriert: %d Clients, %d Access Points\r\n"), clients_known_count, aps_known_live_count());
  Serial.println(F(" ESC/Backspace = abbrechen"));
  Serial.println(F(" 'o' = alle APs mit Status old und Geraeten 0/0 loeschen"));
  Serial.println(F("-------------------------------------------------------"));
  Serial.print(F(" Alter in Sekunden eingeben (Eintraege AELTER werden geloescht): "));
  if (offline_banner_will_print()) Serial.println();  // BUGFIX 2.30.44
}

// NEU 2.30.60: Punkt v - Versorgungsbereiche (Roaming-Gruppen). Konsumiert
// nur die kurze Paarliste aus roaming_record(); keine Suche ueber
// clients_known[]. Isolierte APs (ohne beobachtetes Roaming) werden nicht
// aufgelistet.
void menu_enter_roaming_groups()
{
  menu_state = STATE_ROAMING_GROUPS;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;
  Serial.println(F("======================================================="));
  Serial.println(F(" Versorgungsbereiche (vermutet)"));
  Serial.println(F("======================================================="));
  Serial.println(F(" Gruppierung anhand beobachteter Client-Roamings zwischen"));
  Serial.println(F(" Access Points. Gruppen wachsen mit der Beobachtungsdauer."));
  Serial.println();

  // 1) Union-Find initialisieren (jeder AP zunaechst eigene Gruppe)
  for (int i = 0; i < aps_known_count; i++) roaming_parent[i] = (uint8_t)i;

  // 2) Paarliste verschmelzen (Plausibilitaet nochmals pruefen: Slots
  //    koennen seit der Erfassung freigegeben worden sein)
  for (int i = 0; i < roaming_pair_count; i++) {
    uint8_t a = roaming_pairs[i][0];
    uint8_t b = roaming_pairs[i][1];
    if (a < aps_known_count && b < aps_known_count &&
        ! ap_slot_free(a) && ! ap_slot_free(b)) {
      roaming_union(a, b);
    }
  }

  // 3) Gruppen ausgeben: Iteration ueber Wurzeln, jede Gruppe genau einmal
  int group_num = 0;
  for (int i = 0; i < aps_known_count; i++) {
    if (ap_slot_free(i)) continue;
    if (roaming_find(i) != i) continue;
    int members = 0;
    for (int j = 0; j < aps_known_count; j++) {
      if (ap_slot_free(j)) continue;
      if (roaming_find(j) == i) members++;
    }
    if (members < 2) continue;
    group_num++;
    Serial.printf_P(PSTR(" Versorgungsbereich %d (%d APs):\r\n"), group_num, members);
    for (int j = 0; j < aps_known_count; j++) {
      if (ap_slot_free(j)) continue;
      if (roaming_find(j) != i) continue;
      Serial.printf_P(PSTR("   #%-3d [%s] Kanal %d, MAC "),
                      j, aps_known[j].ssid,
                      aps_known[j].channel & AP_CHANNEL_MASK);
      print_mac(aps_known[j].bssid, NULL);
      Serial.println();
    }
    Serial.println();
    yield();
  }
  if (group_num == 0) {
    Serial.println(F(" (noch kein Roaming zwischen APs beobachtet)"));
    Serial.println();
  }

  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Gruppen entstehen ausschliesslich aus beobachtetem"));
  Serial.println(F(" Roaming. Ein noch nicht gesehener Wechsel zwischen zwei"));
  Serial.println(F(" APs fuehrt dazu, dass diese (noch) getrennt erscheinen."));
  Serial.println(F(" Backspace/ESC = zurueck zum Hauptmenue"));
}

// =====================================================================
// NEU 2.30.24: Punkt 2 "Funkverkehr gezielt untersuchen" (Filter-Untermenue)
// =====================================================================

// NEU 2.30.29: Schlaegt eine MAC-Adresse nach - Punkt 2.3 "MAC-Adresse
// nachschlagen" UND fuer den Kanal-Lock in menu_enter_filter_live() (Punkt
// 2.1). Prueft zuerst den AP-Cache (aps_known[], per find_ap_index_by_
// bssid()), dann bei Nichttreffer den Client-Cache (clients_known[]).
mac_lookup_result lookup_mac(uint8_t *mac)
{
  mac_lookup_result r;
  r.found = false;
  r.is_ap = false;
  r.channel = 0;
  r.ap_idx = -1;

  int idx = find_ap_index_by_bssid(mac);
  if (idx >= 0) {
    r.found = true;
    r.is_ap = true;
    r.channel = aps_known[idx].channel & AP_CHANNEL_MASK;
    r.ap_idx = idx;
    return r;
  }

  for (int i = 0; i < clients_known_count; i++) {
    if (! memcmp(clients_known[i].station, mac, ETH_MAC_LEN)) {
      r.found = true;
      r.is_ap = false;
      r.channel = clients_known[i].channel;
      r.ap_idx = clients_known[i].ap_idx;
      return r;
    }
  }
  return r;
}

void menu_enter_filter_menu()
{
  menu_state = STATE_FILTER_MENU;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Funkverkehr untersuchen"));
  Serial.println(F("======================================================="));
  Serial.println(F(" 1) Nach MAC-Adresse filtern (AP oder Client)"));
  Serial.println(F(" 2) Nach Pakettyp filtern (alle Geraete)"));
  Serial.println(F(" 3) MAC-Adresse nachschlagen"));
  Serial.println(F(" 4) Diagnose: scharfer Timing-Test (Debug)"));
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Backspace/ESC = zurueck zum Hauptmenue"));
}

void menu_enter_mac_lookup_input()
{
  menu_state = STATE_MAC_LOOKUP_INPUT;
  lookup_mac_input_len = 0;
  lookup_mac_input_buf[0] = '\0';
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" MAC-Adresse nachschlagen"));
  Serial.println(F("======================================================="));
  Serial.print(F(" MAC-Adresse eingeben (12 Hex-Zeichen): "));
  if (offline_banner_will_print()) Serial.println();  // BUGFIX 2.30.44
}

void menu_enter_mac_lookup_result()
{
  menu_state = STATE_MAC_LOOKUP_RESULT;
  mac_lookup_result r = lookup_mac(lookup_mac_result_mac);
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.print(F(" Ergebnis: "));
  for (int n = 0; n < ETH_MAC_LEN; n++) Serial.printf_P(PSTR("%02x"), lookup_mac_result_mac[n]);
  Serial.println();
  Serial.println(F("======================================================="));
  if (! r.found) {
    Serial.println(F(" Unbekannt - diese MAC-Adresse wurde bisher nicht gesehen."));
  } else if (r.is_ap) {
    Serial.println(F(" Rolle     : Access Point"));
    Serial.printf_P(PSTR(" SSID      : %s\r\n"), aps_known[r.ap_idx].ssid);
    Serial.printf_P(PSTR(" Kanal     : %d\r\n"), r.channel);
  } else {
    Serial.println(F(" Rolle     : Client"));
    Serial.printf_P(PSTR(" Kanal     : %d\r\n"), r.channel);
    if (r.ap_idx >= 0 && r.ap_idx < aps_known_count && ! ap_slot_free(r.ap_idx)) {
      Serial.printf_P(PSTR(" Angemeldet an: %s\r\n"), aps_known[r.ap_idx].ssid);
    } else {
      Serial.println(F(" Angemeldet an: unbekannt"));
    }
  }
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Backspace/ESC = zurueck"));
}

void menu_enter_filter_mac_input()
{
  menu_state = STATE_FILTER_MAC_INPUT;
  filter_mac_input_len = 0;
  filter_mac_input_buf[0] = '\0';
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Filter nach MAC-Adresse"));
  Serial.println(F("======================================================="));
  Serial.print(F(" MAC-Adresse eingeben (12 Hex-Zeichen): "));
  if (offline_banner_will_print()) Serial.println();  // BUGFIX 2.30.44
}

// Gemeinsame Zeichenkette fuer einen Haken - vermeidet doppelten Text an
// jeder der vielen Checkbox-Zeilen unten.
const char* chk(bool on)
{
  return on ? "[x]" : "[ ]";
}

// NEU 2.30.32: Tri-State-Variante von chk() fuer die uebergeordneten Menuepunkte
// 4/5/6/7 (Probes/Management/Control/Data), deren Haken den Gesamtzustand der
// zugehoerigen Checkboxen im jeweiligen Unterauswahlmenue (P/M/C/D) wider-
// spiegelt: alle aktiv -> "[x]" (wie bisher), keine aktiv -> "[ ]" (wie bisher),
// nur ein Teil aktiv -> neu "[~]".
const char* chk_tri(bool any_active, bool all_active)
{
  if (all_active) return "[x]";
  if (any_active) return "[~]";
  return "[ ]";
}

// Zeichnet den Kriterien-Bildschirm (Punkt 2.1 UND 2.2 gemeinsam - der
// einzige Unterschied ist der MAC-/Richtungsblock, der nur bei filter_has_mac
// erscheint). Eigene Funktion statt Teil von menu_enter_filter_criteria(),
// da nach jedem Toggle nur neu GEZEICHNET werden muss, ohne den State
// erneut zu setzen.
void draw_filter_criteria_screen()
{
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  if (filter_has_mac) {
    Serial.print(F(" Filterkriterien: "));
    for (int n = 0; n < ETH_MAC_LEN; n++) Serial.printf_P(PSTR("%02x"), filter_mac[n]);
    Serial.println();
  } else {
    Serial.println(F(" Filterkriterien: alle Geraete"));
  }
  Serial.println(F("======================================================="));
  if (filter_has_mac) {
    Serial.println(F(" Richtung:"));
    Serial.printf_P(PSTR("  1) %s abgehend (MAC ist Sender)\r\n"), chk(filter_dir_out));
    Serial.printf_P(PSTR("  2) %s ankommend (MAC ist Empfaenger)\r\n"), chk(filter_dir_in));
    Serial.println();
  }
  Serial.println(F(" Pakettypen:"));
  Serial.printf_P(PSTR("  3) %s Beacons\r\n"), chk(filter_sel_beacon));
  // NEU 2.30.32: Punkte 4/5/6/7 zeigen jetzt "[~]" statt "[x]", wenn nur ein
  // Teil der zugehoerigen Checkboxen im jeweiligen Unterauswahlmenue aktiv ist.
  Serial.printf_P(PSTR("  4) %s Probes          (p = Unterauswahl)\r\n"),
                chk_tri(filter_sel_probe_req || filter_sel_probe_resp, filter_sel_probe_req && filter_sel_probe_resp));
  Serial.printf_P(PSTR("  5) %s Management       (m = Unterauswahl)\r\n"),
                chk_tri(filter_mgmt_mask != 0, filter_mgmt_mask == FILTER_MGMT_FULL_MASK));
  Serial.printf_P(PSTR("  6) %s Control          (c = Unterauswahl)\r\n"),
                chk_tri(filter_ctrl_mask != 0, filter_ctrl_mask == FILTER_CTRL_FULL_MASK));
  Serial.printf_P(PSTR("  7) %s Data             (d = Unterauswahl)\r\n"),
                chk_tri(filter_data_mask != 0, filter_data_mask == FILTER_DATA_FULL_MASK));
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Zahl = Haken toggeln, p/m/c/d = Unterauswahl"));
  Serial.println(F(" s = Start   Backspace/ESC = zurueck"));
}

void menu_enter_filter_criteria()
{
  menu_state = STATE_FILTER_CRITERIA;
  draw_filter_criteria_screen();
}

void menu_enter_filter_sub_probe()
{
  menu_state = STATE_FILTER_SUB_PROBE;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Probes - Unterauswahl"));
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR("  a) %s Probe Request\r\n"), chk(filter_sel_probe_req));
  Serial.printf_P(PSTR("  b) %s Probe Response\r\n"), chk(filter_sel_probe_resp));
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Buchstabe = Haken toggeln   Backspace/ESC = zurueck"));
}

void menu_enter_filter_sub_mgmt()
{
  menu_state = STATE_FILTER_SUB_MGMT;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Management - Unterauswahl"));
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR("  a) %s Association Request\r\n"), chk(filter_mgmt_mask & ((uint16_t)1<<0)));
  Serial.printf_P(PSTR("  b) %s Association Response\r\n"), chk(filter_mgmt_mask & ((uint16_t)1<<1)));
  Serial.printf_P(PSTR("  c) %s Reassociation Request\r\n"), chk(filter_mgmt_mask & ((uint16_t)1<<2)));
  Serial.printf_P(PSTR("  d) %s Reassociation Response\r\n"), chk(filter_mgmt_mask & ((uint16_t)1<<3)));
  Serial.printf_P(PSTR("  e) %s ATIM\r\n"), chk(filter_mgmt_mask & ((uint16_t)1<<9)));
  Serial.printf_P(PSTR("  f) %s Disassociation\r\n"), chk(filter_mgmt_mask & ((uint16_t)1<<10)));
  Serial.printf_P(PSTR("  g) %s Authentication\r\n"), chk(filter_mgmt_mask & ((uint16_t)1<<11)));
  Serial.printf_P(PSTR("  h) %s Deauthentication\r\n"), chk(filter_mgmt_mask & ((uint16_t)1<<12)));
  Serial.printf_P(PSTR("  i) %s Action\r\n"), chk(filter_mgmt_mask & ((uint16_t)1<<13)));
  Serial.printf_P(PSTR("  s) %s Sonstige/selten (Timing Advertisement,\r\n"), chk(filter_mgmt_mask & FILTER_MGMT_MISC_MASK));
  Serial.println(F("     Action No Ack, Reserved)"));
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Buchstabe = Haken toggeln   Backspace/ESC = zurueck"));
}

void menu_enter_filter_sub_ctrl()
{
  menu_state = STATE_FILTER_SUB_CTRL;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Control - Unterauswahl"));
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR("  a) %s Block ACK Request\r\n"), chk(filter_ctrl_mask & ((uint16_t)1<<8)));
  Serial.printf_P(PSTR("  b) %s Block ACK\r\n"), chk(filter_ctrl_mask & ((uint16_t)1<<9)));
  Serial.printf_P(PSTR("  c) %s PS-Poll\r\n"), chk(filter_ctrl_mask & ((uint16_t)1<<10)));
  Serial.printf_P(PSTR("  d) %s RTS\r\n"), chk(filter_ctrl_mask & ((uint16_t)1<<11)));
  Serial.printf_P(PSTR("  e) %s CTS\r\n"), chk(filter_ctrl_mask & ((uint16_t)1<<12)));
  Serial.printf_P(PSTR("  f) %s ACK\r\n"), chk(filter_ctrl_mask & ((uint16_t)1<<13)));
  Serial.printf_P(PSTR("  s) %s Sonstige/selten (Reserved, Beamforming\r\n"), chk(filter_ctrl_mask & FILTER_CTRL_MISC_MASK));
  Serial.println(F("     Report Poll, VHT/HE NDP, Control Wrapper, CF-End)"));
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Buchstabe = Haken toggeln   Backspace/ESC = zurueck"));
}

void menu_enter_filter_sub_data()
{
  menu_state = STATE_FILTER_SUB_DATA;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Data - Unterauswahl"));
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR("  a) %s Data\r\n"), chk(filter_data_mask & ((uint16_t)1<<0)));
  Serial.printf_P(PSTR("  b) %s Null (kein Payload)\r\n"), chk(filter_data_mask & ((uint16_t)1<<4)));
  Serial.printf_P(PSTR("  c) %s QoS Data\r\n"), chk(filter_data_mask & ((uint16_t)1<<8)));
  Serial.printf_P(PSTR("  d) %s QoS Null (kein Payload)\r\n"), chk(filter_data_mask & ((uint16_t)1<<12)));
  Serial.printf_P(PSTR("  s) %s Sonstige/selten (CF-Ack/-Poll-Varianten,\r\n"), chk(filter_data_mask & FILTER_DATA_MISC_MASK));
  Serial.println(F("     Reserved)"));
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Buchstabe = Haken toggeln   Backspace/ESC = zurueck"));
}

// NEU 2.30.29: hebt einen aktiven Kanal-Lock wieder auf (siehe
// menu_enter_filter_live() unten) - setzt channel_filter auf den Wert
// zurueck, der vor dem Sperren galt.
void filter_channel_unlock_if_active()
{
  if (channel_lock_active) {
    strncpy(channel_filter, saved_channel_filter, 32);
    channel_filter[31] = '\0';
    channel_lock_active = false;
  }
}

void menu_enter_filter_live()
{
  // NEU 2.30.44: Startzeitpunkt fuer den Zeitstempel-Praefix nur beim ECHTEN
  // Einstieg setzen (nicht bei einem Refresh, z.B. durch Strg+O waehrend
  // dieser Bildschirm schon aktiv ist) - sonst wuerde der Zeitstempel bei
  // jedem Online/Offline-Umschalten wieder bei 0 anfangen.
  if (menu_state != STATE_FILTER_LIVE) filter_live_start_ms = millis();
  menu_state = STATE_FILTER_LIVE;

  // NEU 2.30.29: Kanal-Lock fuer Punkt 2.1 - ist die MAC bekannt (Client
  // oder AP), wird der Scan auf genau deren Kanal gesperrt, statt weiter
  // alle Kanaele durchzuwandern. Nutzt die bereits vorhandene channel_filter-
  // Einstellung (Punkt e/3) - gleicher Mechanismus, den der Nutzer auch von
  // Hand setzen koennte, hier nur automatisch temporaer angewendet.
  bool lock_hint = false;
  uint8_t lock_channel = 0;
  if (filter_has_mac) {
    if (channel_lock_active) {
      // NEU 2.30.29 BUGFIX: menu_enter_filter_live() kann erneut aufgerufen
      // werden, waehrend der Lock schon aktiv ist (z.B. Strg+O-Refresh via
      // refresh_current_screen()) - dann NICHT erneut sichern/sperren (das
      // wuerde saved_channel_filter mit dem bereits gesperrten Einzelkanal
      // ueberschreiben und den urspruenglichen Wert unwiederbringlich
      // verlieren), sondern nur die Anzeige auffrischen.
      lock_hint = true;
      lock_channel = channel;
    } else {
      mac_lookup_result r = lookup_mac(filter_mac);
      if (r.found) {
        strncpy(saved_channel_filter, channel_filter, 32);
        saved_channel_filter[31] = '\0';
        channel_lock_active = true;
        snprintf_P(channel_filter, sizeof(channel_filter), PSTR("%d"), r.channel);
        channel = r.channel;
        wifi_set_channel(channel);
        lock_hint = true;
        lock_channel = r.channel;
      }
    }
  }

  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  if (lock_hint) {
    Serial.printf_P(PSTR("Filter aktiv, Kanal auf %d gesperrt. ESC/Backspace = zurueck.\r\n"), lock_channel);
  } else {
    Serial.println(F("Filter aktiv. ESC/Backspace = zurueck zu den Kriterien."));
  }
  Serial.println(F("-------------------------------------------------------"));
}

// =====================================================================
// NEU 2.30.32: Punkt 2.4 "Diagnose: scharfer Timing-Test" (Debug)
// =====================================================================

void menu_enter_timing_test_mac_input()
{
  menu_state = STATE_TIMING_TEST_MAC_INPUT;
  timing_test_mac_input_len = 0;
  timing_test_mac_input_buf[0] = '\0';
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Diagnose: scharfer Timing-Test (Debug)"));
  Serial.println(F("======================================================="));
  Serial.println(F(" Zeichnet ALLE Sichtungen einer MAC-Adresse minimal-"));
  Serial.println(F(" invasiv auf (kein Print pro Paket, keine sonstige"));
  Serial.printf_P(PSTR(" Verarbeitung), %lu Sekunden lang.\r\n"), (unsigned long)timing_test_duration_s);
  Serial.println(F("-------------------------------------------------------"));
  Serial.print(F(" MAC-Adresse eingeben (12 Hex-Zeichen): "));
  if (offline_banner_will_print()) Serial.println();  // BUGFIX 2.30.44
}

void menu_enter_timing_test_running()
{
  menu_state = STATE_TIMING_TEST_RUNNING;
  timing_test_count = 0;
  timing_test_start_ms = millis();
  timing_test_active = true;  // ab jetzt greift der Kurzschluss in promisc_cb()
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.print(F(" Test laeuft fuer: "));
  for (int n = 0; n < ETH_MAC_LEN; n++) Serial.printf_P(PSTR("%02x"), timing_test_mac[n]);
  Serial.println();
  Serial.printf_P(PSTR(" Dauer: %lu Sekunden - keine weitere Ausgabe bis zum Ende.\r\n"), (unsigned long)timing_test_duration_s);
  Serial.println(F(" Backspace/ESC = vorzeitig abbrechen"));
  Serial.println(F("======================================================="));
}

void timing_test_finish()
{
  timing_test_active = false;
  menu_state = STATE_TIMING_TEST_RESULT;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.print(F(" Ergebnis: "));
  for (int n = 0; n < ETH_MAC_LEN; n++) Serial.printf_P(PSTR("%02x"), timing_test_mac[n]);
  Serial.println();
  Serial.printf_P(PSTR(" Treffer: %d"), timing_test_count);
  if (timing_test_count >= TIMING_TEST_MAX_ENTRIES) {
    Serial.print(F(" (Puffer voll - ggf. weitere Treffer nicht aufgezeichnet)"));
  }
  Serial.println();
  Serial.println(F("======================================================="));
  if (timing_test_count == 0) {
    Serial.println(F(" Keine einzige Sichtung dieser MAC-Adresse im gesamten"));
    Serial.println(F(" Testzeitraum - auch nicht mit diesem radikal minimalen,"));
    Serial.println(F(" von der uebrigen Programmlogik komplett entkoppelten"));
    Serial.println(F(" Pfad. Spricht stark fuer ein echtes Empfangs-/"));
    Serial.println(F(" Reichweitenproblem statt fuer eine Ueberlastung durch"));
    Serial.println(F(" unsere eigene Verarbeitung."));
  } else {
    for (int i = 0; i < timing_test_count; i++) {
      timing_test_entry *e = &timing_test_log[i];
      uint8_t ftype = (e->fc_byte & 0x0C) >> 2;
      uint8_t fsubtype = (e->fc_byte & 0xF0) >> 4;
      const char *rolestr = "?";
      if ((e->role & 3) == 3) rolestr = "<>";
      else if (e->role & 1) rolestr = "->";
      else if (e->role & 2) rolestr = "<-";
      Serial.printf_P(PSTR(" +%6lums %s %-20s Ch%2d %4d\r\n"),
                       (unsigned long)e->t_ms, rolestr,
                       ie_frame_subtype_name(ftype, fsubtype),
                       e->channel, e->rssi);
    }
  }
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" -> = MAC war Sender, <- = MAC war Empfaenger"));
  Serial.println(F(" Backspace/ESC = zurueck"));
}

void menu_enter_settings()
{
  menu_state = STATE_SETTINGS;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Einstellungen"));
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" 1) Terminal-Modus:  %s\r\n"), color_enabled ? "VT100+ (mit Farben)" : "VT100 (nur reiner Text)");
  Serial.printf_P(PSTR(" 2) Start-Modus: %s\r\n"), startup_online ? "Online" : "Offline");
  Serial.printf_P(PSTR(" 3) Betriebsmodus:   %s\r\n"), online_mode ? "Online (Live-Aufzeichnung aktiv)" : "Offline (Listen eingefroren)");
  Serial.printf_P(PSTR(" 4) Auto-Save bei Listen-Ueberlauf: %s\r\n"), auto_save_on_overflow ? "An" : "Aus");
  Serial.printf_P(PSTR(" 5) Auto-Offline bei Listen-Ueberlauf: %s\r\n"), auto_offline_on_overflow ? "An" : "Aus");
  if (auto_save_on_overflow && auto_offline_on_overflow) {
    Serial.println(F("    (beide aktiv -> Auto-Offline hat Vorrang, Auto-Save greift dann nicht)"));
  }
  Serial.printf_P(PSTR(" 6) SSID-Liste zweispaltig ab: %d Eintraegen (0=aus)\r\n"), two_col_threshold_ssids);
  Serial.printf_P(PSTR(" 7) Geraeteliste zweispaltig ab: %d Geraeten (0=aus)\r\n"), two_col_threshold_devices);
  Serial.printf_P(PSTR(" 8) NTFY Benachrichtigung konfigurieren >>   [%s]\r\n"), notif_enabled ? "aktiv" : "aus");
  Serial.printf_P(PSTR(" 9) NTP (Zeit) Konfiguration >>   [%s]\r\n"), ntp_enabled ? "aktiv" : "aus");
  Serial.printf_P(PSTR(" a) Auto-Load Datei beim Neustart: %s\r\n"), autoload_filename[0] != '\0' ? autoload_filename : "(deaktiviert)");
  // NEU 2.30.32: ADC-Einstellungen (bisher hier unter 'b') sind in die Hidden
  // Settings verschoben worden - Funktion/Inhalt unveraendert, nur der Menueort.
  Serial.printf_P(PSTR(" c) AP-Modus (fuer Punkt 7, HTTP-Datei-Server) >>   [%s]\r\n"), ap_mode_enabled ? "eigener AP" : "bestehendes WLAN");
  Serial.println(F("-------------------------------------------------------"));
//  Serial.println(F(" Taste 1/2/3/4/5 = umschalten, Taste 6/7 = Zahl eingeben, 8/9/a = Untermenue."));
  Serial.println(F(" Taste s = alle Einstellungen dauerhaft speichern."));
  Serial.println(F(" Backspace/ESC = zurueck zum Menue"));
}

// "Hidden Settings" - nur ueber Taste 'E' IM Einstellungsmenue (Punkt e)
// erreichbar, fuer Einstellungen, die nicht in der normalen Liste
// auftauchen sollen.
void menu_enter_hidden_settings()
{
  menu_state = STATE_HIDDEN_SETTINGS;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Hidden Settings"));
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" 1) Boot-Logo anzeigen: %s\r\n"), show_logo ? "An" : "Aus");
  Serial.printf_P(PSTR(" 2) Auto-Save täglich (um 00:00 Uhr): %s\r\n"), auto_save_enabled ? "An" : "Aus");
  Serial.printf_P(PSTR(" 3) Channel-Filter: %s\r\n"), channel_filter);
  Serial.printf_P(PSTR(" 4) Scan-Verweilzeit pro Kanal: %u ms\r\n"), channel_dwell_ms);
  // NEU 2.17.6: Status-LED GPIO-Pin
  if (status_led_pin >= 0) {
    Serial.printf_P(PSTR(" 5) Status-LED GPIO-Pin: %d\r\n"), status_led_pin);
    // NEU 2.17.7: Polarität - viele Onboard-LEDs sind aktiv-LOW verdrahtet
    Serial.printf_P(PSTR(" 6) Status-LED Polaritaet: %s\r\n"),
                   status_led_active_low ? "invertiert (LOW=an)" : "normal (HIGH=an)");
  } else {
    Serial.printf_P(PSTR(" 5) Status-LED GPIO-Pin: aus (keiner konfiguriert)\r\n"));
  }
  // NEU 2.21.0: Signalisierungspin Optionen
  if (signal_pin >= 0) {
    Serial.printf_P(PSTR(" 9) Signalisierungspin GPIO: %d\r\n"), signal_pin);
    Serial.printf_P(PSTR(" S) Signal aktiviert: %s\r\n"),
                   signal_enabled ? "Ja" : "Nein");
  } else {
    Serial.printf_P(PSTR(" 9) Signalisierungspin GPIO: aus (keiner konfiguriert)\r\n"));
  }
  Serial.println(F(" 7) ESP-Neustart (mit Sicherheitsabfrage)"));
  Serial.println(F(" 8) Werkseinstellungen herstellen >>Sicherheitsabfrage"));  // NEU 2.20.6 BUG8: Letzter Punkt!
  // NEU 2.30.32: ADC-Einstellungen von den normalen Einstellungen hierher
  // verschoben (Funktion/Inhalt unveraendert, nur der Menueort).
  Serial.printf_P(PSTR(" d) ADC (Akkuspannung) konfigurieren >>   [%s]\r\n"), adc_calib_raw > 0 ? "kalibriert" : "nicht kalibriert");
  // NEU 2.30.34: passive RAM-/Stack-Diagnose
  Serial.printf_P(PSTR(" r) Debug RAM Memory >>   [%s]\r\n"), ram_debug.enabled ? "Analyse EIN" : "Analyse AUS");
  Serial.printf_P(PSTR(" k) Szenario-Kompression: %s\r\n"), scenario_compression_enabled ? "EIN" : "AUS");
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Änderungen werden sofort gespeichert."));
//  Serial.println(F(" Taste 3/4/9 = Wert eingeben."));
  Serial.println(F(" Taste t/b = Test LED/Signal Toggle"));
  // NEU 2.30.49: Taste C/P (Listenueberlauf-Test) entfernt - Tests
  // abgeschlossen, Funktionalitaet (Auto-Offline/Auto-Save bei Ueberlauf)
  // bestaetigt funktionsfaehig. Platz fuer Auftrag 1 (Traffic-Stats
  // Varianten 2/3) geschaffen.
  Serial.println(F(" Backspace/ESC = zurueck zu den Einstellungen"));
}

void menu_enter_apmode_settings()
{
  menu_state = STATE_APMODE_SETTINGS;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Einstellungen > AP-Modus (Punkt 7, HTTP-Datei-Server)"));
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" 1) Aktiv: %s\r\n"), ap_mode_enabled ? "An (eigener Access Point)" : "Aus (bestehendes WLAN wird genutzt)");
  Serial.printf_P(PSTR(" 2) AP-SSID: %s\r\n"), ap_mode_ssid);
  Serial.printf_P(PSTR(" 3) AP-Passwort: %s\r\n"), ap_mode_pass[0] ? "********" : "(offen, kein Passwort)");
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Ist Punkt 1 aktiv, spannt Punkt 7 (HTTP-Datei-Server) beim"));
  Serial.println(F(" Start ein EIGENES WLAN mit obiger SSID/obigem Passwort auf,"));
  Serial.println(F(" statt sich (wie bisher) mit dem unter 'Benachrichtigung'"));
  Serial.println(F(" hinterlegten WLAN zu verbinden. Praktisch, wenn gerade kein"));
  Serial.println(F(" Router in Reichweite ist. Ein Passwort muss leer (offenes"));
  Serial.println(F(" WLAN) oder mindestens 8 Zeichen lang sein (WPA2-Minimum)."));
  Serial.println(F(" Taste s = alle Einstellungen dauerhaft speichern."));
  Serial.println(F(" Backspace/ESC = zurueck zu den Einstellungen"));
}

// Textfeld-Eingabe fuer SSID (target=1) bzw. Passwort (target=2) des
// eigenen Access Points - Aufbau analog zu menu_enter_notif_text_edit().
void menu_enter_apmode_text_edit(int target)
{
  menu_state = STATE_APMODE_TEXT_EDIT;
  ap_mode_edit_target = target;
  ap_mode_text_edit_len = 0;
  ap_mode_text_edit_buf[0] = '\0';
  Serial.printf_P(PSTR("\r\nNeuen Wert eingeben (Enter = uebernehmen, leer = loeschen): "));
}

void menu_enter_factory_reset_confirm()
{
  menu_state = STATE_FACTORY_RESET_CONFIRM;
  factory_reset_input_len = 0;
  factory_reset_input_buf[0] = '\0';
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" WERKSEINSTELLUNGEN WIEDERHERSTELLEN"));
  Serial.println(F("======================================================="));
  Serial.println(F(" ACHTUNG: Das loescht ALLE gespeicherten Dateien im Flash"));
  Serial.println(F(" (LittleFS) unwiderruflich und setzt ALLE Einstellungen auf"));
  Serial.println(F(" Standardwerte zurueck! Dieser Schritt kann NICHT"));
  Serial.println(F(" rueckgaengig gemacht werden."));
  Serial.println();
  Serial.println(F(" Zum Bestaetigen exakt LOESCHEN eingeben und Enter druecken."));
  Serial.println(F(" Jede andere Eingabe oder Backspace/ESC bricht ab."));
  Serial.print(F(" > "));
  if (offline_banner_will_print()) Serial.println();  // BUGFIX 2.30.44
}

// NEU 2.20.0 FEATURE 4: ESP-Neustart Sicherheitsabfrage
void menu_enter_esp_restart_confirm()
{
  menu_state = STATE_ESP_RESTART_CONFIRM;
  factory_reset_input_len = 0;  // Nutze gleiches Input-Buffer
  factory_reset_input_buf[0] = '\0';
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" ESP-NEUSTART"));
  Serial.println(F("======================================================="));
  Serial.println(F(" Der ESP wird sofort neugestartet."));
  Serial.println(F(" Der aktuelle Scan-Betrieb wird UNTERBROCHEN."));
  Serial.println();
  Serial.println(F(" Zum Bestaetigen 'ja' eingeben und Enter druecken."));
  Serial.println(F(" Zum Abbrechen ESC druecken."));
  Serial.println();
  Serial.print(F(" > "));
  if (offline_banner_will_print()) Serial.println();  // BUGFIX 2.30.44
}

// Setzt alle Einstellungen auf ihre Standardwerte zurueck, loescht ALLE
// Dateien im SPIFFS und haelt danach in einer Endlosschleife an - das
// Geraet muss danach manuell neu gestartet werden. Schaltet vorher das
// Sniffing komplett "taub", damit waehrend des Loeschens keine neuen
// Pakete mehr verarbeitet werden.
void perform_factory_reset()
{
  wifi_promiscuous_enable(disable);

  vt_clear_screen();
  Serial.println(F("======================================================="));
  Serial.println(F(" WERKSEINSTELLUNGEN WERDEN WIEDERHERGESTELLT ..."));
  Serial.println(F("======================================================="));
  Serial.println(F(" Sniffing angehalten."));

  Serial.println(F(" Loesche alle Dateien im Flash ..."));
  Dir dir = LittleFS.openDir("/");
  while (dir.next()) {
    String fn = dir.fileName();
    if (LittleFS.remove(fn)) {
      Serial.printf_P(PSTR("  geloescht: %s\r\n"), fn.c_str());
    } else {
      Serial.printf_P(PSTR("  FEHLER beim Loeschen: %s\r\n"), fn.c_str());
    }
    yield();
  }

  Serial.println(F(" Setze alle Einstellungen auf Standardwerte zurueck ..."));
  color_enabled = true;
  startup_online = true;
  show_logo = true;
  online_mode = true;
  list_refresh_sec = 10;  // NEU 2.30.14: Standard jetzt 10s (einheitlich)
  current_sort_field = SORT_MAC;
  sort_ascending = true;
  current_ap_sort_field = AP_SORT_NONE;
  ap_sort_ascending = true;
  led_write_digital(false);
  status_led_pin = -1;
  status_led_active_low = false;
  // NEU 2.21.0: Signalisierungspin zurücksetzen
  signal_force_off();
  signal_pin = -1;
  signal_enabled = true;
  signal_active_low = false;
  enable_return_pulse = false;  // NEU 2.30.15: jetzt persistiert, siehe save_all_settings()
  signal_boot_pulse_sent = false;
  ntp_timezone_hours = 1;
  dst_enabled = false;
  rssi_trend_threshold = 10;
  two_col_threshold_devices = 30;
  two_col_threshold_ssids = 40;
  watchlist_refresh_sec = 10;  // NEU 2.30.14: Standard jetzt 10s (einheitlich)
  ssid_select_refresh_sec = 10;  // NEU 2.27.4, NEU 2.30.14: Standard jetzt 10s
  watchlist_count = 0;
  memset(timewatch_state, 0, sizeof(timewatch_state));  // NEU 2.30.67
  notif_enabled = false;
  notif_wifi_ssid[0] = '\0';
  notif_wifi_pass[0] = '\0';
  notif_channel[0] = '\0';
  notif_interval_min = 15;
  notif_content_mode = 0;
  notif_ssid_filter[0] = '\0';
  auto_save_on_overflow = false;
  scenario_compression_enabled = true;
  auto_offline_on_overflow = true;  // NEU 2.29.9: neuer Default
  ntp_enabled = false;
  ntp_wifi_ssid[0] = '\0';
  ntp_wifi_pass[0] = '\0';
  strcpy(ntp_server, "pool.ntp.org");
  ntp_synced = false;
  // NEU 2.30.5: AP-Modus zuruecksetzen
  ap_mode_enabled = false;
  strcpy(ap_mode_ssid, "WiFi-Monitor");
  ap_mode_pass[0] = '\0';

  Serial.println(F("======================================================="));
  Serial.println(F(" Werkseinstellungen wiederhergestellt."));
  Serial.println(F(" Bitte das Geraet jetzt manuell neu starten (Reset-Taste"));
  Serial.println(F(" oder Stromversorgung trennen)."));
  Serial.println(F("======================================================="));

  while (true) {
    delay(1000);
    yield();
  }
}

// ===================== Benachrichtigung (ntfy.sh) =====================
static const char notif_mode_0[] PROGMEM = "Komplette aktive Liste (alle Clients)";
static const char notif_mode_1[] PROGMEM = "Eine SSID (alle APs mit gleicher SSID)";
static const char notif_mode_2[] PROGMEM = "Mehrere SSIDs (kommagetrennt)";
static const char notif_mode_3[] PROGMEM = "Alle Access Points der Hauptliste";

const char* notif_mode_name(int mode)
{
  static char buf[48];
  PGM_P src = notif_mode_0;
  if (mode == 1) src = notif_mode_1;
  else if (mode == 2) src = notif_mode_2;
  else if (mode == 3) src = notif_mode_3;
  strncpy_P(buf, src, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = '\0';
  return buf;
}

void menu_enter_notif_settings()
{
  menu_state = STATE_NOTIF_SETTINGS;
  notif_interval_input_active = false;
  notif_interval_input_len = 0;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Einstellungen > Benachrichtigung (ntfy.sh)"));
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" 1) Aktiv: %s\r\n"), notif_enabled ? "An" : "Aus");
  Serial.printf_P(PSTR(" 2) WLAN-SSID (fuer Versand): %s\r\n"), notif_wifi_ssid[0] ? notif_wifi_ssid : "(nicht gesetzt)");
  Serial.printf_P(PSTR(" 3) WLAN-Passwort: %s\r\n"), notif_wifi_pass[0] ? "********" : "(nicht gesetzt)");
  Serial.printf_P(PSTR(" 4) ntfy-Kanalname: %s\r\n"), notif_channel[0] ? notif_channel : "(nicht gesetzt)");
  Serial.printf_P(PSTR(" 5) Intervall: %d Minuten\r\n"), notif_interval_min);
  Serial.printf_P(PSTR(" 6) Message-Header: %s\r\n"), notif_header_text);  // NEU 2.20.9 BUG6: Punkt 6 (war 7)
  Serial.printf_P(PSTR(" 7) Inhalt: %s\r\n"), notif_mode_name(notif_content_mode));  // NEU 2.20.9 BUG6: Punkt 7 (war 6)
  if (notif_content_mode == 1 || notif_content_mode == 2) {
    Serial.printf_P(PSTR(" 8) SSID-Filter: %s\r\n"), notif_ssid_filter[0] ? notif_ssid_filter : "(nicht gesetzt)");
  }
  Serial.println(F(" 9) Jetzt einmalig senden (Test)"));
  Serial.println(F("-------------------------------------------------------"));
  // NEU 2.20.12: Klar machen, dass Änderungen nur im RAM sind bis 's' gedrückt wird
  Serial.println(F(" Alle Aenderungen sind zuerst nur im RAM (fett gedruckt)!"));
  Serial.println(F(" Taste s = alle Einstellungen dauerhaft speichern"));
  Serial.println(F(" (nur dann wird in Flash geschrieben)"));
  Serial.println(F(" Backspace/ESC = zurueck zu den Einstellungen"));
}

void menu_enter_notif_text_edit(int target)
{
  notif_edit_target = target;
  menu_state = STATE_NOTIF_TEXT_EDIT;
  notif_text_edit_len = 0;
  notif_text_edit_buf[0] = '\0';
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  const char* label;
  if (target == 1) label = "WLAN-SSID (fuer den Versand)";
  else if (target == 2) label = "WLAN-Passwort";
  else if (target == 3) label = "ntfy-Kanalname (Topic)";
  else if (target == 4) label = "Message-Header (Betreff)";  // NEU 2.20.5 BUG5
  else label = "SSID-Filter (mehrere Namen durch Komma trennen)";
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" %s eingeben\r\n"), label);
  Serial.println(F("======================================================="));
  Serial.println(F(" Enter = speichern, Backspace bei leerer Eingabe/ESC = abbrechen."));
  Serial.print(F(" > "));
  if (offline_banner_will_print()) Serial.println();  // BUGFIX 2.30.44
}

// ===================== NTP-Zeitsynchronisation (Menue) =====================
void menu_enter_ntp_settings()
{
  menu_state = STATE_NTP_SETTINGS;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Einstellungen > NTP-Zeitsynchronisation"));
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" 1) Aktiv: %s\r\n"), ntp_enabled ? "An" : "Aus");
  Serial.printf_P(PSTR(" 2) WLAN-SSID (fuer NTP): %s\r\n"), ntp_wifi_ssid[0] ? ntp_wifi_ssid : "(nicht gesetzt)");
  Serial.printf_P(PSTR(" 3) WLAN-Passwort: %s\r\n"), ntp_wifi_pass[0] ? "********" : "(nicht gesetzt)");
  Serial.printf_P(PSTR(" 4) NTP-Server: %s\r\n"), ntp_server);
  // NEU 2.17.8: Zeitzone jetzt frei einstellbar (-12..12) statt fest MEZ/
  // MESZ-Umschaltung; Daylight Saving Time (DST) separat als eigener
  // An/Aus-Punkt, Umstellung erfolgt dann automatisch nach Kalenderdatum.
  Serial.printf_P(PSTR(" 5) Zeitzone (UTC-Offset): %+d Stunde(n)\r\n"), ntp_timezone_hours);
  Serial.printf_P(PSTR(" 6) Daylight Saving Time (Sommer-/Winterzeit): %s\r\n"),
                 dst_enabled ? "An" : "Aus");
  Serial.println(F("-------------------------------------------------------"));
  if (ntp_synced) {
    time_t now = current_unix_time_with_tz();
    Serial.printf_P(PSTR(" Aktuell synchronisiert: %s"), ctime(&now));
  } else {
    Serial.println(F(" Noch nicht synchronisiert - erfolgt beim naechsten Neustart,"));
    Serial.println(F(" sofern hier aktiviert und WLAN-Zugangsdaten gesetzt sind."));
  }
  Serial.println(F("-------------------------------------------------------"));
//  Serial.println(F(" Taste 1/6 = umschalten, 2/3/4/5 = Wert eingeben."));
  Serial.println(F(" Taste s = alle Einstellungen dauerhaft speichern."));
  Serial.println(F(" Backspace/ESC = zurueck zu den Einstellungen"));
}

void menu_enter_ntp_text_edit(int target)
{
  ntp_edit_target = target;
  menu_state = STATE_NTP_TEXT_EDIT;
  ntp_text_edit_len = 0;
  ntp_text_edit_buf[0] = '\0';
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  const char* label;
  if (target == 1) label = "WLAN-SSID (fuer NTP)";
  else if (target == 2) label = "WLAN-Passwort";
  else label = "NTP-Server (z.B. pool.ntp.org)";
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" %s eingeben\r\n"), label);
  Serial.println(F("======================================================="));
  Serial.println(F(" Enter = speichern, Backspace bei leerer Eingabe/ESC = abbrechen."));
  Serial.print(F(" > "));
  if (offline_banner_will_print()) Serial.println();  // BUGFIX 2.30.44
}

// NEU 2.29.0: Liefert die aktuelle Akkuspannung in Millivolt, basierend auf
// der Einpunkt-Kalibrierung (adc_calib_raw/adc_calib_mv). Ohne Kalibrierung
// (adc_calib_raw==0) wird 0 zurueckgegeben - Aufrufer muessen das als
// "nicht verfuegbar" behandeln.
uint16_t adc_read_voltage_mv()
{
  if (adc_calib_raw == 0) return 0;
  int raw = analogRead(A0);
  // uint32_t Zwischenrechnung gegen Ueberlauf (adc_calib_mv * raw kann > 65535 sein)
  uint32_t mv = ((uint32_t)adc_calib_mv * (uint32_t)raw) / (uint32_t)adc_calib_raw;
  if (mv > 65535) mv = 65535;
  return (uint16_t)mv;
}

// Einstellungen > ADC (Akkuspannung). Zeigt den aktuellen Roh-ADC-Wert (zur
// Kontrolle der Spannungsteiler-Dimensionierung) sowie die daraus
// berechnete Spannung, falls kalibriert.
void menu_enter_adc_settings()
{
  menu_state = STATE_ADC_SETTINGS;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  int raw = analogRead(A0);
  Serial.println(F("======================================================="));
  Serial.println(F(" Hidden Settings > ADC (Akkuspannung)"));  // NEU 2.30.32: umgehaengt von Einstellungen
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" Aktueller ADC-Rohwert: %d (0-1023)\r\n"), raw);
  if (adc_calib_raw > 0) {
    uint16_t mv = adc_read_voltage_mv();
    Serial.printf_P(PSTR(" Kalibrierung: %d mV bei ADC-Rohwert %d\r\n"), adc_calib_mv, adc_calib_raw);
    Serial.printf_P(PSTR(" Berechnete aktuelle Spannung: %d.%02d V\r\n"), mv / 1000, (mv % 1000) / 10);
  } else {
    Serial.println(F(" Kalibrierung: nicht kalibriert"));
  }
  Serial.println(F("-------------------------------------------------------"));
  Serial.printf_P(PSTR(" Warnschwelle (fest): %d.%02d V\r\n"),
                 ADC_LOW_VOLTAGE_THRESHOLD_MV / 1000, (ADC_LOW_VOLTAGE_THRESHOLD_MV % 1000) / 10);
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" 1) Spannung kalibrieren (gemessene Spannung eingeben)"));
  Serial.println(F(" Backspace/ESC = zurueck zu Hidden Settings"));  // NEU 2.30.32
}

// NEU 2.30.34: Hidden Settings > Debug RAM Memory - zeigt aktuelle Werte
// (immer live abgefragt, unabhaengig vom EIN/AUS-Zustand der Analyse - das
// ist eine einmalige Anzeige-Abfrage beim Aufruf dieses Bildschirms, KEINE
// laufende Aufzeichnung) sowie die per ram_debug_sample() aufgezeichneten
// Extremwerte samt Messpunkt. Reine Rohwert-Anzeige, keine automatische
// Bewertung (siehe Vorgabe "keine automatische Aussage wie RAM OK/CRITICAL").
void menu_enter_ram_debug()
{
  menu_state = STATE_RAM_DEBUG;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.34: Banner am Ende (RAII)
  Serial.println(F("======================================================="));
  Serial.println(F(" --- DEBUG RAM MEMORY ---"));
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" RAM-Analyse : %s\r\n"), ram_debug.enabled ? "EIN" : "AUS");
  Serial.println();
  Serial.println(F(" AKTUELL"));
  Serial.printf_P(PSTR(" Free Heap       %lu B\r\n"), (unsigned long) ESP.getFreeHeap());
  Serial.printf_P(PSTR(" Max Free Block  %lu B\r\n"), (unsigned long) ESP.getMaxFreeBlockSize());
  Serial.printf_P(PSTR(" Fragmentation      %u %%\r\n"), (unsigned) ESP.getHeapFragmentation());
  // GEPRUEFT 2.30.37 (auf Anwenderanfrage): dies ist bei jedem Aufruf dieser
  // Funktion eine FRISCHE Abfrage von ESP.getFreeContStack() - kein
  // zwischengespeicherter/historischer Wert, keine Verwechslung mit
  // ram_debug.min_free_stack. Dass AKTUELL zufaellig nahe am/gleich dem
  // MINIMUM liegen kann, ist plausibel und kein Anzeigefehler: dieser
  // Bildschirm wird selbst tief verschachtelt aufgerufen (ueber
  // menu_handle_serial() -> ... -> hier), zusaetzlich vertieft durch die
  // Call-Chain-Guards, sofern die Analyse eingeschaltet ist.
  Serial.printf_P(PSTR(" Free Stack      %lu B\r\n"), (unsigned long) ESP.getFreeContStack());
  Serial.println();
  Serial.println(F(" MINIMUM"));
  if (ram_debug.measurement_count == 0) {
    // Noch keine Messung seit letztem Reset/Neustart - Rohwert-Anzeige,
    // keine sinnvollen Extremwerte vorhanden.
    Serial.println(F(" Free Heap       ---"));
    Serial.println(F(" Max Free Block  ---"));
    Serial.println(F(" Free Stack      ---"));
  } else {
    char name[20];
    ram_debug_point_name(ram_debug.min_free_heap_point, name, sizeof(name));
    Serial.printf_P(PSTR(" Free Heap       %lu B   [%s]\r\n"), (unsigned long) ram_debug.min_free_heap, name);
    ram_debug_point_name(ram_debug.min_max_free_block_point, name, sizeof(name));
    Serial.printf_P(PSTR(" Max Free Block  %lu B   [%s]\r\n"), (unsigned long) ram_debug.min_max_free_block, name);
    ram_debug_point_name(ram_debug.min_free_stack_point, name, sizeof(name));
    Serial.printf_P(PSTR(" Free Stack      %lu B   [%s]\r\n"), (unsigned long) ram_debug.min_free_stack, name);
  }
  Serial.println();
  Serial.println(F(" MAXIMUM"));
  if (ram_debug.measurement_count == 0) {
    Serial.println(F(" Fragmentation      ---"));
  } else {
    char name[20];
    ram_debug_point_name(ram_debug.max_fragmentation_point, name, sizeof(name));
    Serial.printf_P(PSTR(" Fragmentation      %u %%  [%s]\r\n"), (unsigned) ram_debug.max_fragmentation, name);
  }
  Serial.println();
  Serial.printf_P(PSTR(" Messungen       %lu\r\n"), (unsigned long) ram_debug.measurement_count);
  Serial.println(F("-------------------------------------------------------"));
  // NEU 2.30.35: Call-Chain-Erweiterung - eigener Schalter (siehe Vorgabe
  // Pkt.2: nicht automatisch mit der RAM-Analyse gekoppelt).
  Serial.printf_P(PSTR(" Call-Chain Analyse : %s%s\r\n"), call_chain_enabled ? "EIN" : "AUS",
                (call_chain_enabled && !ram_debug.enabled) ? "  (inaktiv, da RAM-Analyse AUS)" : "");
  Serial.println(F(" 1) Analyse EIN/AUS"));
  Serial.println(F(" 2) Messwerte loeschen"));
  Serial.println(F(" 3) Call-Chain Analyse EIN/AUS"));
  Serial.println(F(" 4) Call-Chain anzeigen"));
  Serial.println(F(" 5) Zurueck"));
}

// NEU 2.30.35: Gibt eine gespeicherte Call-Chain-Momentaufnahme kompakt aus
// (Funktionsnamen aus dem Flash aufgeloest, keine dynamischen Strings).
void call_chain_print_snapshot(uint8_t depth, const uint8_t *point,
                               const uint32_t *entry_stack, uint8_t context,
                               const char* title)
{
  Serial.printf_P(PSTR(" %s\r\n"), title);
  if (depth == 0) {
    Serial.println(F("  (keine Messung seit letztem Reset/Neustart)"));
    return;
  }
  // NEU 2.30.37 (Vorgabe Pkt.15): Kontext klar benennen, damit z.B. ein
  // Messpunkt innerhalb des Promiscuous Callbacks nicht mit einer normalen
  // Hauptprogrammfunktion verwechselt wird.
  Serial.printf_P(PSTR("  Kontext: %s\r\n"),
                context == CTX_PROMISC ? "PROMISCUOUS CALLBACK" : "Hauptprogramm/Menue");
  if (context == CTX_PROMISC) {
    // NEU 2.30.44: per SP-Adressvergleich (siehe oben) empirisch bestaetigt,
    // dass der Promiscuous Callback auf einem ANDEREN physischen Stack
    // laeuft als das Hauptprogramm. Die "Entry"-Werte hier sind deshalb kein
    // verlaesslicher Stack-Fuellstand des Callbacks selbst, sondern spiegeln
    // (zufaellig) den Zustand des dabei pausierten Hauptprogramm-Stacks
    // wider. Heap/Block/Fragmentierung bleiben davon unberuehrt (globale,
    // kontextunabhaengige Ressourcen).
    Serial.println(F("  Hinweis: Stack-Werte hier vermutlich NICHT aussagekraeftig"));
    Serial.println(F("  (Callback laeuft laut SP-Vergleich auf anderem Stack)"));
  }
  char name[20];
  // NEU 2.30.35: Kette von aussen (Ebene 0) nach innen (tiefste Ebene) mit
  // Einrueckung, jeweils mit dem beim Eintritt in diese Ebene noch freien
  // Stack (Vorgabe Pkt.21: Eintritts- und Minimumwert unterscheiden - die
  // tiefste Ebene entspricht dabei dem gesuchten Minimum selbst).
  for (uint8_t i = 0; i < depth && i < CALL_CHAIN_MAX_DEPTH; i++) {
    ram_debug_point_name(point[i], name, sizeof(name));
    if (i == 0) {
      Serial.printf_P(PSTR("  %s"), name);
    } else {
      for (uint8_t j = 0; j < i; j++) Serial.print(F("  "));
      Serial.printf_P(PSTR("-> %s"), name);
    }
    Serial.printf_P(PSTR("   Entry: %lu B\r\n"), (unsigned long) entry_stack[i]);
  }
}

// NEU 2.30.35: Hidden Settings > Debug RAM Memory > Call-Chain anzeigen.
// Reine Anzeige (Punkt "Call-Chain anzeigen") - loest selbst keine neue
// Messung aus, zeigt nur die bereits erfassten Kennzahlen/Ketten an.
void menu_enter_call_chain_view()
{
  menu_state = STATE_CALL_CHAIN_VIEW;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.35: Banner am Ende (RAII)
  Serial.println(F("======================================================="));
  Serial.println(F(" --- CALL-CHAIN ANALYSE ---"));
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" Status: %s\r\n"), call_chain_enabled ? "EIN" : "AUS");
  Serial.println();

  Serial.printf_P(PSTR(" Minimum Free Stack (Call-Chain): %lu B\r\n"),
                call_chain_min_stack == 0xFFFFFFFFUL ? 0UL : (unsigned long) call_chain_min_stack);
  call_chain_print_snapshot(call_chain_snapshot_min_stack.depth, call_chain_snapshot_min_stack.point, call_chain_snapshot_min_stack.entry_stack, (uint8_t)call_chain_snapshot_min_stack.context, "Kette:");
  Serial.println();

  Serial.printf_P(PSTR(" Max. Call Depth: %u\r\n"), (unsigned) call_chain_max_depth);
  call_chain_print_snapshot(call_chain_snapshot_max_depth.depth, call_chain_snapshot_max_depth.point, call_chain_snapshot_max_depth.entry_stack, (uint8_t)call_chain_snapshot_max_depth.context, "Kette:");
  Serial.println();

  // BUGFIX 2.30.47: SP-Adressvergleichsdiagnose (2.30.38) entfernt - war nur
  // eine einmalige Untersuchungshilfe (Frage laengst beantwortet: zwei
  // verschiedene Stacks bestaetigt), siehe Kommentar bei call_chain_state.

  // NEU 2.30.44 (Anwenderwunsch): ALLE Messpunkte auflisten, auch mit 0
  // Aufrufen - so ist sichtbar, welcher Codepfad/Zweig im laufenden Test
  // noch gar nicht durchlaufen wurde, statt nur die bereits getroffenen zu
  // zeigen (vorher: "if (...== 0) continue;" liess unbenutzte Punkte
  // stillschweigend weg).
  Serial.println(F(" FUNKTION             AUFRUFE"));
  char name[20];
  for (uint8_t i = 1; i < RDP_COUNT; i++) {  // 0 = RDP_NONE, uebersprungen
    ram_debug_point_name(i, name, sizeof(name));
    if (call_chain_call_count[i] == 0) {
      Serial.printf_P(PSTR(" %-20s %8s\r\n"), name, "-- noch nicht erreicht --");
    } else {
      Serial.printf_P(PSTR(" %-20s %8lu\r\n"), name, (unsigned long) call_chain_call_count[i]);
    }
  }
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Backspace/ESC = zurueck zu Debug RAM Memory"));
}

// NEU 2.29.0: Periodische Ueberwachung der Akkuspannung, aus menu_periodic()
// heraus aufgerufen (also unabhaengig vom aktuellen Menuestatus, wie schon
// die Watchlist-Signalisierung). Nicht kalibriert -> keine Wirkung. Bei
// Unterschreiten der Schwelle werden zur Vermeidung von Messfehlern
// insgesamt 3 Messungen im Abstand von je 5 Sekunden verlangt, die ALLE
// unterhalb der Schwelle liegen muessen, bevor der aktuelle Listenzustand
// (wie beim GPIO0-Tastendruck) im Flash gesichert wird - nur mit "ADC_"
// statt "Bttn_" als Dateinamens-Praefix. Danach Latch (adc_low_event_fired),
// bis die Spannung wieder ueber die Schwelle steigt.
void adc_voltage_monitor()
{
  if (adc_calib_raw == 0) return;  // nicht kalibriert - keine Ueberwachung moeglich

  // NEU 2.29.3 BUGFIX: menu_periodic() (und damit adc_voltage_monitor())
  // wird bei jedem loop()-Durchlauf aufgerufen, also >500x/s. analogRead()
  // auf dem ESP8266 stoert bei so hoher Frequenz das SDK-interne Timing,
  // von dem der interruptgesteuerte Promiscuous-Empfang abhaengt - seit
  // 2.29.0 dadurch spuerbar "tauber" Scanner (AP/Client-Erkennung verzoegert
  // oder komplett verpasst). Die eigentliche 3-fach-Bestaetigung tickt
  // ohnehin nur alle 5s, eine Messung pro Sekunde reicht bei weitem.
  static uint32_t last_adc_check_ms = 0;
  if ((uint32_t)(millis() - last_adc_check_ms) < 15000) return;  // NEU 2.29.4: 1s -> 15s
  last_adc_check_ms = millis();

  uint16_t mv = adc_read_voltage_mv();

  if (adc_low_event_fired) {
    // Bereits ausgeloest - erst bei Erholung ueber die Schwelle wieder scharf
    if (mv >= ADC_LOW_VOLTAGE_THRESHOLD_MV) {
      adc_low_event_fired = false;
      adc_low_confirm_count = 0;
    }
    return;
  }

  if (adc_low_confirm_count == 0) {
    // Noch keine Bestaetigungsmessung laufend - erste Unterschreitung?
    if (mv < ADC_LOW_VOLTAGE_THRESHOLD_MV) {
      adc_low_confirm_count = 1;
      adc_low_confirm_last_ms = millis();
      Serial.printf_P(PSTR("\r\n [ADC] Spannung %d.%02d V unter Schwelle - bestaetige in ~15s erneut (1/3)...\r\n"),
                     mv / 1000, (mv % 1000) / 10);
    }
    return;
  }

  // Bestaetigungsmessung laeuft - die naechste Messung kommt ohnehin erst
  // nach dem 15s-Messintervall oben, dieser Wartewert dient nur noch als
  // zusaetzliche Absicherung (kein eigenstaendiger 5s-Takt mehr).
  if (millis() - adc_low_confirm_last_ms < 3000) return;

  if (mv < ADC_LOW_VOLTAGE_THRESHOLD_MV) {
    adc_low_confirm_count++;
    adc_low_confirm_last_ms = millis();
    if (adc_low_confirm_count >= 3) {
      // Alle 3 Messungen bestaetigt - jetzt sichern, wie beim GPIO0-Tastendruck,
      // nur mit "ADC_" statt "Bttn_" als Dateinamens-Praefix.
      Serial.printf_P(PSTR(" [ADC] Spannung %d.%02d V dreifach bestaetigt unter Schwelle - sichere Zustand...\r\n"),
                     mv / 1000, (mv % 1000) / 10);
      if (clients_known_count > 0 || aps_known_live_count() > 0) {
        char adc_filename[50];
        if (ntp_synced) {
          time_t now = current_unix_time_with_tz();
          struct tm* timeinfo = localtime(&now);
          snprintf_P(adc_filename, sizeof(adc_filename),
                   PSTR("ADC_%d-%d_%02d%02d%02d_%02d%02d%02d"),
                   clients_known_count, aps_known_live_count(),
                   timeinfo->tm_year % 100, timeinfo->tm_mon + 1, timeinfo->tm_mday,
                   timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
        } else {
          // NEU 2.30.65: "offline_"+millis() -> "NoNtp_"+ddhhmmss
          char uptime[9];
          format_uptime_ddhhmmss(uptime, sizeof(uptime));
          snprintf_P(adc_filename, sizeof(adc_filename),
                   PSTR("ADC_%d-%d_NoNtp_%s"),
                   clients_known_count, aps_known_live_count(),
                   uptime);
        }
        int result = save_current_lists(adc_filename);
        if (result > 0) {
          Serial.printf_P(PSTR(" [ADC] erfolgreich: %d Eintraege gespeichert als '%s.txt'.\r\n"), result, adc_filename);
        } else {
          Serial.println(F(" [ADC] FEHLER beim Speichern!"));
        }
      } else {
        Serial.println(F(" [ADC] Keine Geraete/APs aufgezeichnet - nicht gespeichert."));
      }
      if (traffic_stats_active) {
        Serial.println(F(" [ADC] Aktive Hintergrundverkehr-Aufzeichnung wird zusaetzlich gesichert..."));
        traffic_stats_save_to_file();
      }
      adc_low_event_fired = true;
      adc_low_confirm_count = 0;
      // NEU 2.30.35: rote Serial-Warnung (einmalig) + 5x Signalpin-Impuls.
      // Die LED-Warnanzeige selbst haengt direkt am Latch adc_low_event_fired
      // (siehe led_update()) und braucht hier keinen weiteren Aufruf.
      vt_sgr("31");
      Serial.println(F(" !!! WARNUNG: MINIMALER AKKU-SCHWELLWERT UNTERSCHRITTEN !!!"));
      Serial.printf_P(PSTR(" Akku: %d.%02d V   Schwelle: %d.%02d V\r\n"),
                     mv / 1000, (mv % 1000) / 10,
                     ADC_LOW_VOLTAGE_THRESHOLD_MV / 1000, (ADC_LOW_VOLTAGE_THRESHOLD_MV % 1000) / 10);
      vt_color_reset();
      adc_low_start_pulse();
    } else {
      Serial.printf_P(PSTR(" [ADC] Spannung %d.%02d V weiterhin unter Schwelle - bestaetige in ~15s erneut (%d/3)...\r\n"),
                     mv / 1000, (mv % 1000) / 10, adc_low_confirm_count);
    }
  } else {
    // Waehrend der Bestaetigungsphase erholt - Messfehler-Verdacht, abbrechen
    Serial.printf_P(PSTR(" [ADC] Spannung wieder bei %d.%02d V - Bestaetigung abgebrochen.\r\n"),
                   mv / 1000, (mv % 1000) / 10);
    adc_low_confirm_count = 0;
  }
}
// enthaltenen Geraete, oder -1 bei Fehler.
#define NOTIF_TMP_FILE "/notif_tmp.txt"

// NEU 2.28.6: Vendor-Lookup fuer den ntfy-Versand grundsaetzlich deaktiviert
// (unabhaengig von der Einstellung show_vendors_in_menu3a/show_vendors_in_menu3).
// Der ntfy-Aufrufpfad liegt gegenueber der Konsole 3 Funktionsebenen tiefer,
// bevor er in dieselbe ohnehin knappe Vendor-Lookup-Kette eintaucht - das
// sprengte in Tests wiederholt den ESP8266-cont-Stack (Panic in __yield).
// Die einzige stack-sichere Loesung waere gemeinsam genutzte globale
// Scratch-Puffer gewesen (~1300 Byte dauerhafte RAM-Reservierung) - das
// wurde als RAM-Kosten explizit abgelehnt. Ist die Einstellung trotzdem
// eingeschaltet, wird die Liste einfach so erzeugt, als waere sie aus -
// keine Heap-/Stack-Schutzmechanismen mehr noetig, da der Lookup fuer
// ntfy schlicht nie aufgerufen wird.

// NEU 2.30.81: Einheitlicher Header fuer erzeugte textbasierte Nutzdateien.
void format_generation_timestamp(char *out, size_t outlen)
{
  if (out == NULL || outlen == 0) return;
  if (ntp_synced) { time_t t=current_unix_time_with_tz(); struct tm* ti=localtime(&t); snprintf_P(out,outlen,PSTR("%04d-%02d-%02d %02d:%02d:%02d"),ti->tm_year+1900,ti->tm_mon+1,ti->tm_mday,ti->tm_hour,ti->tm_min,ti->tm_sec); }
  else format_uptime_dhm(millis()/1000UL,out,outlen);
}
void write_generated_file_header(File &f)
{ char ts[32]; format_generation_timestamp(ts,sizeof(ts)); f.printf_P(PSTR("# Erzeugt: %s | Programmversion: v%s\r\n"),ts,FIRMWARE_VERSION); }

// NEU 2.30.63: Schreibt den kompletten aktuellen Listen-Zustand im
// unkomprimierten Sicherungsformat in das uebergebene File-Objekt. Wird von
// save_current_lists() (Zieldatei im Flash) UND von build_notif_attachment()
// (ntfy-Anhang, Modus 0) gemeinsam verwendet - dadurch ist der ntfy-Anhang
// exakt im selben Format wie eine ueber RETURN/GPIO0 erzeugte Sicherung und
// laesst sich ueber Menue 6 "l+Zahl" wieder als Arbeitsliste einlesen.
// Muss vor allen Aufrufern DEFINIERT sein (nicht nur deklariert) - sonst
// stuende der von Arduino automatisch generierte Funktionsprototyp vor
// dieser Definition, was sich in diesem Sketch historisch mehrfach als
// fehleranfaellig erwiesen hat (siehe Changelog 2.30.22/.25/.47/.49/.51).
// Exakte Spaltenabstaende (" %3d   %d   %d   %4d\r\n") und der Kopfsatz
// duerfen sich nicht aendern - load_scenario_file() erwartet sie so.
// Rueckgabe: Anzahl geschriebener Eintraege (Clients + APs).
int write_scenario_plaintext(File &f, uint64_t now)
{
  int entry_count = 0;

  write_generated_file_header(f);
  f.printf_P(PSTR("# WiFi-Monitor Sicherung - %d Clients, %d Access Points\r\n"),
             clients_known_count, aps_known_live_count());
  f.println(F("-------------------------------------------------------------------------------------"));

  for (int u = 0; u < clients_known_count; u++) {
    clientinfo ci = clients_known[u];
    f.print(F("DEVICE: "));
    for (int i = 0; i < 6; i++) f.printf_P(PSTR("%02x"), ci.station[i]);
    f.print(F(" ==> "));
    bool known = (ci.ap_idx < aps_known_count && !ap_slot_free(ci.ap_idx));
    if (known) {
      f.printf_P(PSTR("[%32s]  "), aps_known[ci.ap_idx].ssid);
      for (int i = 0; i < 6; i++) f.printf_P(PSTR("%02x"), aps_known[ci.ap_idx].bssid[i]);
    } else {
      f.printf_P(PSTR("[%32s]  "), "??");
      f.print(F("????????????"));
    }
    f.printf_P(PSTR(" %3d   %d   %d   %4d\r\n"),
               ci.channel, (int)(now - ci.last_heard), ci.reported, ci.rssi);
    entry_count++;
    yield();
  }

  for (int u = 0; u < aps_known_count; u++) {
    if (ap_slot_free(u)) continue;
    beaconinfo bi = aps_known[u];
    f.printf_P(PSTR("BEACON: <=============== [%32s]  "), bi.ssid);
    for (int i = 0; i < 6; i++) f.printf_P(PSTR("%02x"), bi.bssid[i]);
    f.printf_P(PSTR(" %3d   %d   %d   %4d\r\n"),
               bi.channel & AP_CHANNEL_MASK,
               (int)(now - bi.last_heard), bi.reported, bi.rssi);
    entry_count++;
    yield();
  }

  f.println(F("# SETTINGS"));
  f.printf_P(PSTR("sort_field=%d\r\n"), (int)current_sort_field);
  f.printf_P(PSTR("sort_ascending=%d\r\n"), sort_ascending ? 1 : 0);
  f.printf_P(PSTR("ap_sort_field=%d\r\n"), (int)current_ap_sort_field);
  f.printf_P(PSTR("ap_sort_ascending=%d\r\n"), ap_sort_ascending ? 1 : 0);
  f.printf_P(PSTR("list_refresh_sec=%d\r\n"), list_refresh_sec);
  f.printf_P(PSTR("rssi_trend_threshold=%d\r\n"), rssi_trend_threshold);
  f.printf_P(PSTR("two_col_threshold_devices=%d\r\n"), two_col_threshold_devices);
  f.printf_P(PSTR("two_col_threshold_ssids=%d\r\n"), two_col_threshold_ssids);

  return entry_count;
}

// NEU 2.28.0: Baut den Dateinamen fuer den ntfy-Anhang aus dem konfigurierten
// Message-Header-Text (statt des bisherigen festen "liste.txt") plus einem
// kurzen, am Inhalt orientierten Zusatz, damit die Art der Liste am Dateinamen
// erkennbar ist. Leerzeichen/Zeilenumbrueche werden durch "_" ersetzt, damit
// der Name als HTTP-Headerwert unproblematisch ist.
// NEU 2.30.64: Schema von "[Konfigurierter Name]_[Listentyp].txt" auf
// "[Zeitstempel]_[Konfigurierter Name].txt" umgestellt (Beispiel:
// "260929_133114_Testschwein.txt"), der bisherige Listentyp-Suffix
// (Liste/SSID/SSIDs/APs) entfaellt dabei komplett - fuer alle Modi
// gleichermassen, wie im Auftrag als generelles Schema vorgegeben. Ohne
// NTP-Synchronisation ist kein sinnvoller Zeitstempel verfuegbar; dann
// faellt die Funktion auf "000000_000000_" als Platzhalter-Praefix zurueck,
// statt ganz auf das alte Schema umzuschalten - so bleibt das Format
// (und damit z.B. ein Downstream-Parser fuer den Dateinamen) einheitlich.
void build_notif_filename(char* out, size_t outlen)
{
  char base[33];
  strncpy(base, notif_header_text, sizeof(base) - 1);
  base[sizeof(base) - 1] = '\0';
  if (base[0] == '\0') strcpy(base, "WiFi-Monitor");

  for (int i = 0; base[i] != '\0'; i++) {
    if (base[i] == ' ' || base[i] == '\r' || base[i] == '\n') base[i] = '_';
  }

  char ts[14];
  if (ntp_synced) {
    time_t tz_now = current_unix_time_with_tz();
    struct tm* timeinfo = localtime(&tz_now);
    snprintf_P(ts, sizeof(ts), PSTR("%02d%02d%02d_%02d%02d%02d"),
      timeinfo->tm_year % 100, timeinfo->tm_mon + 1, timeinfo->tm_mday,
      timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
  } else {
    // NEU 2.30.65: ddhhmmss ersetzt den Zeitstempel direkt (kein "NoNtp_"-
    // Zusatz hier, anders als bei den Flash-Dateien).
    format_uptime_ddhhmmss(ts, sizeof(ts));
  }

  // NEU 2.30.65: modusabhaengiger Typ-Zusatz zurueck (neue Schreibweise),
  // aber weiterhin NICHT fuer Modus 0 (regulaere Sicherung seit 2.30.63).
  const char* suffix;
  switch (notif_content_mode) {
    case 1: suffix = "_ssid"; break;
    case 2: suffix = "_Xssid"; break;
    case 3: suffix = "_APs"; break;
    default: suffix = ""; break;  // Modus 0
  }

  snprintf_P(out, outlen, PSTR("%s_%s%s.txt"), ts, base, suffix);
}

// Schreibt einen Clients-Abschnitt (Header + Zeilen, Format identisch zur
// Konsole in Menue 3a) fuer die uebergebenen (bereits gefilterten) Indizes
// in die Datei f. Sortierung erfolgt hier NICHT mehr - der Aufrufer sortiert
// vorher passend (sort_clients() bzw. unsortiert fuer Modus 0, s.u.).
// NEU 2.28.1: Die Datei bleibt WAEHREND des gesamten Abschnitts durchgehend
// offen (EIN Handle, kein Oeffnen/Schliessen pro Zeile).
// NEU 2.28.6: Vendor-Lookup hier grundsaetzlich deaktiviert (s. Kommentar oben).
void write_notif_client_section(File &f, uint16_t *indices, int count, uint64_t now, int *written)
{
  // NEU 2.28.6: Vendor-Lookup fuer ntfy grundsaetzlich deaktiviert (s.
  // Kommentar weiter oben) - unabhaengig von show_vendors_in_menu3a wird
  // die Liste immer so erzeugt, als waere die Einstellung aus.
  const bool want_vendor = false;

  if (want_vendor) {
    f.println(F(" MAC          ch  Age  db      Hersteller"));
  } else {
    f.println(F(" MAC          ch  Age  db"));
  }
  f.println(F("-------------------------------------------------------"));

  for (int i = 0; i < count; i++) {
    int u = indices[i];
    f.print(F(" "));
    print_client_cell(u, now, &f);
    if (want_vendor) {
      f.print(F(" "));
      String vendor = vendorCache_lookup_or_search(clients_known[u].station);
      f.print(vendor.c_str());
    }
    f.println();
    (*written)++;
    yield();
  }
  if (count == 0) f.println(F(" (keine Geraete)"));
  f.println(F("-------------------------------------------------------"));
}

// Schreibt einen Access-Point-Abschnitt (Header + Zeilen, Format identisch
// zur Konsole in Menue 3) fuer ALLE bekannten APs, sortiert nach der
// aktuellen AP-Sortiereinstellung. RAM-Vorgehen wie write_notif_client_section.
void write_notif_ap_section(File &f, uint64_t now, int *written)
{
  int ssid_width = calculate_max_ssid_length(NULL, 0);
  if (ssid_width > AP_CELL_SSID_WIDTH) ssid_width = AP_CELL_SSID_WIDTH;

  // NEU 2.28.6: zurueck auf lokales Stack-Array (kein globaler Scratch-
  // Puffer mehr) - unproblematisch, da hier ohnehin kein Vendor-Lookup
  // mehr in die Tiefe geht (s. Kommentar weiter oben).
  uint8_t ap_sorted[MAX_APS_TRACKED];
  int live_n = 0;
  for (int i = 0; i < aps_known_count; i++) {
    if (! ap_slot_free(i)) ap_sorted[live_n++] = i;
  }
  sort_aps(ap_sorted, live_n, now);

  // NEU 2.28.6: Vendor-Lookup fuer ntfy grundsaetzlich deaktiviert (s.
  // Kommentar weiter oben) - unabhaengig von show_vendors_in_menu3 wird
  // die Liste immer so erzeugt, als waere die Einstellung aus.
  const bool want_vendor = false;

  if (want_vendor) {
    f.printf_P(PSTR(" # [%-*.*s] MAC-Adresse   Hersteller\r\n"), ssid_width, ssid_width, "SSID");
  } else {
    f.printf_P(PSTR(" # [%-*.*s] %6s %2s  %s Age MAC-Adresse\r\n"), ssid_width, ssid_width, "SSID", "Ger", "ch", "dB");
  }
  f.println(F("-------------------------------------------------------------"));

  for (int a = 0; a < live_n; a++) {
    print_ap_cell(ap_sorted[a], ssid_width, false, now, want_vendor, &f);
    f.println();
    (*written)++;
    yield();
  }
  if (live_n == 0) f.println(F(" (keine Access Points)"));
  f.println(F("-------------------------------------------------------"));
}

// NEU 2.28.0: Erzeugt den ntfy-Dateianhang. Die Ausgabe nutzt jetzt
// dieselben Zeilen-Formatierungsfunktionen wie die Konsole
// (print_client_cell()/print_ap_cell()) und beruecksichtigt daher Vendor-
// Lookup und die aktuell eingestellte Sortierung exakt wie am Bildschirm.
// Modus 0 ("ganze Liste") enthaelt jetzt - wie die Sicherung ueber Menue 5 -
// sowohl Clients als auch Access Points, nicht mehr nur Clients.
int build_notif_attachment()
{
  File f = LittleFS.open(NOTIF_TMP_FILE, "w");
  if (!f) return -1;

  uint64_t now = effective_now();
  int written = 0;

  // NEU 2.28.0: "Von:" zeigt jetzt den konfigurierten Message-Header-Text
  // (Punkt 6 im Benachrichtigungsmenue) statt der WLAN-SSID.
  // NEU 2.30.63, ZURUECKGENOMMEN in 2.30.64: kurzzeitig nur fuer die Modi
  // 1/2/3 geschrieben, in der Annahme, load_scenario_file() bräuchte fuer
  // Modus 0 eine Datei OHNE fuehrende Zusatzzeilen. Das war unnoetig
  // vorsichtig: der Loader liest zeilenweise nach Praefix ("DEVICE: ",
  // "BEACON: ", "# SETTINGS", "key=val") und ueberspringt jede nicht
  // erkannte Zeile folgenlos (kein skipped-Zaehler, keine Fehlermeldung) -
  // "Von: ..." und die "="-Trennzeile stoeren ihn also nicht. Der Header
  // steht daher wieder fuer ALLE Modi inkl. 0, die Datei bleibt trotzdem
  // ueber Menue 6 "l+Zahl" ladbar.
  if (ntp_synced) {
    // WICHTIG: Verwende current_unix_time_with_tz() statt effective_now()!
    // effective_now() ist relatives Alter, nicht Unix-Zeit!
    time_t tz_now = current_unix_time_with_tz();
    struct tm* timeinfo = localtime(&tz_now);
    f.printf_P(PSTR("Von: %s | Zeitstempel: %04d-%02d-%02d %02d:%02d:%02d | Programmversion: v%s\r\n"),
      notif_header_text,
      timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
      timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, FIRMWARE_VERSION);
  } else {
    f.printf_P(PSTR("Von: %s | Zeitstempel: nicht verfuegbar (kein NTP) | Programmversion: v%s\r\n"),
      notif_header_text, FIRMWARE_VERSION);
  }
  f.println(F("==============================================================="));

  // NEU 2.28.6: Vendor-Cache wird fuer ntfy nicht mehr benoetigt - der
  // Lookup ist hier grundsaetzlich deaktiviert (s. Kommentar bei
  // write_notif_client_section).

  if (notif_content_mode == 0) {
    // NEU 2.30.63: Anhang im Sicherungsformat statt Konsolenformat -
    // direkter Aufruf der gemeinsamen Schreibfunktion, identisch zur ueber
    // RETURN/GPIO0 erzeugten Datei. Kein malloc mehr noetig (der bisherige
    // 2000-Byte-Sortierpuffer entfaellt), da die Sortierung im
    // # SETTINGS-Block mitgespeichert und beim Laden angewendet wird.
    written += write_scenario_plaintext(f, now);

  } else if (notif_content_mode == 3) {
    // Modus 3: alle Access Points - Format wie Konsole Punkt 3.
    f.printf_P(PSTR("# WiFi-Monitor - alle bekannten Access Points: %d\r\n"), aps_known_live_count());
    f.println(F("==============================================================="));
    write_notif_ap_section(f, now, &written);
    f.printf_P(PSTR("# Ausgegeben von WiFi-Monitor v%s\r\n"), FIRMWARE_VERSION);

  } else {
    // Modus 1 (eine SSID) oder 2 (mehrere SSIDs): Clients zu gefilterten
    // SSIDs, Format wie Konsole Menue 3a.
    f.printf_P(PSTR("# WiFi-Monitor - Clients zu SSID-Filter: %s\r\n"), notif_ssid_filter);
    f.println(F("==============================================================="));

    char filter_copy[128];
    strncpy(filter_copy, notif_ssid_filter, 127);
    filter_copy[127] = '\0';

    // NEU 2.12.0: Alle SSID-Filter auf einmal in einer Liste sammeln
    // statt separaten Sektion für jede SSID
    // NEU 2.21.0 OPTIMIZATION (Punkt 3.1): int zu uint16_t
    // BUGFIX 2.30.10: all_matches[]/ap_matches[] (unten, in der Schleife)
    // jetzt auf malloc()/free() umgestellt - siehe Kommentar beim
    // indices[]-Fix oben in diesem selben Funktion.
    uint16_t *all_matches = (uint16_t*) malloc(MAX_CLIENTS_TRACKED * sizeof(uint16_t));
    if (all_matches == NULL) {
      f.close();
      return -1;
    }
    int all_match_count = 0;

    char* saveptr = NULL;
    char* tok = strtok_r(filter_copy, ",", &saveptr);
    while (tok != NULL) {
      while (*tok == ' ') tok++;
      int tl = strlen(tok);
      while (tl > 0 && tok[tl - 1] == ' ') { tok[tl - 1] = '\0'; tl--; }

      if (tl > 0) {
        // Finde alle APs mit dieser SSID
        // NEU 2.21.0 OPTIMIZATION (Punkt 3.1): int zu uint8_t
        uint8_t *ap_matches = (uint8_t*) malloc(MAX_APS_TRACKED * sizeof(uint8_t));
        if (ap_matches == NULL) {
          free(all_matches);
          f.close();
          return -1;
        }
        int ap_match_count = 0;
        for (int a = 0; a < aps_known_count; a++) {
          if (ap_slot_free(a)) continue;  // NEU 2.29.10: stale ssid sonst falsch positiv
          if (strcmp((const char*)aps_known[a].ssid, tok) == 0) {
            ap_matches[ap_match_count] = a;
            ap_match_count++;
          }
        }

        // Finde alle Clients zu diesen APs
        for (int u = 0; u < clients_known_count; u++) {
          bool match = false;
          for (int k = 0; k < ap_match_count; k++) {
            if (clients_known[u].ap_idx == ap_matches[k]) {
              match = true;
              break;
            }
          }
          if (match && all_match_count < MAX_CLIENTS_TRACKED) {
            all_matches[all_match_count++] = u;
          }
        }
        free(ap_matches);
      }
      tok = strtok_r(NULL, ",", &saveptr);
    }

    // Sortiere und zeige wie Konsole Menue 3a
    sort_clients(all_matches, all_match_count, now);
    write_notif_client_section(f, all_matches, all_match_count, now, &written);
    f.printf_P(PSTR("# Ausgegeben von WiFi-Monitor v%s\r\n"), FIRMWARE_VERSION);
    free(all_matches);
  }

  f.close();
  return written;
}

// Verbindet sich kurzzeitig mit dem konfigurierten WLAN, sendet den
// aktuellen Anhang per HTTPS-PUT an ntfy.sh und stellt danach das
// Promiscuous-Sniffing wieder her. WICHTIG: Waehrend des Versands (WLAN-
// Verbindung + Upload) kann der ESP8266 wegen des einzelnen Funkchips
// NICHT gleichzeitig mitsniffen - das pausiert fuer die Dauer des
// Versands automatisch und laeuft danach normal weiter.
bool notif_send_now(const char* file_path)
{
  ram_debug_sample(RDP_NTFY_START);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
  CallChainGuard __cc_guard(RDP_NTFY_START);  // NEU 2.30.35: Call-Chain-Erweiterung
  if (notif_wifi_ssid[0] == '\0' || notif_wifi_pass[0] == '\0' || notif_channel[0] == '\0') {
    Serial.println(F(" Benachrichtigung: WLAN-SSID, Passwort oder ntfy-Kanalname nicht gesetzt - Versand uebersprungen."));
    return false;
  }
  
  // NEU 2.20.8 BUG4: Heap-Check - mit 350 Clients + 75 APs wird RAM kritisch
  unsigned heap_free = ESP.getFreeHeap();
  if (heap_free < 1800) {  // Mindestens 8KB freier RAM erforderlich
    Serial.printf_P(PSTR(" Benachrichtigung: Unzureichend freier RAM (%u Byte) - Versand uebersprungen.\r\n"), heap_free);
    return false;
  }
  
  led_force_off();  // NEU 2.17.6: zeitkritischer Vorgang - Status-LED aus

  int device_count = file_path ? 1 : build_notif_attachment();
  if (device_count < 0) {
    Serial.println(F(" Benachrichtigung: Anhang konnte nicht erzeugt werden (LittleFS-Fehler)."));
    return false;
  }
  if (file_path && (!notif_channel[0] || !notif_wifi_ssid[0] || !notif_wifi_pass[0])) {
    Serial.println(F(" Datei-Versand: WLAN-SSID, Passwort oder ntfy-Kanalname nicht gesetzt.")); return false;
  }
  Serial.printf_P(PSTR(" Benachrichtigung: sende %s per ntfy.sh (Sniffing pausiert kurz) ...\r\n"), file_path ? file_path : "Geraeteliste");

  wifi_promiscuous_enable(disable);
  // Kompletter Moduswechsel (OFF -> STA) statt nur WiFi.mode(WIFI_STA):
  // ohne den Zwischenschritt ueber WIFI_OFF blieb der Funk offenbar in
  // einem Zwischenzustand haengen (vermutlich durch das vorherige
  // wifi_set_channel()/wifi_promiscuous_enable() bei der Reaktivierung
  // des Sniffings) - dadurch schlug der ZWEITE Versandversuch in Folge
  // regelmaessig fehl, obwohl der erste nach einem Neustart klappte.
  WiFi.mode(WIFI_OFF);
  delay(200);
  WiFi.mode(WIFI_STA);
  delay(100);
  ram_debug_sample(RDP_NTFY_HTTP_BEGIN);  // NEU 2.30.34: passive RAM-/Stack-Diagnose (vor WiFi.begin/Verbindungsaufbau)
  WiFi.begin(notif_wifi_ssid, notif_wifi_pass);

  uint32_t start = millis();
  bool connected = false;
  while (millis() - start < 15000) {
    if (WiFi.status() == WL_CONNECTED) { connected = true; break; }
    delay(200);
    yield();
  }

  bool ok = false;
  if (!connected) {
    Serial.println(F(" Benachrichtigung: WLAN-Verbindung fehlgeschlagen (Timeout nach 15s)."));
  } else {
    // Reines HTTP statt HTTPS: umgeht axTLS komplett, das auf alten
    // ESP8266-Cores (z.B. 2.4.2, kein BearSSL) mit modernen TLS-Servern
    // wie ntfy.sh oft abstuerzt statt sauber einen Fehler zu melden.
    WiFiClient client;
    client.setTimeout(10000);

    if (!client.connect("ntfy.sh", 80)) {
      Serial.println(F(" Benachrichtigung: Verbindung zu ntfy.sh fehlgeschlagen."));
    } else {
      ram_debug_sample(RDP_NTFY_FILE_OPEN);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
      File f = LittleFS.open(file_path ? file_path : NOTIF_TMP_FILE, "r");
      if (!f) {
        Serial.println(F(" Benachrichtigung: Anhangsdatei konnte nicht geoeffnet werden."));
      } else {
        size_t filesize = f.size();
        // NEU 2.15.0: Title Header mit Absender-SSID hinzufügen
        client.printf_P(PSTR("PUT /%s HTTP/1.1\r\n"), notif_channel);
        client.print(F("Host: ntfy.sh\r\n"));
        client.print(F("User-Agent: Firefly-WiFi-Monitor\r\n"));
        // NEU 2.20.8 BUG2: notif_header_text verwenden (nicht notif_wifi_ssid!)
        client.printf_P(PSTR("Title: %s\r\n"), notif_header_text);
        // NEU 2.28.0: Dateiname aus Message-Header + Listentyp statt fest "liste.txt"
        // NEU 2.30.64: von 48 auf 56 vergroessert - das neue Schema
        // "YYMMDD_HHMMSS_[Name].txt" ist mit 13+1+32+4+1=51 Byte im
        // ungünstigsten Fall (voll ausgeschöpfter 32-Zeichen-Name) laenger
        // als das alte "[Name]_[Typ].txt" (max. 32+1+5+4+1=43 Byte).
        // NEU 2.30.65: von 56 auf 60 vergroessert - ungünstigster Fall (NTP,
        // Modus 2, 32-Zeichen-Name): 13+1+32+6+4+1 = 57 Byte.
        char notif_filename[64];
        if (file_path) { const char *base=strrchr(file_path,'/'); base=base?base+1:file_path; strncpy(notif_filename,base,sizeof(notif_filename)-1); notif_filename[sizeof(notif_filename)-1]='\0'; }
        else build_notif_filename(notif_filename, sizeof(notif_filename));
        client.printf_P(PSTR("Filename: %s\r\n"), notif_filename);
        client.printf_P(PSTR("Content-Length: %u\r\n"), (unsigned)filesize);
        client.print(F("Content-Type: text/plain\r\n"));
        client.print(F("Connection: close\r\n\r\n"));
        ram_debug_sample(RDP_NTFY_REQUEST_BUILD);  // NEU 2.30.34: passive RAM-/Stack-Diagnose (Request-Header aufgebaut)

        uint8_t buf[256];
        while (f.available()) {
          size_t n = f.read(buf, sizeof(buf));
          ram_debug_sample(RDP_NTFY_FILE_READ);  // NEU 2.30.34: passive RAM-/Stack-Diagnose (waehrend Datei-Uebertragung)
          client.write(buf, n);
          yield();
        }
        f.close();

        ram_debug_sample(RDP_NTFY_SEND);  // NEU 2.30.34: passive RAM-/Stack-Diagnose (Antwort wird erwartet)
        uint32_t wait_start = millis();
        while (client.connected() && millis() - wait_start < 5000) {
          if (client.available()) {
            String line = client.readStringUntil('\n');
            if (line.startsWith("HTTP/")) {
              Serial.printf_P(PSTR(" Benachrichtigung: Antwort %s\r\n"), line.c_str());
              ok = (line.indexOf("200") > 0);
            }
          }
          yield();
        }
        client.stop();
      }
    }
  }

  WiFi.disconnect(true);
  delay(100);

  // Vollstaendige Reinitialisierung, identisch zur Sequenz in setup().
  // Nur wifi_set_promiscuous_rx_cb()+wifi_promiscuous_enable() zu rufen
  // reichte nicht aus - der Funk blieb nach WiFi.begin()/disconnect() in
  // einem Zustand haengen, in dem promisc_cb() keine Pakete mehr erhielt
  // ("taub" nach dem Versand). wifi_set_opmode()/wifi_set_channel()
  // muessen ebenfalls erneut gesetzt werden.
  wifi_promiscuous_enable(disable);
  wifi_set_opmode(STATION_MODE);
  wifi_set_channel(channel);
  wifi_set_promiscuous_rx_cb(promisc_cb);
  wifi_promiscuous_enable(enable);
  nothing_new = 0;

  if (!file_path) LittleFS.remove(NOTIF_TMP_FILE);

  if (ok) { if(file_path) Serial.printf_P(PSTR(" Datei erfolgreich gesendet: %s\r\n"),file_path); else Serial.printf_P(PSTR(" Benachrichtigung: %d Geraete erfolgreich gesendet.\r\n"), device_count); }
  else Serial.println(F(" Benachrichtigung: Versand vermutlich fehlgeschlagen (siehe Meldungen oben)."));

  ram_debug_sample(RDP_NTFY_END);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
  return ok;
}
bool notif_send_file(const char *path)
{
  if (!path || !path[0]) { Serial.println(F(" Datei-Versand: ungueltiger Pfad.")); return false; }
  if (!notif_channel[0] || !notif_wifi_ssid[0] || !notif_wifi_pass[0]) { Serial.println(F(" Datei-Versand: WLAN-SSID, Passwort oder ntfy-Kanalname nicht gesetzt.")); return false; }
  if (!LittleFS.exists(path)) { Serial.println(F(" Datei-Versand: Datei nicht gefunden.")); return false; }
  return notif_send_now(path);
}

const char* format_number_with_dots(uint32_t value)
{
    static char buf[20];
    char tmp[20];

    sprintf_P(tmp, PSTR("%lu"), (unsigned long)value);

    int len = strlen(tmp);
    int dots = (len - 1) / 3;
    int newlen = len + dots;

    buf[newlen] = '\0';

    int i = len - 1;
    int j = newlen - 1;
    int count = 0;

    while (i >= 0) {
        if (count == 3) {
            buf[j--] = '.';
            count = 0;
        }
        buf[j--] = tmp[i--];
        count++;
    }

    return buf;
}

void menu_enter_info()
{
  menu_state = STATE_INFO;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  print_logo();
  Serial.println(F("======================================================="));
  Serial.println(F(" Info"));
  Serial.println(F("======================================================="));
  Serial.println(F(" Herkunft (Original-Basis):"));
  Serial.println(F("  ESP8266 RTOS Sniffer-Demo (Espressif)"));
  Serial.println(F("  Arduino-Portierung: RandDruid/esp8266-deauth,"));
  Serial.println(F("  kripthor/WiFiBeaconJam"));
  Serial.println(F("  Ueberarbeitung: Ray Burnette (hackster.io/rayburne)"));
  Serial.println();
  Serial.println(F(" Diese Version:"));
  Serial.printf_P(PSTR("  WiFi-Monitor V%s  (%s)\r\n"), FIRMWARE_VERSION, FIRMWARE_BUILD_DATE);
  Serial.println(F("  Created 2026 by Firefly  enmgzirn@yahoo.de"));
  Serial.println();
  Serial.println(F(" Terminal mit VT100/ANSI erforderlich"));
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" NTP-Zeit:"));
  if (ntp_synced) {
    time_t now = current_unix_time_with_tz();
    Serial.printf_P(PSTR("  Synchronisiert (Server: %s)\r\n"), ntp_server);
    Serial.printf_P(PSTR("  Aktuell (UTC%+d%s): %s"), ntp_timezone_hours,
                   (dst_enabled && eu_dst_active(current_unix_time())) ? "+1 DST" : "", ctime(&now));
    if (dst_enabled) {
      bool active = eu_dst_active(current_unix_time());
      Serial.printf_P(PSTR("\r  %s\r\n"), active ? " Sommerzeit aktiv (+1h)" : " Winterzeit (kein Zuschlag)");
      Serial.println(F("  (EU-Regel: letzter Sonntag Maerz/Oktober)"));
    }
  } else if (ntp_enabled) {
    Serial.println(F("  Aktiviert, aber noch nicht synchronisiert."));
  } else {
    Serial.println(F("  Deaktiviert (Einstellungen > 9)."));
  }
  Serial.println();
  {
    uint32_t uptime_sec = millis() / 1000;
    uint32_t days = uptime_sec / 86400;
    uint32_t hh = (uptime_sec % 86400) / 3600;
    uint32_t mm = (uptime_sec % 3600) / 60;
    uint32_t ss = uptime_sec % 60;
    Serial.printf_P(PSTR("  Betriebszeit seit letztem Reset: %u %02u:%02u:%02u\r\n"), days, hh, mm, ss);
  }
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" ESP-Hardware:"));
  Serial.printf_P(PSTR("  Chip-ID: 0x%08X   CPU-Takt: %d MHz\r\n"), ESP.getChipId(), ESP.getCpuFreqMHz());
  Serial.println();
  {
    unsigned flash_chip_total = (unsigned)ESP.getFlashChipRealSize();
    unsigned sketch_used = (unsigned)ESP.getSketchSize();
    unsigned sketch_free = (unsigned)ESP.getFreeSketchSpace();
    unsigned sketch_partition_total = sketch_used + sketch_free;
    
    // NEU 2.20.9 BUG9: Validierung - sketch_free darf nicht größer als sketch_partition_total sein
    if (sketch_free > sketch_partition_total) sketch_free = 0;
    
    int sketch_pct_free = (sketch_partition_total > 0) ? (int)((100.0 * sketch_free) / sketch_partition_total + 0.5) : 0;
    
    FSInfo fs_info;
    LittleFS.info(fs_info);
    unsigned fs_total = fs_info.totalBytes;
    unsigned fs_used = fs_info.usedBytes;
    unsigned fs_free = fs_total - fs_used;
    
    // NEU 2.20.9 BUG9: Validierung - fs_free darf nicht größer als fs_total sein
    if (fs_free > fs_total) fs_free = 0;
    
    int fs_pct_free = (fs_total > 0) ? (int)((100.0 * fs_free) / fs_total + 0.5) : 0;
    
    unsigned heap_free = (unsigned)ESP.getFreeHeap();
    // NEU 2.30.32: RAM-Referenzwert von 80.000 auf empirisch ermittelte 49.024 Byte
    // korrigiert (siehe RAM_REFERENCE_BYTES) - Format/Text/Reihenfolge unveraendert.
    int heap_pct_free = (heap_free > 0 && heap_free < RAM_REFERENCE_BYTES) ? (int)((100.0 * heap_free) / RAM_REFERENCE_BYTES + 0.5) : 0;
    
    
    
    
    Serial.printf_P(PSTR("  Flash gesamt:     %s Byte\r\n"), format_number_with_dots(flash_chip_total));
    Serial.printf_P(PSTR("  Sketch-Partition: %s Byte %d%% frei\r\n"),
                  format_number_with_dots(sketch_partition_total), sketch_pct_free);
    Serial.printf_P(PSTR("  Datei-Partition:  %s Byte %d%% frei\r\n"),
                  format_number_with_dots(fs_total), fs_pct_free);
    // BUGFIX 2.30.36: format_number_with_dots() liefert einen Zeiger auf einen
    // EINZIGEN statischen Puffer, der bei jedem Aufruf ueberschrieben wird.
    // Zwei Aufrufe innerhalb DESSELBEN printf_P()-Statements (wie zuvor hier:
    // Referenzwert UND heap_free) haben deshalb je nach - nicht garantierter -
    // Auswertungsreihenfolge der Funktionsargumente denselben (falschen) Text
    // an beiden %s-Stellen ausgegeben. Fix: Referenzwert-String vorher in
    // einen eigenen, unabhaengigen Puffer kopieren.
    char ram_ref_buf[20];
    strncpy(ram_ref_buf, format_number_with_dots(RAM_REFERENCE_BYTES), sizeof(ram_ref_buf) - 1);
    ram_ref_buf[sizeof(ram_ref_buf) - 1] = '\0';
    Serial.printf_P(PSTR("  RAM :                %s Byte %d%% frei (%s Byte)\r\n"),
                  ram_ref_buf, heap_pct_free, format_number_with_dots(heap_free));
  }
  Serial.println();
  // NEU 2.29.0: Akkuspannung (ADC), zweistellig hinter dem Komma
  if (adc_calib_raw > 0) {
    uint16_t mv = adc_read_voltage_mv();
    Serial.printf_P(PSTR("  Akku-Spannung: %d.%02d V\r\n"), mv / 1000, (mv % 1000) / 10);
  } else {
    Serial.println(F("  Akku-Spannung: nicht kalibriert (Einstellungen > b)"));
  }
  Serial.println();
  {
    unsigned sketch_used = (unsigned)ESP.getSketchSize();
    FSInfo fs_info;
    LittleFS.info(fs_info);
    unsigned fs_used = fs_info.usedBytes;
    int file_count = 0;
    Dir dircount = LittleFS.openDir("/");
    while (dircount.next()) file_count++;
    
    // NEU 2.20.10 BUG10: Max Scan Kapazitäten anzeigen (in v2211 Optimization wieder hinzugefügt)
    Serial.printf_P(PSTR("  Max Scan: Clients=%d APs=%d\r\n"), MAX_CLIENTS_TRACKED, MAX_APS_TRACKED);
    Serial.printf_P(PSTR("  Programmgröße:           %s Byte\r\n"), format_number_with_dots(sketch_used));
    Serial.printf_P(PSTR("  Gespeicherte Dateien: %d   %s Byte\r\n"), file_count, format_number_with_dots(fs_used));
  }
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Backspace/ESC = zurueck zum Menue"));
}

void menu_enter_help()
{
  menu_state = STATE_HELP;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Hilfe"));
  Serial.println(F("======================================================="));
  Serial.println(F(" Was macht dieses Programm?"));
  Serial.println(F("  Der ESP8266 hoert im WLAN-Promiscuous-Modus laufend"));
  Serial.println(F("  Management- und Datenrahmen mit (Beacons, Probe"));
  Serial.println(F("  Requests, Datenrahmen-Header) und zeichnet gesehene"));
  Serial.println(F("  Access Points und Clients mit RSSI, Kanal und"));
  Serial.println(F("  Zeitpunkt auf."));
  Serial.println();
  Serial.println(F(" Menuepunkte:"));
  Serial.println(F("  1  Laufende Live-Ausgabe aller neuen Sichtungen."));
  Serial.println(F("  2  Funkverkehr gezielt nach MAC-Adresse oder"));
  Serial.println(F("     Pakettyp filtern (Untermenue mit Checkbox-"));
  Serial.println(F("     Kriterien, Beacons/Probes/Management/Control/Data)."));
  Serial.println(F("     Zusaetzlich: MAC-Adresse nachschlagen (bekannt?"));
  Serial.println(F("     AP oder Client? an welchem AP angemeldet?)."));
  Serial.println(F("  3  Alle Clients einer gewaehlten SSID als sortierbare,"));
  Serial.println(F("     automatisch aktualisierte Liste mit RSSI-Trend."));
  Serial.println(F("     S+Zahl+Enter statt Zahl+Enter: zeigt die Clients"));
  Serial.println(F("     aller Access Points mit dieser SSID zusammen."));
  Serial.println(F("  4  Watchlist frei waehlbarer MAC-Adressen mit"));
  Serial.println(F("     Beschreibung, automatisch aktualisiert. MACs auf"));
  Serial.println(F("     der Watchlist werden ueberall blau markiert."));
  Serial.println(F("  5  Aktueller Scan speichern."));
//  Serial.println(F("     im Flash sichern."));
  Serial.println(F("  6  Gesicherte Dateien anzeigen,laden,loeschen"));
  Serial.println(F("  7  HTTP-Datei-Server: Flashinhalt per Browser"));  // NEU 2.30.0
  Serial.println(F("     verwalten (nutzt das unter 'Benachrichtigung'"));
  Serial.println(F("     hinterlegte WLAN). Beliebige Taste = beenden."));
  Serial.println(F("  e  Einstellungen"));
  Serial.println(F("  i  Info: Herkunft, Version, ESP-/Speicherdaten."));
  Serial.println(F("  v  Versorgungsbereiche: APs, zwischen denen ein Client"));  // NEU 2.30.60
  Serial.println(F("     gewechselt hat, werden als Gruppe angezeigt."));
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Backspace/ESC = zurueck zum Menue"));
}

// NEU 2.12.0: Parst kommagetrennte AP-Nummern (z.B. "1,5,7")
// Speichert die Indizes in selected_ap_indices[] und selected_ap_count
// Liefert true, wenn gueltig; false bei ungueltig (Nummer > aps_known_count)
bool parse_multi_ap_selection(const char *input)
{
  selected_ap_count = 0;
  const char *p = input;
  
  while (*p && selected_ap_count < MAX_APS_TRACKED) {
    int num = 0;
    bool found_digit = false;
    
    while (*p && isdigit(*p)) {
      num = num * 10 + (*p - '0');
      p++;
      found_digit = true;
    }
    
    if (found_digit) {
      if (num >= 0 && num < aps_known_count && !ap_slot_free(num)) {
        // Pruefe auf Duplikate
        bool already_selected = false;
        for (int i = 0; i < selected_ap_count; i++) {
          if (selected_ap_indices[i] == num) {
            already_selected = true;
            break;
          }
        }
        if (!already_selected) {
          selected_ap_indices[selected_ap_count++] = num;
        }
      } else {
        // Ungueltige Nummer
        return false;
      }
    }
    
    if (*p == ',') {
      p++;
    } else if (*p != '\0') {
      // Ungueltige Zeichen
      return false;
    }
  }
  
  return selected_ap_count > 0;
}

// NEU 2.12.0: Zeigt Clients aus mehreren (vom Nutzer gewaehlten) APs kombiniert
// selected_ap_indices[] und selected_ap_count muessen vorher gesetzt sein
// Diese Funktion wird nach "s1,5,7" + Enter aufgerufen
void menu_enter_ssid_list_multi()
{
  menu_state = STATE_SSID_LIST;
  current_list_mode = 3;  // Modus 3 = Multi-AP
  led_force_off();  // NEU 2.17.6: zeitkritisch (lange Listenausgabe) - Status-LED aus
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  
  // NEU 2.27.4: Vendor-Cache beim Menueeintritt initialisieren (No-Op bei
  // Redraw waehrend laufender Sitzung) - analog zu Variante 1/2. Wird hier
  // zusaetzlich benoetigt, da Variante 3 direkt aus Menue 3 heraus (S mit
  // Kommaliste) erreichbar ist, ohne vorher Variante 1/2 durchlaufen zu haben.
  vendorCache_begin();

  if (selected_ap_count <= 0 || selected_ap_count > MAX_APS_TRACKED) {
    Serial.println(F(" Fehler: Keine APs gewählt."));
    return;
  }

  // Alle Clients sammeln, die zu einem dieser APs gehoeren
  // NEU 2.21.1 OPTIMIZATION: uint16_t statt int (konsistent mit sort_clients)
  // BUGFIX 2.30.10: matches[] jetzt auf malloc()/free() umgestellt (Heap
  // statt Stack) - siehe ausfuehrlichen Kommentar in menu_enter_ssid_list()
  // zum selben Fix (2000 Byte Stack-Ersparnis waehrend der Funktionslaufzeit).
  uint16_t *matches = (uint16_t*) malloc(MAX_CLIENTS_TRACKED * sizeof(uint16_t));
  if (matches == NULL) {
    Serial.println(F(" Fehler: kein Speicher fuer die Geraeteliste verfuegbar."));
    return;
  }
  uint16_t match_count = 0;
  for (int u = 0; u < clients_known_count; u++) {
    for (int k = 0; k < selected_ap_count; k++) {
      int ap_idx = selected_ap_indices[k];
      if (ap_idx >= 0 && ap_idx < aps_known_count && !ap_slot_free(ap_idx)) {
        if (clients_known[u].ap_idx == ap_idx) {
          matches[match_count] = u;
          match_count++;
          break;
        }
      }
    }
  }

  uint64_t now = effective_now();

  // NEU 2.17.2, geaendert 2.29.7: Ignore-Filter (Taste 'i') - blendet nur noch AP-Wechsler aus, "out"-Eintraege bleiben sichtbar
  if (list_hide_inactive) {
    int filtered_count = 0;
    for (int i = 0; i < match_count; i++) {
      if (!client_is_switched(matches[i], now)) {
        matches[filtered_count++] = matches[i];
      }
    }
    match_count = filtered_count;
  }

  sort_clients(matches, match_count, now);

  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" %d Geraete aus %d APs:\r\n"), match_count, selected_ap_count);
  // NEU 2.14.0: Zeige SSID für jeden AP
  Serial.print(F(" "));
  for (int i = 0; i < selected_ap_count; i++) {
    if (i > 0) Serial.print(F(","));
    int ap_idx = selected_ap_indices[i];
    if (ap_idx >= 0 && ap_idx < aps_known_count && !ap_slot_free(ap_idx)) {
      Serial.printf_P(PSTR("%d (%s)"), ap_idx, (const char*)aps_known[ap_idx].ssid);
    } else {
      Serial.printf_P(PSTR("%d"), ap_idx);  // Fallback falls Index ungültig
    }
  }
  Serial.println();
  Serial.println(F("======================================================="));
  print_sort_legend();
  Serial.printf_P(PSTR(" RSSI-Trend-Schwelle: %d dB (t=aendern)\r\n"), rssi_trend_threshold);
  Serial.printf_P(PSTR(" Ignoriere AP-Wechsel/Out: %s (i=toggle)\r\n"), list_hide_inactive ? "EIN" : "AUS");
  Serial.printf_P(PSTR(" Aktualisierung: %ds (+ = +5s, - = -5s)\r\n"), list_refresh_sec);
  // NEU 2.27.4: gleiches Flag wie Variante 1/2 (show_vendors_in_menu3a) -
  // eine gemeinsame Session-Einstellung fuer alle drei Varianten.
  Serial.printf_P(PSTR(" Hersteller anzeigen: %s (v=toggle)\r\n"), show_vendors_in_menu3a ? "EIN" : "AUS");
  // NEU 2.30.49: Auftrag 2 - jetzt auch in Modus 3 verfuegbar.
  Serial.println(F(" b = Hintergrundverkehr-Statistik dieser APs starten"));
  Serial.println(F("-------------------------------------------------------"));
  
  // NEU 2.27.4: Bei Vendor-Anzeige immer einspaltig (analog Variante 1/2)
  bool two_col = false;
  if (!show_vendors_in_menu3a) {
    two_col = (two_col_threshold_devices > 0 && match_count > two_col_threshold_devices);
  }
  
  if (show_vendors_in_menu3a) {
    Serial.println(F(" MAC          AP  Age  db      Hersteller"));
    Serial.println(F("-------------------------------------------------------"));
  } else if (two_col) {
    Serial.println(F(" MAC          AP  Age  db      MAC          AP  Age  db"));
    Serial.println(F("----------------------------------------------------------"));
  } else {
    Serial.println(F(" MAC          AP  Age  db"));
    Serial.println(F("-------------------------------------------------------"));
  }

  int half = two_col ? (match_count + 1) / 2 : match_count;
  for (int i = 0; i < half; i++) {
    Serial.print(F(" "));
    print_client_cell_ap_mode(matches[i], selected_ap_indices, selected_ap_count, now);
    if (show_vendors_in_menu3a) {
      // NEU 2.27.4: On-Demand Vendor-Lookup ueber den Cache (analog Var.1/2)
      Serial.print(F(" "));
      String vendor = vendorCache_lookup_or_search(clients_known[matches[i]].station);
      Serial.print(vendor.c_str());
    } else if (two_col) {
      int right_i = half + i;
      if (right_i < match_count) {
        Serial.print(F(" "));
        print_client_cell_ap_mode(matches[right_i], selected_ap_indices, selected_ap_count, now);
      }
    }
    Serial.println();
    yield();
  }
  if (match_count == 0) {
    Serial.println(F(" (keine Geraete gefunden)"));
  }

  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Backspace = zurueck zur SSID-Auswahl, ESC = Menue."));
  last_list_refresh_time = millis() / 1000;
  free(matches);  // NEU 2.30.10: siehe Kommentar bei der malloc()-Stelle oben
}

// NEU 2.13.0: Berechnet die laengste SSID-Laenge in der aktuellen Liste
// Das wird genutzt, um die Spaltenbreite dynamisch anzupassen (statt feste 32 Zeichen)
// ap_indices = Array mit AP-Indizes (NULL wenn alle APs)
// ap_count = Anzahl der APs (0 wenn alle APs)
int calculate_max_ssid_length(uint8_t *ap_indices, int ap_count)
{
  int max_len = 4;  // Mindestens "SSID" (Headertext)
  
  if (ap_indices == NULL || ap_count == 0) {
    // Alle APs durchsuchen
    for (int a = 0; a < aps_known_count; a++) {
      if (ap_slot_free(a)) continue;  // NEU 2.29.10: stale ssid sonst faelschlich mitgezaehlt
      int len = strlen((const char*)aps_known[a].ssid);
      if (len > max_len) max_len = len;
    }
  } else {
    // Nur gewählte APs durchsuchen
    for (int k = 0; k < ap_count; k++) {
      int ap_idx = ap_indices[k];
      if (ap_idx >= 0 && ap_idx < aps_known_count && !ap_slot_free(ap_idx)) {
        int len = strlen((const char*)aps_known[ap_idx].ssid);
        if (len > max_len) max_len = len;
      }
    }
  }
  
  // Begrenzung auf max 32 (kannst du anpassen)
  if (max_len > 32) max_len = 32;
  // NEU 2.17.3 Bugfix: bisher wurden hier faelschlich +2 Zeichen fuer
  // "Abstaende" addiert - dadurch war die Kuerzung nie so knapp wie
  // eigentlich beabsichtigt. Ersatzlos gestrichen.
  return max_len;
}

// NEU 2.13.0: Prueft ob ein Kanal im aktiven Filter liegt
// Wenn channel_filter == "alle", sind alle Kanäle erlaubt
// Wenn z.B. "1,6,11", nur diese Kanäle
bool is_channel_allowed(int channel)
{
  if (strcmp(channel_filter, "alle") == 0) {
    return true;  // Alle Kanäle erlaubt
  }
  
  // Parse kommagetrennte Liste
  char filter_copy[64];
  strncpy(filter_copy, channel_filter, 63);
  filter_copy[63] = '\0';
  
  char* saveptr = NULL;
  char* tok = strtok_r(filter_copy, ",", &saveptr);
  while (tok != NULL) {
    int ch = atoi(tok);
    if (ch == channel) {
      return true;  // Kanal gefunden
    }
    tok = strtok_r(NULL, ",", &saveptr);
  }
  
  return false;  // Kanal nicht erlaubt
}

// NEU 2.17.5: Entfernt alle Clients aelter als max_age_sec aus clients_known[]
// (kompaktiert das Array). Gibt die Anzahl geloeschter Eintraege zurueck.
int delete_old_clients(int max_age_sec, uint64_t now)
{
  int removed = 0;
  int w = 0;
  for (int r = 0; r < clients_known_count; r++) {
    int age = (int)(now - clients_known[r].last_heard);
    if (age > max_age_sec) {
      removed++;
      continue;
    }
    if (w != r) clients_known[w] = clients_known[r];
    w++;
  }
  clients_known_count = w;
  return removed;
}

// NEU 2.17.5: Entfernt alle Access Points aelter als max_age_sec aus
// aps_known[]. NEU 2.29.10: markiert die betroffenen Slots nur noch als
// frei (ap_slot_mark_free()) statt das Array zu verschieben - haelt die
// Indizes aller UEBRIGEN APs stabil (Grundlage fuer die kommende
// Client->AP-Index-Referenz). Kaskadiert jetzt (wie delete_ap_by_index())
// auch auf die zugehoerigen Clients, da dies ein bewusst vom Nutzer
// ausgeloester manueller Vorgang ist (Cleanup-Menue, Schwellwert wird
// aktiv eingegeben) - kein automatischer Hintergrund-Trigger. Gibt die
// Anzahl geloeschter AP-Eintraege zurueck.
int delete_old_aps(int max_age_sec, uint64_t now)
{
  int removed = 0;
  for (int r = 0; r < aps_known_count; r++) {
    if (ap_slot_free(r)) continue;
    int age = (int)(now - aps_known[r].last_heard);
    if (age > max_age_sec) {
      // NEU 2.29.11: kein target_bssid mehr noetig - Vergleich direkt ueber
      // den (stabilen) AP-Index.
      int w = 0;
      for (int c = 0; c < clients_known_count; c++) {
        if (clients_known[c].ap_idx == r) continue;
        if (w != c) clients_known[w] = clients_known[c];
        w++;
      }
      clients_known_count = w;
      ap_slot_mark_free(r);
      removed++;
    }
  }
  return removed;
}

// NEU 2.17.5: Loescht gezielt einen einzelnen AP aus aps_known[] (Punkt 3,
// d+Zahl+Enter). NEU 2.29.10: markiert den Slot nur noch als frei statt
// das Array zu verschieben - die Indizes/Nummern aller anderen APs bleiben
// dadurch unveraendert (vorher ruckten alle nachfolgenden Indizes eins
// nach vorne). NEU 2.29.9: entfernt zusaetzlich alle Clients, die ueber
// die BSSID zu diesem AP gehoeren. Gibt die Anzahl geloeschter Clients
// zurueck, oder -1 bei ungueltigem/bereits freiem Index.

// NEU 2.30.67: Loescht alle APs, die gleichzeitig "old" (Age > 99999 s)
// und ohne jemals gesehenen Client (0/0) sind. ap_slot_mark_free() kuemmert
// sich dabei auch um die Bereinigung der zugehoerigen Roaming-Paare.
int delete_old_empty_aps(uint64_t now)
{
  int removed = 0;
  for (int a = 0; a < aps_known_count; a++) {
    if (ap_slot_free(a)) continue;
    uint32_t age = (uint32_t)(now - aps_known[a].last_heard);
    if (age <= 99999UL) continue;
    bool has_client = false;
    for (int c = 0; c < clients_known_count; c++) {
      if ((c & 0x1F) == 0) yield();
      if (clients_known[c].ap_idx == a) {
        has_client = true;
        break;
      }
    }
    if (has_client) continue;
    ap_slot_mark_free(a);
    removed++;
  }
  return removed;
}


int delete_ap_by_index(int idx)
{
  if (idx < 0 || idx >= aps_known_count || ap_slot_free(idx)) return -1;

  // NEU 2.29.11: kein target_bssid mehr noetig - Vergleich direkt ueber
  // den (stabilen) AP-Index.
  int removed_clients = 0;
  int w = 0;
  for (int r = 0; r < clients_known_count; r++) {
    if (clients_known[r].ap_idx == idx) {
      removed_clients++;
      continue;
    }
    if (w != r) clients_known[w] = clients_known[r];
    w++;
  }
  clients_known_count = w;

  ap_slot_mark_free(idx);
  return removed_clients;
}

void menu_enter_ssid_select()
{
  ram_debug_sample(RDP_AP_LIST);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
  CallChainGuard __cc_guard(RDP_AP_LIST);  // NEU 2.30.35: Call-Chain-Erweiterung
  menu_state = STATE_SSID_SELECT;
  ssid_input_len = 0;
  ssid_select_combined = false;
  ssid_select_delete_mode = false;
  ssid_select_analyze_mode = false;
  ssid_select_timewatch_prefix = false;
  ssid_select_timewatch_mode = false;
  current_list_mode = 0;
  led_force_off();
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" SSID waehlen:"));
  Serial.println(F(" Zahl+Enter = nur dieser AP"));
  Serial.println(F(" S+Zahl+Enter = alle AP mit gleicher SSID"));
  Serial.println(F(" S+Zahl,Zahl,Zahl+Enter = mehrere AP"));
  Serial.println(F(" d+Zahl+Enter = AP loeschen"));
  Serial.println(F(" w+Zahl+Enter = Beacon-Frame analysieren (nur aktive APs)"));
  Serial.printf_P(PSTR(" wt+Zahl+Enter = FrameTrap wartet auf Beacon (max. %d)\r\n"), FRAMETRAP_BEACON_MAX_PENDING);
  Serial.println(F(" tw+Zahl+Enter = TimeWatch aktivieren"));
  Serial.println(F("======================================================="));
  Serial.print(F(" Sort:"));
  for (int f = 0; f <= 5; f++) {
    ApSortField af = (ApSortField) f;
    bool active = (af == current_ap_sort_field);
    Serial.print(F(" "));
    if (active) {
      Serial.print(F("["));
      Serial.print(ap_sort_field_name(af));
      Serial.print(ap_sort_ascending ? "^]" : "v]");
    } else {
      Serial.print(ap_sort_field_name(af));
    }
  }
  Serial.println();
  // NEU 2.27.4: a=Age, m=MAC ergaenzt
  Serial.println(F(" Tasten u/n/g/p/a/m = Sortierung/Richtung"));
  // NEU 2.26.x: Vendor-Anzeige-Hinweis (analog Menue 3a)
  Serial.printf_P(PSTR(" Hersteller anzeigen: %s (v=toggle)\r\n"), show_vendors_in_menu3 ? "EIN" : "AUS");
  // NEU 2.27.4: Auto-Refresh-Hinweis (eigene Tasten +/- statt u/d, siehe
  // Begruendung bei den Variablendefinitionen)
  Serial.printf_P(PSTR(" Aktualisierung: %ds (+ = +5s, - = -5s)\r\n"), ssid_select_refresh_sec);
  Serial.println();
  // NEU 2.26.x: Bei aktiver Vendor-Anzeige immer einspaltig - Ger/ch/dB
  // entfallen dafuer komplett (kein Platz fuer Herstellernamen im
  // zweispaltigen Modus).
  bool two_col = false;
  // NEU 2.29.10: sorted_idx darf nur noch LEBENDE Slots enthalten - freie
  // (geloeschte) Slots werden uebersprungen. Die angezeigte "#"-Nummer
  // bleibt dabei der echte, stabile Array-Index (siehe print_ap_cell()),
  // sie ist nur nicht mehr zwingend luecklos durchnummeriert.
  uint8_t sorted_idx[MAX_APS_TRACKED];
  int live_n = 0;
  for (int i = 0; i < aps_known_count; i++) {
    if (! ap_slot_free(i)) sorted_idx[live_n++] = i;
  }
  if (!show_vendors_in_menu3) {
    two_col = (two_col_threshold_ssids > 0 && live_n >
               two_col_threshold_ssids);
  }
  int ssid_width_left, ssid_width_right = 0;
  // BUGFIX 2.30.18: "now" wird jetzt VOR sort_aps() gebraucht (ueberlauf-
  // sicherer Alters-Vergleich bei AP_SORT_AGE) - deshalb hierher vorgezogen
  // (vorher stand diese Zeile weiter unten, kurz vor der Ausgabeschleife).
  uint64_t now = effective_now();
  sort_aps(sorted_idx, live_n, now);
  if (two_col) {
    uint8_t left_indices[MAX_APS_TRACKED];
    uint8_t left_count = 0;
    int half = (live_n + 1) / 2;
    for (int i = 0; i < half; i++) left_indices[left_count++] =
      sorted_idx[i];
    ssid_width_left = calculate_max_ssid_length(left_indices,
                                                 left_count);
    if (ssid_width_left > AP_CELL_SSID_WIDTH) ssid_width_left =
      AP_CELL_SSID_WIDTH;
    uint8_t right_indices[MAX_APS_TRACKED];
    uint8_t right_count = 0;
    for (int i = half; i < live_n; i++)
      right_indices[right_count++] = sorted_idx[i];
    ssid_width_right = calculate_max_ssid_length(right_indices,
                                                  right_count);
    if (ssid_width_right > AP_CELL_SSID_WIDTH) ssid_width_right =
      AP_CELL_SSID_WIDTH;
  } else {
    ssid_width_left = calculate_max_ssid_length(NULL, 0);
  }

  // DYNAMISCHER HEADER-BLOCK
  if (two_col) {
    // Linke Header-Hälfte - mit 2 Leerzeichen zwischen ch und dB
    char h_buf[96];
    int h_len = snprintf_P(h_buf, sizeof(h_buf), PSTR(" # [%-*.*s] %6s %2s  %s"),
                         ssid_width_left, ssid_width_left, "SSID", "Ger", "ch", "dB");
    h_buf[h_len] = '\0';
    Serial.print(h_buf);
    Serial.print(F(" "));
    
    // Rechte Header-Hälfte
    Serial.printf_P(PSTR(" # [%-*.*s] %6s %2s  %s\r\n"),
                  ssid_width_right, ssid_width_right, "SSID", "Ger", "ch", "dB");
    
    // Trennlinie - um 2 Zeichen verlängert (wegen zusätzlicher Leerzeichen im Header)
    int line_length = (3 + 1 + ssid_width_left + 1 + 1 + 6 + 1 + 2 + 2 + 2) + 1 + 
                      (3 + 1 + ssid_width_right + 1 + 1 + 6 + 1 + 2 + 2 + 2);
    for (int i = 0; i < line_length; i++) Serial.print(F("-"));
    Serial.println();
  } else if (show_vendors_in_menu3) {
    // NEU 2.26.x: Vendor-Modus - Ger/ch/dB entfallen, SSID + MAC + Hersteller
    Serial.printf_P(PSTR(" # [%-*.*s] MAC-Adresse   Hersteller\r\n"),
                  ssid_width_left, ssid_width_left, "SSID");
    Serial.println(F("-------------------------------------------------------------"));
  } else {
    // Einspaltiger Modus
    // NEU 2.27.1 REQ-3: Age-Spalte zwischen dB und MAC-Adresse ergaenzt
    Serial.printf_P(PSTR(" # [%-*.*s] %6s %2s  %s Age MAC-Adresse\r\n"),
                  ssid_width_left, ssid_width_left, "SSID", "Ger", "ch", "dB");
    Serial.println(F("-------------------------------------------------------------"));
  }
  ssid_select_cursor_count = live_n;
  int half = two_col ? (live_n + 1) / 2 : live_n;
  for (int i = 0; i < half; i++) {
    print_ap_cell(sorted_idx[i], ssid_width_left, two_col, now, show_vendors_in_menu3);
    if (two_col) {
      int right_i = half + i;
      if (right_i < live_n) {
        Serial.print(F(" "));
        print_ap_cell(sorted_idx[right_i], ssid_width_right, two_col,
                      now, false);
      }
    }
    Serial.println();
    yield();
  }
  if (live_n == 0) {
    Serial.println(F(" (noch keine SSIDs aufgezeichnet)"));
  }
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Backspace/ESC = zurueck"));
  Serial.print(F(" Auswahl: "));
  if (offline_banner_will_print()) Serial.println();  // BUGFIX 2.30.44: siehe Kommentar bei offline_banner_will_print()
  // NEU 2.27.4: Zeitstempel fuer Auto-Refresh setzen (analog Menue 3a/4)
  last_ssid_select_refresh_time = millis() / 1000;
}

// NEU 2.29.17: startet die Beacon-Frame-Erfassung fuer den gewaehlten AP
// (Punkt 3, "w"+Zahl+Enter). Legt den 112-Byte-Zwischenpuffer erst hier an
// (kein dauerhaft reservierter RAM) und "bewaffnet" die Erfassung - der
// eigentliche Fang passiert asynchron im Promiscuous-Callback, sobald der
// naechste Beacon dieser BSSID eintrifft (siehe promisc_cb()). menu_periodic()
// prueft laufend auf Erfolg oder Timeout (siehe dort).
void menu_start_beacon_capture(int idx)
{
  if (!online_mode) {
    Serial.println(F(" Nicht moeglich: Aufzeichnung ist pausiert (Offline-Modus) -"));
    Serial.println(F(" es koennen aktuell keine neuen Beacons erfasst werden."));
    Serial.print(F(" Auswahl: "));
    return;
  }
  if (idx < 0 || idx >= aps_known_count || ap_slot_free(idx)) {
    Serial.println(F(" Ungueltige Auswahl."));
    Serial.print(F(" Auswahl: "));
    return;
  }
  if (beacon_capture_buf != NULL) free(beacon_capture_buf);  // Sicherheitsnetz
  beacon_capture_buf = (uint8_t*) malloc(112);
  if (beacon_capture_buf == NULL) {
    Serial.println(F(" Fehler: kein Speicher fuer die Erfassung verfuegbar."));
    Serial.print(F(" Auswahl: "));
    return;
  }
  memcpy(beacon_capture_target_bssid, aps_known[idx].bssid, ETH_MAC_LEN);
  beacon_capture_ap_idx = idx;
  beacon_capture_reallen = 0;
  beacon_capture_rssi = 0;
  beacon_capture_done = false;
  beacon_capture_start_ms = millis();
  beacon_capture_armed = true;

  menu_state = STATE_BEACON_ANALYSIS;
  ram_debug_sample(RDP_BEACON_ANALYSIS);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
  CallChainGuard __cc_guard(RDP_BEACON_ANALYSIS);  // NEU 2.30.35: Call-Chain-Erweiterung
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Beacon-Frame-Analyse"));
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" AP #%d [%s]\r\n"), idx, aps_known[idx].ssid);
  Serial.print(F(" BSSID "));
  print_mac(aps_known[idx].bssid, NULL);
  Serial.println();
  Serial.println();
  Serial.println(F(" Warte auf den naechsten Beacon dieses APs..."));
  Serial.printf_P(PSTR(" (Timeout nach %lu Sekunden)\r\n"), BEACON_ANALYSIS_TIMEOUT_MS / 1000UL);
  Serial.println();
  Serial.println(F(" Backspace/ESC = abbrechen"));
}

// NEU 2.29.17: bricht eine laufende/abgeschlossene Erfassung ab und gibt den
// Zwischenpuffer wieder frei - aufgerufen von Backspace/ESC waehrend
// STATE_BEACON_ANALYSIS (egal ob noch am Warten oder Ergebnis schon steht).
void cancel_beacon_capture()
{
  beacon_capture_armed = false;
  beacon_capture_done = false;
  if (beacon_capture_buf != NULL) {
    free(beacon_capture_buf);
    beacon_capture_buf = NULL;
  }
}

// NEU 2.29.17: Klartextnamen bekannter Information-Element-IDs (IEEE 802.11).
// Unbekannte IDs werden trotzdem mit ihren Rohbytes angezeigt (siehe
// display_beacon_frame_analysis()) - hier fehlt nur der Klartextname.
const char* ie_element_name(uint8_t id)
{
  static char buf[32];  // NEU 2.29.18 RAM-FIX: statisch, wiederverwendet - Text liegt per PROGMEM im Flash
  switch (id) {
    case 0:   strcpy_P(buf, PSTR("SSID")); break;
    case 1:   strcpy_P(buf, PSTR("Supported Rates")); break;
    case 3:   strcpy_P(buf, PSTR("DSSS Parameter Set/Kanal")); break;
    case 5:   strcpy_P(buf, PSTR("TIM")); break;
    case 7:   strcpy_P(buf, PSTR("Country")); break;
    case 11:  strcpy_P(buf, PSTR("QBSS Load")); break;
    case 32:  strcpy_P(buf, PSTR("Power Constraint")); break;
    case 33:  strcpy_P(buf, PSTR("Power Capability")); break;
    case 36:  strcpy_P(buf, PSTR("Supported Channels")); break;
    case 42:  strcpy_P(buf, PSTR("ERP Information")); break;
    case 45:  strcpy_P(buf, PSTR("HT Capabilities")); break;
    case 48:  strcpy_P(buf, PSTR("RSN (WPA2/WPA3)")); break;
    case 50:  strcpy_P(buf, PSTR("Extended Supported Rates")); break;
    case 61:  strcpy_P(buf, PSTR("HT Operation")); break;
    case 127: strcpy_P(buf, PSTR("Extended Capabilities")); break;
    case 191: strcpy_P(buf, PSTR("VHT Capabilities")); break;
    case 192: strcpy_P(buf, PSTR("VHT Operation")); break;
    case 221: strcpy_P(buf, PSTR("Vendor Specific")); break;
    case 255: strcpy_P(buf, PSTR("Element-ID-Erweiterung")); break;
    default:  strcpy_P(buf, PSTR("unbekannt")); break;
  }
  return buf;
}

// NEU 2.29.17: Cipher-Suite-Typen aus RSN/WPA2-IEs (OUI 00-0F-AC, IEEE 802.11).
const char* rsn_cipher_suite_name(uint8_t type)
{
  static char buf[24];  // NEU 2.29.18 RAM-FIX
  switch (type) {
    case 0:  strcpy_P(buf, PSTR("Gruppe verwenden")); break;
    case 1:  strcpy_P(buf, PSTR("WEP-40")); break;
    case 2:  strcpy_P(buf, PSTR("TKIP")); break;
    case 4:  strcpy_P(buf, PSTR("CCMP (AES)")); break;
    case 5:  strcpy_P(buf, PSTR("WEP-104")); break;
    case 6:  strcpy_P(buf, PSTR("BIP (Management)")); break;
    case 8:  strcpy_P(buf, PSTR("GCMP-128")); break;
    case 9:  strcpy_P(buf, PSTR("GCMP-256")); break;
    case 10: strcpy_P(buf, PSTR("CCMP-256")); break;
    default: strcpy_P(buf, PSTR("unbekannt")); break;
  }
  return buf;
}

// NEU 2.29.17: AKM-Suite-Typen (Authentifizierung/Schluesselaushandlung) aus
// RSN/WPA2-IEs (OUI 00-0F-AC, IEEE 802.11).
const char* rsn_akm_suite_name(uint8_t type)
{
  static char buf[24];  // NEU 2.29.18 RAM-FIX
  switch (type) {
    case 1:  strcpy_P(buf, PSTR("802.1X (Enterprise)")); break;
    case 2:  strcpy_P(buf, PSTR("PSK")); break;
    case 3:  strcpy_P(buf, PSTR("FT-802.1X")); break;
    case 4:  strcpy_P(buf, PSTR("FT-PSK")); break;
    case 5:  strcpy_P(buf, PSTR("802.1X-SHA256")); break;
    case 6:  strcpy_P(buf, PSTR("PSK-SHA256")); break;
    case 8:  strcpy_P(buf, PSTR("SAE (WPA3-Personal)")); break;
    case 9:  strcpy_P(buf, PSTR("FT-SAE")); break;
    case 11: strcpy_P(buf, PSTR("802.1X-Suite-B-192")); break;
    case 12: strcpy_P(buf, PSTR("FT-802.1X-SHA384")); break;
    case 18: strcpy_P(buf, PSTR("OWE")); break;
    default: strcpy_P(buf, PSTR("unbekannt")); break;
  }
  return buf;
}

// NEU 2.29.17: zerlegt ein RSN/WPA2(/WPA3)-Information-Element (ID 48) in
// seine Bestandteile. d/len zeigen auf die IE-Nutzdaten (ohne ID/Laengen-
// Byte). Absichtlich robust gegen abgeschnittene Daten (SDK-Puffergrenze) -
// bricht einfach an der Stelle ab, an der nicht mehr genug Bytes fuer das
// naechste Feld vorhanden sind.
void decode_rsn_ie(uint8_t *d, int len)
{
  if (len < 2) { Serial.print(F("(zu kurz)")); return; }
  int p = 0;
  uint16_t version = d[p] | (d[p + 1] << 8); p += 2;
  Serial.printf_P(PSTR("Version %u"), version);
  if (p + 4 <= len) {
    Serial.printf_P(PSTR(", Gruppenverschluesselung %s"), rsn_cipher_suite_name(d[p + 3]));
    p += 4;
  }
  if (p + 2 <= len) {
    uint16_t pairwise_count = d[p] | (d[p + 1] << 8); p += 2;
    Serial.print(F(", Paarweise ["));
    for (int i = 0; i < pairwise_count && p + 4 <= len; i++) {
      Serial.printf_P(PSTR("%s%s"), i > 0 ? ", " : "", rsn_cipher_suite_name(d[p + 3]));
      p += 4;
    }
    Serial.print(']');
  }
  if (p + 2 <= len) {
    uint16_t akm_count = d[p] | (d[p + 1] << 8); p += 2;
    Serial.print(F(", Authentifizierung ["));
    for (int i = 0; i < akm_count && p + 4 <= len; i++) {
      Serial.printf_P(PSTR("%s%s"), i > 0 ? ", " : "", rsn_akm_suite_name(d[p + 3]));
      p += 4;
    }
    Serial.print(']');
  }
  if (p + 2 <= len) {
    uint16_t rsn_capa = d[p] | (d[p + 1] << 8); p += 2;
    Serial.printf_P(PSTR(", RSN-Capabilities 0x%04X"), rsn_capa);
  }
}

// NEU 2.29.17: zerlegt den in beacon_capture_buf erfassten Rohframe Bit-/
// Byte-genau und gibt eine vollstaendige Tabelle aus. Wiederverwendbar
// aufgebaut (arbeitet ausschliesslich auf den globalen beacon_capture_*-
// Variablen, kein AP-Array-Zugriff noetig) - kann spaeter auch aus Menue 3a
// heraus aufgerufen werden, ohne Anpassung.
void display_beacon_frame_analysis()
{
  uint8_t *f = beacon_capture_buf;
  uint16_t real_len = beacon_capture_reallen;
  // Wie viele der 112 gepufferten Byte sind laut SDK tatsaechlich Teil des
  // empfangenen Frames? (RxControl.legacy_length kann kleiner ODER groesser
  // als 112 sein - alles darueber hinaus ist SDK-seitig nicht erfassbar.)
  uint16_t usable_len = (real_len > 0 && real_len < 112) ? real_len : 112;

  Serial.println(F("======================================================="));
  Serial.println(F(" Beacon-Frame-Analyse - Ergebnis"));
  Serial.println(F("======================================================="));
  if (real_len > 112) {
    Serial.printf_P(PSTR(" Frame ist laut Funkmodul %u Byte lang, der SDK-Puffer liefert\r\n"), real_len);
    Serial.println(F(" davon nur die ersten 112 Byte (Hardware-/SDK-Grenze) - alles"));
    Serial.println(F(" darueber hinaus ist auf diesem Weg nicht erfassbar."));
  } else {
    Serial.printf_P(PSTR(" Frame ist %u Byte lang, vollstaendig erfasst.\r\n"), usable_len);
  }
  Serial.printf_P(PSTR(" Signalstaerke bei Empfang: %d dBm\r\n"), beacon_capture_rssi);
  Serial.println();

  // ---------- MAC-Header ----------
  Serial.println(F("--- MAC-Header (IEEE 802.11) ---"));
  uint16_t fc = f[0] | (f[1] << 8);
  uint8_t proto_ver = f[0] & 0x03;
  uint8_t ftype = (f[0] >> 2) & 0x03;
  uint8_t fsubtype = (f[0] >> 4) & 0x0F;
  Serial.printf_P(PSTR(" Byte  0- 1  Frame Control       : 0x%04X\r\n"), fc);
  Serial.printf_P(PSTR("   Protokoll-Version : %d\r\n"), proto_ver);
  {
    static char type_buf[12];
    strcpy_P(type_buf, ftype == 0 ? PSTR("Management") : ftype == 1 ? PSTR("Control") : ftype == 2 ? PSTR("Data") : PSTR("Reserviert"));
    Serial.printf_P(PSTR("   Typ               : %d (%s)\r\n"), ftype, type_buf);
  }
  {
    static char subtype_buf[16];
    strcpy_P(subtype_buf, fsubtype == 8 ? PSTR("Beacon") : fsubtype == 5 ? PSTR("Probe Response") : PSTR("?"));
    Serial.printf_P(PSTR("   Subtyp            : %d (%s)\r\n"), fsubtype, subtype_buf);
  }
  Serial.printf_P(PSTR("   Flags             : ToDS=%d FromDS=%d MoreFrag=%d Retry=%d PwrMgt=%d MoreData=%d Protected=%d Order=%d\r\n"),
                (f[1] >> 0) & 1, (f[1] >> 1) & 1, (f[1] >> 2) & 1, (f[1] >> 3) & 1,
                (f[1] >> 4) & 1, (f[1] >> 5) & 1, (f[1] >> 6) & 1, (f[1] >> 7) & 1);

  uint16_t duration = f[2] | (f[3] << 8);
  Serial.printf_P(PSTR(" Byte  2- 3  Duration/ID         : %u\r\n"), duration);

  Serial.print(F(" Byte  4- 9  Adresse 1 (DA)      : ")); print_mac(f + 4, NULL); Serial.println();
  Serial.print(F(" Byte 10-15  Adresse 2 (SA/BSSID): ")); print_mac(f + 10, NULL);
  {
    String vendor = vendorCache_lookup_or_search(f + 10);
    Serial.printf_P(PSTR("  Hersteller: %s\r\n"), vendor.c_str());
  }
  Serial.print(F(" Byte 16-21  Adresse 3 (BSSID)   : ")); print_mac(f + 16, NULL); Serial.println();

  uint16_t seqctl = f[22] | (f[23] << 8);
  Serial.printf_P(PSTR(" Byte 22-23  Sequence Control    : Fragment=%u Sequenznummer=%u\r\n"), seqctl & 0x0F, seqctl >> 4);
  Serial.println();

  // ---------- Feste Beacon-Felder ----------
  Serial.println(F("--- Feste Beacon-Felder ---"));
  uint32_t ts_low = 0, ts_high = 0;
  for (int i = 3; i >= 0; i--) ts_low = (ts_low << 8) | f[24 + i];
  for (int i = 3; i >= 0; i--) ts_high = (ts_high << 8) | f[28 + i];
  // NEU 2.30.32: Darstellung als vollstaendiger 64-Bit-TSF-Wert (unsigned) statt
  // High/Low-Zerlegung. Die Byte-24-31-Auswertung/Little-Endian-Zusammensetzung
  // oben bleibt unveraendert - es aendert sich ausschliesslich die Ausgabe.
  {
    uint64_t tsf = ((uint64_t) ts_high << 32) | (uint64_t) ts_low;
    char tsf_buf[21], days_buf[21];
    format_uint64_dec(tsf, tsf_buf, sizeof(tsf_buf));

    uint64_t total_seconds = tsf / 1000000ULL;
    uint32_t rem_us = (uint32_t)(tsf % 1000000ULL);
    uint32_t ms = rem_us / 1000UL;
    uint64_t days = total_seconds / 86400ULL;
    uint32_t rem_sec = (uint32_t)(total_seconds % 86400ULL);
    uint32_t hh = rem_sec / 3600UL;
    uint32_t mm = (rem_sec % 3600UL) / 60UL;
    uint32_t ss = rem_sec % 60UL;
    format_uint64_dec(days, days_buf, sizeof(days_buf));

    Serial.printf_P(PSTR(" Byte 24-31  Timestamp/TSF       : %s \xc2\xb5s\r\n"), tsf_buf);
    Serial.printf_P(PSTR("                                   ca. %s Tage %02lu:%02lu:%02lu.%03lu\r\n"),
                  days_buf, (unsigned long) hh, (unsigned long) mm, (unsigned long) ss, (unsigned long) ms);
  }

  uint16_t beacon_interval = f[32] | (f[33] << 8);
  uint32_t interval_us = (uint32_t) beacon_interval * 1024UL;  // 1 TU = 1024 Mikrosekunden, exakt
  Serial.printf_P(PSTR(" Byte 32-33  Beacon-Intervall    : %u TU (= %lu.%03lu ms)\r\n"),
                beacon_interval, (unsigned long)(interval_us / 1000), (unsigned long)(interval_us % 1000));

  uint16_t capa = f[34] | (f[35] << 8);
  Serial.printf_P(PSTR(" Byte 34-35  Capability Info     : 0x%04X\r\n"), capa);
  Serial.printf_P(PSTR("   ESS=%d IBSS=%d CFPollable=%d CFPollReq=%d Privacy=%d ShortPreamble=%d\r\n"),
                (capa >> 0) & 1, (capa >> 1) & 1, (capa >> 2) & 1, (capa >> 3) & 1, (capa >> 4) & 1, (capa >> 5) & 1);
  Serial.printf_P(PSTR("   ChannelAgility=%d SpectrumMgmt=%d QoS=%d ShortSlotTime=%d APSD=%d\r\n"),
                (capa >> 7) & 1, (capa >> 8) & 1, (capa >> 9) & 1, (capa >> 10) & 1, (capa >> 11) & 1);
  Serial.printf_P(PSTR("   RadioMeasurement=%d DSSS-OFDM=%d DelayedBlockAck=%d ImmediateBlockAck=%d\r\n"),
                (capa >> 12) & 1, (capa >> 13) & 1, (capa >> 14) & 1, (capa >> 15) & 1);
  Serial.println();

  // ---------- Information Elements ----------
  Serial.println(F("--- Information Elements ---"));
  int pos = 36;
  int ie_count = 0;
  while (pos + 2 <= usable_len) {
    uint8_t id = f[pos];
    uint8_t ie_len = f[pos + 1];
    int data_start = pos + 2;
    int available = usable_len - data_start;
    int shown_len = (ie_len <= available) ? ie_len : available;
    bool truncated_by_sdk = (ie_len > available);

    Serial.printf_P(PSTR(" ID %3d (%-28s) Laenge %3d: "), id, ie_element_name(id), ie_len);

    switch (id) {
      case 0: {  // SSID
        char ssidbuf[33];
        int n = shown_len > 32 ? 32 : shown_len;
        memcpy(ssidbuf, f + data_start, n);
        ssidbuf[n] = '\0';
        if (n == 0) Serial.print(F("(leer/versteckt)"));
        else Serial.printf_P(PSTR("\"%s\""), ssidbuf);
        break;
      }
      case 1: case 50: {  // Supported Rates / Extended Supported Rates
        for (int i = 0; i < shown_len; i++) {
          uint8_t v = f[data_start + i];
          bool basic = (v & 0x80) != 0;
          int whole = (v & 0x7F) / 2;
          int frac = ((v & 0x7F) % 2) * 5;
          Serial.printf_P(PSTR("%s%d.%d%s"), i > 0 ? ", " : "", whole, frac, basic ? "*" : "");
        }
        if (shown_len > 0) Serial.print(F(" Mbps (* = Basisrate)"));
        break;
      }
      case 3:  // DSSS Parameter Set
        if (shown_len >= 1) Serial.printf_P(PSTR("Kanal %d"), f[data_start]);
        break;
      case 48:  // RSN
        decode_rsn_ie(f + data_start, shown_len);
        break;
      case 221:  // Vendor Specific
        if (shown_len >= 4) {
          uint8_t oui_as_mac[6] = { f[data_start], f[data_start + 1], f[data_start + 2], 0, 0, 0 };
          String vendor = vendorCache_lookup_or_search(oui_as_mac);
          Serial.printf_P(PSTR("OUI %02x:%02x:%02x (%s), Typ %d"),
                        f[data_start], f[data_start + 1], f[data_start + 2],
                        vendor.c_str(), f[data_start + 3]);
        }
        break;
      default:
        // Kein spezifischer Decoder - die Rohbytes unten reichen, damit
        // nichts an Information verloren geht.
        break;
    }
    Serial.println();

    // Rohbytes IMMER zusaetzlich zeigen, unabhaengig davon, ob oben schon
    // eine Interpretation stand - nichts wird verschwiegen.
    if (shown_len > 0) {
      Serial.print(F("     Rohdaten: "));
      for (int i = 0; i < shown_len; i++) {
        Serial.printf_P(PSTR("%02x "), f[data_start + i]);
        if ((i + 1) % 16 == 0 && i + 1 < shown_len) Serial.print(F("\r\n               "));
        if ((i & 0x0F) == 0) yield();
      }
      Serial.println();
    }
    if (truncated_by_sdk) {
      Serial.println(F("     (laut Laengenangabe im Frame laenger als der erfasste Bereich - SDK-Puffergrenze erreicht)"));
    }

    pos = data_start + ie_len;  // naechstes IE anhand der ANGEGEBENEN Laenge
    ie_count++;
    yield();
  }
  if (ie_count == 0) {
    Serial.println(F(" (keine Information Elements im erfassten Bereich)"));
  }
  Serial.println(F("-------------------------------------------------------"));
}

// NEU 2.30.6: startet die Probe-Request-Erfassung fuer den gewaehlten Client
// (Menue 3a, "w"+Zahl+Enter). Pendant zu menu_start_beacon_capture() oben -
// gleiches Prinzip (malloc() erst hier, Erfassung asynchron im Callback),
// aber Match auf die Station-MAC des Clients statt der BSSID eines APs.
void menu_start_client_capture(int idx)
{
  if (!online_mode) {
    Serial.println(F(" Nicht moeglich: Aufzeichnung ist pausiert (Offline-Modus) -"));
    Serial.println(F(" es koennen aktuell keine neuen Frames erfasst werden."));
    Serial.print(F(" Auswahl: "));
    return;
  }
  if (idx < 0 || idx >= clients_known_count) {
    Serial.println(F(" Ungueltige Auswahl."));
    Serial.print(F(" Auswahl: "));
    return;
  }
  if (client_capture_buf != NULL) free(client_capture_buf);  // Sicherheitsnetz
  client_capture_buf = (uint8_t*) malloc(112);
  if (client_capture_buf == NULL) {
    Serial.println(F(" Fehler: kein Speicher fuer die Erfassung verfuegbar."));
    Serial.print(F(" Auswahl: "));
    return;
  }
  memcpy(client_capture_target_station, clients_known[idx].station, ETH_MAC_LEN);
  client_capture_client_idx = idx;
  client_capture_reallen = 0;
  client_capture_buf_capacity = 0;
  client_capture_rssi = 0;
  client_capture_done = false;
  client_capture_start_ms = millis();
  client_capture_armed = true;

  menu_state = STATE_CLIENT_ANALYSIS;
  ram_debug_sample(RDP_CLIENT_ANALYSIS);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
  CallChainGuard __cc_guard(RDP_CLIENT_ANALYSIS);  // NEU 2.30.35: Call-Chain-Erweiterung
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Client-Frame-Analyse"));
  Serial.println(F("======================================================="));
  Serial.print(F(" Client "));
  print_mac(clients_known[idx].station, NULL);
  Serial.println();
  Serial.println();
  // NEU 2.30.8: wartet auf das naechste Paket JEDER Art (Datenframe oder
  // Management-Frame) - siehe Kommentar bei den client_capture_*-Variablen.
  Serial.println(F(" Warte auf das naechste Paket dieses Clients..."));
  Serial.printf_P(PSTR(" (Timeout nach %lu Sekunden)\r\n"), BEACON_ANALYSIS_TIMEOUT_MS / 1000UL);
  Serial.println(F(" Hinweis: bei einem Datenframe (der Regelfall bei einem bereits"));
  Serial.println(F(" verbundenen, aktiven Client) sind nur MAC-Header und die ersten"));
  Serial.println(F(" Nutzdaten-Byte auswertbar - der eigentliche Inhalt ist ueblicher-"));
  Serial.println(F(" weise WPA2/3-verschluesselt und nicht im Klartext lesbar."));
  Serial.println();
  Serial.println(F(" Backspace/ESC = abbrechen"));
}

// NEU 2.30.6: bricht eine laufende/abgeschlossene Client-Erfassung ab und
// gibt den Zwischenpuffer wieder frei - Pendant zu cancel_beacon_capture().
void cancel_client_capture()
{
  client_capture_armed = false;
  client_capture_done = false;
  if (client_capture_buf != NULL) {
    free(client_capture_buf);
    client_capture_buf = NULL;
  }
}

// NEU 2.30.6: zerlegt den in client_capture_buf erfassten Probe-Request-
// Rohframe Bit-/Byte-genau, analog zu display_beacon_frame_analysis().
// Unterschied zum Beacon-Pendant: KEINE festen Beacon-Felder (Timestamp/
// Beacon-Intervall/Capability Info) - ein Probe Request hat diese Felder
// nicht, die Information Elements beginnen direkt ab Byte 24 statt 36.
// Die IE-Dekodierung selbst (SSID/Rates/RSN/Vendor-Specific) nutzt
// dieselben Hilfsfunktionen wie beim Beacon (ie_element_name(),
// decode_rsn_ie(), vendorCache_lookup_or_search()), da sie frametyp-
// unabhaengig arbeiten.
void display_client_frame_analysis()
{
  uint8_t *f = client_capture_buf;
  uint16_t real_len = client_capture_reallen;
  uint16_t capacity = client_capture_buf_capacity;  // 112 (Management) oder 36 (Datenframe)
  // Wie viele der gepufferten Byte sind laut SDK tatsaechlich Teil des
  // empfangenen Frames? (Gleiche SDK-Puffergrenze wie beim Beacon-Pendant,
  // nur je nach Frametyp mit anderer Kapazitaet.)
  uint16_t usable_len = (real_len > 0 && real_len < capacity) ? real_len : capacity;

  uint16_t fc = f[0] | (f[1] << 8);
  uint8_t proto_ver = f[0] & 0x03;
  uint8_t ftype = (f[0] >> 2) & 0x03;
  uint8_t fsubtype = (f[0] >> 4) & 0x0F;
  bool is_probe_request = (ftype == 0 && fsubtype == 4);

  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" Client-Frame-Analyse - Ergebnis (%s)\r\n"), is_probe_request ? "Probe Request" : (ftype == 2 ? "Datenframe" : "Management-Frame"));
  Serial.println(F("======================================================="));
  if (real_len > capacity) {
    Serial.printf_P(PSTR(" Frame ist laut Funkmodul %u Byte lang, der SDK-Puffer liefert\r\n"), real_len);
    Serial.printf_P(PSTR(" davon nur die ersten %u Byte (Hardware-/SDK-Grenze) - alles\r\n"), capacity);
    Serial.println(F(" darueber hinaus ist auf diesem Weg nicht erfassbar."));
  } else {
    Serial.printf_P(PSTR(" Frame ist %u Byte lang, vollstaendig erfasst.\r\n"), usable_len);
  }
  Serial.printf_P(PSTR(" Signalstaerke bei Empfang: %d dBm\r\n"), client_capture_rssi);
  Serial.println();

  // ---------- MAC-Header ----------
  Serial.println(F("--- MAC-Header (IEEE 802.11) ---"));
  Serial.printf_P(PSTR(" Byte  0- 1  Frame Control       : 0x%04X\r\n"), fc);
  Serial.printf_P(PSTR("   Protokoll-Version : %d\r\n"), proto_ver);
  {
    static char type_buf[12];
    strcpy_P(type_buf, ftype == 0 ? PSTR("Management") : ftype == 1 ? PSTR("Control") : ftype == 2 ? PSTR("Data") : PSTR("Reserviert"));
    Serial.printf_P(PSTR("   Typ               : %d (%s)\r\n"), ftype, type_buf);
  }
  Serial.printf_P(PSTR("   Subtyp            : %d (%s)\r\n"), fsubtype, ie_frame_subtype_name(ftype, fsubtype));
  uint8_t to_ds = f[1] & 1;
  uint8_t from_ds = (f[1] >> 1) & 1;
  Serial.printf_P(PSTR("   Flags             : ToDS=%d FromDS=%d MoreFrag=%d Retry=%d PwrMgt=%d MoreData=%d Protected=%d Order=%d\r\n"),
                to_ds, from_ds, (f[1] >> 2) & 1, (f[1] >> 3) & 1,
                (f[1] >> 4) & 1, (f[1] >> 5) & 1, (f[1] >> 6) & 1, (f[1] >> 7) & 1);

  uint16_t duration = f[2] | (f[3] << 8);
  Serial.printf_P(PSTR(" Byte  2- 3  Duration/ID         : %u\r\n"), duration);

  // NEU 2.30.8: Adressfelder werden jetzt je nach ToDS/FromDS beschriftet
  // (wie bei der normalen Client-Erkennung in parse_data()), statt immer
  // pauschal "DA"/"SA"/"BSSID" - bei einem Datenframe stimmt das sonst nicht
  // in jeder Richtung. Ein 4-Adress-Frame (ToDS=1+FromDS=1, WDS) wird nur
  // benannt, nicht vollstaendig zerlegt - in der Praxis bei Endgeraeten nicht
  // zu erwarten.
  const char *a1_label, *a2_label, *a3_label;
  if (to_ds == 0 && from_ds == 0) {
    a1_label = "Empfaenger (DA)";
    a2_label = "Sender/Client (SA)";
    a3_label = "BSSID";
  } else if (to_ds == 1 && from_ds == 0) {
    a1_label = "BSSID/AP";
    a2_label = "Sender/Client (SA)";
    a3_label = "Empfaenger (DA)";
  } else if (to_ds == 0 && from_ds == 1) {
    a1_label = "Empfaenger/Client (DA)";
    a2_label = "BSSID/AP (SA)";
    a3_label = "Urspruengl. Sender";
  } else {
    a1_label = "Empfaenger (WDS)";
    a2_label = "Sender (WDS)";
    a3_label = "Adresse 3 (WDS)";
  }
  Serial.printf_P(PSTR(" Byte  4- 9  Adresse 1 - %-22s: "), a1_label); print_mac(f + 4, NULL); Serial.println();
  Serial.printf_P(PSTR(" Byte 10-15  Adresse 2 - %-22s: "), a2_label); print_mac(f + 10, NULL);
  {
    String vendor = vendorCache_lookup_or_search(f + 10);
    Serial.printf_P(PSTR("  Hersteller: %s\r\n"), vendor.c_str());
  }
  Serial.printf_P(PSTR(" Byte 16-21  Adresse 3 - %-22s: "), a3_label); print_mac(f + 16, NULL); Serial.println();
  if (to_ds == 1 && from_ds == 1) {
    Serial.println(F(" Hinweis: 4-Adress-Frame (WDS) - Adresse 4 wird hier nicht ausgewertet,"));
    Serial.println(F(" die nachfolgenden Byte-Angaben verschieben sich dadurch um 6 Byte."));
  }

  uint16_t seqctl = f[22] | (f[23] << 8);
  Serial.printf_P(PSTR(" Byte 22-23  Sequence Control    : Fragment=%u Sequenznummer=%u\r\n"), seqctl & 0x0F, seqctl >> 4);

  int pos = 24;
  if (ftype == 2 && (fsubtype & 0x08)) {  // QoS-Data-Varianten (Subtyp 8/9/../15)
    if (usable_len >= 26) {
      uint16_t qos = f[24] | (f[25] << 8);
      Serial.printf_P(PSTR(" Byte 24-25  QoS Control         : 0x%04X (TID=%d)\r\n"), qos, qos & 0x0F);
    }
    pos = 26;
  }
  Serial.println();

  if (is_probe_request) {
    // ---------- Information Elements (nur Probe Request) ----------
    // Kein Block "Feste Beacon-Felder" - Probe Requests haben diese Felder
    // nicht, die IEs beginnen direkt im Anschluss an den MAC-Header.
    Serial.println(F("--- Information Elements ---"));
    int ie_count = 0;
    while (pos + 2 <= usable_len) {
      uint8_t id = f[pos];
      uint8_t ie_len = f[pos + 1];
      int data_start = pos + 2;
      int available = usable_len - data_start;
      int shown_len = (ie_len <= available) ? ie_len : available;
      bool truncated_by_sdk = (ie_len > available);

      Serial.printf_P(PSTR(" ID %3d (%-28s) Laenge %3d: "), id, ie_element_name(id), ie_len);

      switch (id) {
        case 0: {  // SSID (bei Probe Request: die GESUCHTE SSID, leer = Broadcast-Probe)
          char ssidbuf[33];
          int n = shown_len > 32 ? 32 : shown_len;
          memcpy(ssidbuf, f + data_start, n);
          ssidbuf[n] = '\0';
          if (n == 0) Serial.print(F("(leer/Broadcast-Probe)"));
          else Serial.printf_P(PSTR("\"%s\""), ssidbuf);
          break;
        }
        case 1: case 50: {  // Supported Rates / Extended Supported Rates
          for (int i = 0; i < shown_len; i++) {
            uint8_t v = f[data_start + i];
            bool basic = (v & 0x80) != 0;
            int whole = (v & 0x7F) / 2;
            int frac = ((v & 0x7F) % 2) * 5;
            Serial.printf_P(PSTR("%s%d.%d%s"), i > 0 ? ", " : "", whole, frac, basic ? "*" : "");
          }
          if (shown_len > 0) Serial.print(F(" Mbps (* = Basisrate)"));
          break;
        }
        case 3:  // DSSS Parameter Set
          if (shown_len >= 1) Serial.printf_P(PSTR("Kanal %d"), f[data_start]);
          break;
        case 48:  // RSN (selten in Probe Requests, aber moeglich)
          decode_rsn_ie(f + data_start, shown_len);
          break;
        case 221:  // Vendor Specific
          if (shown_len >= 4) {
            uint8_t oui_as_mac[6] = { f[data_start], f[data_start + 1], f[data_start + 2], 0, 0, 0 };
            String vendor = vendorCache_lookup_or_search(oui_as_mac);
            Serial.printf_P(PSTR("OUI %02x:%02x:%02x (%s), Typ %d"),
                          f[data_start], f[data_start + 1], f[data_start + 2],
                          vendor.c_str(), f[data_start + 3]);
          }
          break;
        default:
          // Kein spezifischer Decoder - die Rohbytes unten reichen, damit
          // nichts an Information verloren geht.
          break;
      }
      Serial.println();

      // Rohbytes IMMER zusaetzlich zeigen, unabhaengig davon, ob oben schon
      // eine Interpretation stand - nichts wird verschwiegen.
      if (shown_len > 0) {
        Serial.print(F("     Rohdaten: "));
        for (int i = 0; i < shown_len; i++) {
          Serial.printf_P(PSTR("%02x "), f[data_start + i]);
          if ((i + 1) % 16 == 0 && i + 1 < shown_len) Serial.print(F("\r\n               "));
          if ((i & 0x0F) == 0) yield();
        }
        Serial.println();
      }
      if (truncated_by_sdk) {
        Serial.println(F("     (laut Laengenangabe im Frame laenger als der erfasste Bereich - SDK-Puffergrenze erreicht)"));
      }

      pos = data_start + ie_len;  // naechstes IE anhand der ANGEGEBENEN Laenge
      ie_count++;
      yield();
    }
    if (ie_count == 0) {
      Serial.println(F(" (keine Information Elements im erfassten Bereich)"));
    }
  } else {
    // ---------- Generischer Fall: Datenframe oder sonstiger Management-
    // Frame ohne Information Elements. NEU 2.30.8. ----------
    Serial.println(F("--- Nutzdaten (nach dem MAC-Header) ---"));
    if (ftype == 2) {
      Serial.println(F(" Hinweis: bei einem verschluesselten Netz (WPA2/3, Regelfall) sind"));
      Serial.println(F(" dies keine Klartextdaten, sondern CCMP/TKIP-Rohbytes - eine"));
      Serial.println(F(" inhaltliche Auswertung ist damit nicht moeglich."));
    } else {
      Serial.println(F(" Hinweis: fuer diesen Management-Frame-Subtyp ist hier keine eigene"));
      Serial.println(F(" Feldinterpretation hinterlegt - die Rohbytes unten zeigen dennoch"));
      Serial.println(F(" alles, was tatsaechlich erfasst wurde."));
    }
    int shown_len = usable_len - pos;
    if (shown_len > 0) {
      Serial.print(F(" Rohdaten: "));
      for (int i = 0; i < shown_len; i++) {
        Serial.printf_P(PSTR("%02x "), f[pos + i]);
        if ((i + 1) % 16 == 0 && i + 1 < shown_len) Serial.print(F("\r\n           "));
        if ((i & 0x0F) == 0) yield();
      }
      Serial.println();
    } else {
      Serial.println(F(" (keine weiteren Byte im erfassten Bereich)"));
    }
  }
  Serial.println(F("-------------------------------------------------------"));
}

// NEU 2.30.8: Klartextname fuer Frame-Typ/Subtyp-Kombinationen, fuer die
// generische Anzeige in display_client_frame_analysis() (dort koennen -
// anders als bei der Beacon-/Probe-Request-Analyse - praktisch beliebige
// Subtypen auftreten, nicht nur Beacon/Probe).
// PROGMEM-Tabellen fuer ie_frame_subtype_name() (Umbauauftrag Block 2.1,
// ersetzt die vorherigen drei switch-Bloecke). Texte 1:1 aus der bisherigen
// Switch-Anweisung uebernommen. Fuer Control 0..3 (bisher "default") steht
// der gleiche Text "Control Reserved" direkt in der Tabelle.
static const char fsn_mgmt_0[] PROGMEM = "Association Request";
static const char fsn_mgmt_1[] PROGMEM = "Association Response";
static const char fsn_mgmt_2[] PROGMEM = "Reassociation Request";
static const char fsn_mgmt_3[] PROGMEM = "Reassociation Response";
static const char fsn_mgmt_4[] PROGMEM = "Probe Request";
static const char fsn_mgmt_5[] PROGMEM = "Probe Response";
static const char fsn_mgmt_6[] PROGMEM = "Timing Advertisement";
static const char fsn_mgmt_7[] PROGMEM = "Reserved";
static const char fsn_mgmt_8[] PROGMEM = "Beacon";
static const char fsn_mgmt_9[] PROGMEM = "ATIM";
static const char fsn_mgmt_10[] PROGMEM = "Disassociation";
static const char fsn_mgmt_11[] PROGMEM = "Authentication";
static const char fsn_mgmt_12[] PROGMEM = "Deauthentication";
static const char fsn_mgmt_13[] PROGMEM = "Action";
static const char fsn_mgmt_14[] PROGMEM = "Action No Ack";
static const char fsn_mgmt_15[] PROGMEM = "Reserved";
static const char* const FSN_MGMT[16] PROGMEM = {
  fsn_mgmt_0, fsn_mgmt_1, fsn_mgmt_2, fsn_mgmt_3, fsn_mgmt_4, fsn_mgmt_5,
  fsn_mgmt_6, fsn_mgmt_7, fsn_mgmt_8, fsn_mgmt_9, fsn_mgmt_10, fsn_mgmt_11,
  fsn_mgmt_12, fsn_mgmt_13, fsn_mgmt_14, fsn_mgmt_15
};

static const char fsn_ctrl_reserved[] PROGMEM = "Control Reserved";
static const char fsn_ctrl_4[] PROGMEM = "Beamforming Report Poll";
static const char fsn_ctrl_5[] PROGMEM = "VHT/HE NDP Announcement";
static const char fsn_ctrl_6[] PROGMEM = "Control Frame Extension";
static const char fsn_ctrl_7[] PROGMEM = "Control Wrapper";
static const char fsn_ctrl_8[] PROGMEM = "Block ACK Request";
static const char fsn_ctrl_9[] PROGMEM = "Block ACK";
static const char fsn_ctrl_10[] PROGMEM = "PS-Poll";
static const char fsn_ctrl_11[] PROGMEM = "RTS";
static const char fsn_ctrl_12[] PROGMEM = "CTS";
static const char fsn_ctrl_13[] PROGMEM = "ACK";
static const char fsn_ctrl_14[] PROGMEM = "CF-End (PCF)";
static const char fsn_ctrl_15[] PROGMEM = "CF-End+CF-Ack (PCF)";
static const char* const FSN_CTRL[16] PROGMEM = {
  fsn_ctrl_reserved, fsn_ctrl_reserved, fsn_ctrl_reserved, fsn_ctrl_reserved,
  fsn_ctrl_4, fsn_ctrl_5, fsn_ctrl_6, fsn_ctrl_7,
  fsn_ctrl_8, fsn_ctrl_9, fsn_ctrl_10, fsn_ctrl_11,
  fsn_ctrl_12, fsn_ctrl_13, fsn_ctrl_14, fsn_ctrl_15
};

static const char fsn_data_0[] PROGMEM = "Data";
static const char fsn_data_1[] PROGMEM = "Data+CF-Ack (PCF)";
static const char fsn_data_2[] PROGMEM = "Data+CF-Poll (PCF)";
static const char fsn_data_3[] PROGMEM = "Data+CF-Ack+CF-Poll (PCF)";
static const char fsn_data_4[] PROGMEM = "Null (kein Payload)";
static const char fsn_data_5[] PROGMEM = "CF-Ack ohne Daten (PCF)";
static const char fsn_data_6[] PROGMEM = "CF-Poll ohne Daten (PCF)";
static const char fsn_data_7[] PROGMEM = "CF-Ack+CF-Poll ohne Daten (PCF)";
static const char fsn_data_8[] PROGMEM = "QoS Data";
static const char fsn_data_9[] PROGMEM = "QoS Data+CF-Ack (PCF)";
static const char fsn_data_10[] PROGMEM = "QoS Data+CF-Poll (PCF)";
static const char fsn_data_11[] PROGMEM = "QoS Data+CF-Ack+CF-Poll (PCF)";
static const char fsn_data_12[] PROGMEM = "QoS Null (kein Payload)";
static const char fsn_data_13[] PROGMEM = "Data Reserved";
static const char fsn_data_14[] PROGMEM = "QoS CF-Poll ohne Daten (PCF)";
static const char fsn_data_15[] PROGMEM = "QoS CF-Ack+CF-Poll ohne Daten (PCF)";
static const char* const FSN_DATA[16] PROGMEM = {
  fsn_data_0, fsn_data_1, fsn_data_2, fsn_data_3,
  fsn_data_4, fsn_data_5, fsn_data_6, fsn_data_7,
  fsn_data_8, fsn_data_9, fsn_data_10, fsn_data_11,
  fsn_data_12, fsn_data_13, fsn_data_14, fsn_data_15
};

static const char fsn_unknown[] PROGMEM = "unbekannt";

const char* ie_frame_subtype_name(uint8_t ftype, uint8_t fsubtype)
{
  // RAM-FIX 2.30.29, seit Umbauauftrag Block 2.1 auf PROGMEM-Tabellen
  // umgestellt (statt drei switch-Bloecken): Texte liegen weiterhin nur im
  // Flash, zusaetzlich entfaellt der Switch-Code selbst (Flash-Ersparnis).
  // Ausgabetexte identisch zur vorherigen Fassung.
  static char buf[40];  // laengster Eintrag "Data+CF-Ack+CF-Poll ohne Daten (PCF)" = 37 Zeichen
  const char* const *table = NULL;
  if (ftype == 0) table = FSN_MGMT;
  else if (ftype == 1) table = FSN_CTRL;
  else if (ftype == 2) table = FSN_DATA;

  PGM_P src = fsn_unknown;
  if (table != NULL && fsubtype < 16) {
    PGM_P cand = (PGM_P)pgm_read_ptr(&table[fsubtype]);
    if (cand != NULL) src = cand;
  }
  strncpy_P(buf, src, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = '\0';
  return buf;
}

// Legt fest, was fuer ein Sortierfeld die Standardrichtung ist:
//   MAC:       aufsteigend
//   LastSeen:  aufsteigend (kleinste Anzahl Sekunden = zuletzt gesehen, zuerst)
//   RSSI:      absteigend (staerkster Pegel zuerst)
bool default_ascending_for(SortField f)
{
  if (f == SORT_RSSI) return false;
  return true;
}

void set_sort_field(SortField f)
{
  if (current_sort_field == f) {
    sort_ascending = !sort_ascending;
  } else {
    current_sort_field = f;
    sort_ascending = default_ascending_for(f);
  }
}

// Generischer Vergleich zweier Client-Eintraege nach aktuellem Sortiermodus.
// Liefert true, wenn Eintrag a VOR Eintrag b stehen soll.
bool client_before(int idx_a, int idx_b, uint64_t now)
{
  clientinfo &a = clients_known[idx_a];
  clientinfo &b = clients_known[idx_b];
  int cmp = 0;

  switch (current_sort_field) {
    case SORT_NONE:
      return false;  // wird nie aufgerufen (siehe sort_clients), nur zur Vollstaendigkeit
    case SORT_MAC:
      cmp = memcmp(a.station, b.station, ETH_MAC_LEN);
      break;
    case SORT_LASTSEEN: {
      long age_a = (long)(now - a.last_heard);
      long age_b = (long)(now - b.last_heard);
      cmp = (age_a < age_b) ? -1 : (age_a > age_b ? 1 : 0);
      break;
    }
    case SORT_RSSI:
      cmp = (a.rssi < b.rssi) ? -1 : (a.rssi > b.rssi ? 1 : 0);
      break;
  }
  if (!sort_ascending) cmp = -cmp;
  return cmp < 0;
}

// Insertion-Sort ueber ein Index-Array, Kriterium ueber client_before().
// NEU 2.30.14: bei SORT_NONE bleibt die Reihenfolge unveraendert
// (= "unsortiert", analog sort_aps()/AP_SORT_NONE).
void sort_clients(uint16_t *idx, int count, uint64_t now)
{
  if (current_sort_field == SORT_NONE) return;
  for (int i = 1; i < count; i++) {
    uint16_t key = idx[i];
    int j = i - 1;
    while (j >= 0 && client_before(key, idx[j], now)) {
      idx[j + 1] = idx[j];
      j--;
    }
    idx[j + 1] = key;
  }
}

static const char sfn_unsort[] PROGMEM = "unsort";
static const char sfn_mac[] PROGMEM = "MAC";
static const char sfn_age[] PROGMEM = "Age";
static const char sfn_rssi[] PROGMEM = "RSSI";
static const char sfn_unknown[] PROGMEM = "?";

const char* sort_field_name(SortField f)
{
  static char buf[8];
  PGM_P src = sfn_unknown;
  switch (f) {
    case SORT_NONE: src = sfn_unsort; break;
    case SORT_MAC: src = sfn_mac; break;
    case SORT_LASTSEEN: src = sfn_age; break;
    case SORT_RSSI: src = sfn_rssi; break;
  }
  strncpy_P(buf, src, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = '\0';
  return buf;
}

// NEU 2.17.4: Sortierung fuer die AP-Uebersichtsliste (Liste 3), analog zur
// Client-Sortierung oben (default_ascending_for/set_sort_field/client_before/
// sort_clients/sort_field_name).
bool default_ap_ascending_for(ApSortField f)
{
  if (f == AP_SORT_RSSI) return false;   // staerkster Pegel zuerst
  if (f == AP_SORT_COUNT) return false;  // meiste Geraete zuerst
  if (f == AP_SORT_AGE) return true;     // NEU 2.27.4: kleinstes Alter (frischest) zuerst
  return true;                           // SSID/MAC: alphabetisch/aufsteigend, NONE: unbenutzt
}

void set_ap_sort_field(ApSortField f)
{
  if (current_ap_sort_field == f) {
    ap_sort_ascending = !ap_sort_ascending;
  } else {
    current_ap_sort_field = f;
    ap_sort_ascending = default_ap_ascending_for(f);
  }
}

// Liefert true, wenn AP-Eintrag a VOR Eintrag b stehen soll.
bool ap_before(int idx_a, int idx_b, uint64_t now)
{
  beaconinfo &a = aps_known[idx_a];
  beaconinfo &b = aps_known[idx_b];
  int cmp = 0;

  switch (current_ap_sort_field) {
    case AP_SORT_NONE:
      return false;  // wird nie aufgerufen (siehe sort_aps), nur zur Vollstaendigkeit
    case AP_SORT_SSID:
      cmp = strcmp((const char*)a.ssid, (const char*)b.ssid);
      break;
    case AP_SORT_COUNT: {
      int count_a = 0, count_b = 0;
      for (int c = 0; c < clients_known_count; c++) {
        if (clients_known[c].ap_idx == idx_a) count_a++;
        if (clients_known[c].ap_idx == idx_b) count_b++;
      }
      cmp = (count_a < count_b) ? -1 : (count_a > count_b ? 1 : 0);
      break;
    }
    case AP_SORT_RSSI:
      cmp = (a.rssi < b.rssi) ? -1 : (a.rssi > b.rssi ? 1 : 0);
      break;
    case AP_SORT_AGE: {
      // BUGFIX 2.30.18 (Nutzer-Beobachtung): direkter Vergleich von
      // last_heard (ohne "now") ist NUR aequivalent zu einem Vergleich der
      // Altersunterschiede, solange millis() zwischendurch nicht ueberlaeuft
      // (alle ~49,7 Tage Laufzeit). Nach einem Ueberlauf haben Eintraege,
      // die VOR dem Ueberlauf zuletzt gehoert wurden, einen naheliegend
      // GROSSEN last_heard-Rohwert (nahe 0xFFFFFFFF), waehrend danach
      // gehoerte Eintraege einen KLEINEN Rohwert haben - der direkte
      // Vergleich sortierte die ALTEN (vor dem Ueberlauf gehoerten)
      // Eintraege dadurch faelschlich als "neuer" ganz nach vorn, obwohl
      // ihr tatsaechliches Alter (Age-Spalte, die schon immer korrekt
      // ueberlauf-sicher "now - last_heard" rechnet) laengst gross war.
      // Fix: wie beim laengst richtig gemachten Client-Pendant
      // (client_before(), SORT_LASTSEEN) jetzt ebenfalls ueber "now -
      // last_heard" vergleichen, mit dem gleichen ueberlaufsicheren
      // Cast-Trick (Differenz auf 32 Bit gekappt = korrekt modulo 2^32,
      // exakt wie format_age_field() es fuer die Anzeige schon tut).
      uint32_t age_a = (uint32_t)(now - a.last_heard);
      uint32_t age_b = (uint32_t)(now - b.last_heard);
      cmp = (age_a < age_b) ? -1 : (age_a > age_b ? 1 : 0);
      break;
    }
    case AP_SORT_MAC:
      // NEU 2.27.4
      cmp = memcmp(a.bssid, b.bssid, ETH_MAC_LEN);
      break;
  }
  if (!ap_sort_ascending) cmp = -cmp;
  return cmp < 0;
}

// Insertion-Sort ueber ein Index-Array der APs. Bei AP_SORT_NONE bleibt die
// Reihenfolge unveraendert (= "unsortiert", wie in Punkt 1).
void sort_aps(uint8_t *idx, int count, uint64_t now)
{
  if (current_ap_sort_field == AP_SORT_NONE) return;
  for (int i = 1; i < count; i++) {
    uint8_t key = idx[i];
    int j = i - 1;
    while (j >= 0 && ap_before(key, idx[j], now)) {
      idx[j + 1] = idx[j];
      j--;
    }
    idx[j + 1] = key;
  }
}

static const char apsfn_unsort[] PROGMEM = "unsort";
static const char apsfn_ssid[] PROGMEM = "SSID";
static const char apsfn_count[] PROGMEM = "Anzahl";
static const char apsfn_rssi[] PROGMEM = "Pegel";
static const char apsfn_age[] PROGMEM = "Age";
static const char apsfn_mac[] PROGMEM = "MAC";
static const char apsfn_unknown[] PROGMEM = "?";

const char* ap_sort_field_name(ApSortField f)
{
  static char buf[8];
  PGM_P src = apsfn_unknown;
  switch (f) {
    case AP_SORT_NONE:  src = apsfn_unsort; break;
    case AP_SORT_SSID:  src = apsfn_ssid; break;
    case AP_SORT_COUNT: src = apsfn_count; break;
    case AP_SORT_RSSI:  src = apsfn_rssi; break;
    case AP_SORT_AGE:   src = apsfn_age; break;    // NEU 2.27.4
    case AP_SORT_MAC:   src = apsfn_mac; break;    // NEU 2.27.4
  }
  strncpy_P(buf, src, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = '\0';
  return buf;
}

// =====================================================================
// NEU 2.26.0: VENDOR CACHE - Implementierung (DEKLARATIONEN s.o.)
// =====================================================================
// BUGFIX 2.26.3: menu_enter_ssid_list()/_combined()/menu_enter_watchlist()
// werden NICHT nur beim echten Menueeintritt aufgerufen, sondern bei JEDEM
// Redraw (Auto-Refresh-Tick, Sortierung, u/d, t, v, i - siehe redraw_ssid_list()
// bzw. periodischer STATE_WATCHLIST-Tick). Ohne Guard hat vendorCache_begin()
// den Cache bei jedem einzelnen Redraw komplett neu angelegt (0 Eintraege) -
// der Cache konnte sich dadurch NIE ueber mehrere Bildschirmaufbauten hinweg
// aufbauen, genau dort, wo die Beschleunigung eigentlich greifen sollte
// (wiederkehrende Redraws derselben Geraete). g_vendorCacheSessionActive
// sorgt jetzt dafuer, dass vendorCache_begin() beim wiederholten Aufruf
// waehrend derselben Menuesitzung ein No-Op ist; nur der ECHTE Eintritt
// (Sitzung noch nicht aktiv) alloziert/reset. vendorCache_end() wird nicht
// mehr am Ende von menu_enter_ssid_list()/_combined()/menu_enter_watchlist()
// aufgerufen (das haette denselben Effekt gehabt!), sondern ausschliesslich
// an den echten Austrittspunkten (menu_go_back() sowie globaler ESC-Handler).
// Initialisiert Cache beim ECHTEN Eintritt in Menü 3a/4 (startet leer, 0
// Einträge) - bei einem Redraw waehrend laufender Sitzung: No-Op.
void vendorCache_begin()
{
  if (g_vendorCacheSessionActive) {
    return;  // Sitzung laeuft bereits (Redraw) - Cache-Inhalt bleibt erhalten
  }
  if (g_vendorCache != NULL) {
    free(g_vendorCache);
  }
  g_vendorCache = NULL;
  g_vendorCacheCount = 0;
  g_vendorCacheSessionActive = true;
}

// Gibt Cache-Speicher frei beim ECHTEN Austritt aus Menü 3a/4 (aufgerufen
// aus menu_go_back() und dem globalen ESC-Handler, NICHT mehr aus den
// menu_enter_*()-Funktionen selbst).
void vendorCache_end()
{
  if (g_vendorCache != NULL) {
    free(g_vendorCache);
    g_vendorCache = NULL;
  }
  g_vendorCacheCount = 0;
  g_vendorCacheSessionActive = false;
}

// Sucht MAC im Cache.
// BUGFIX 2.26.2: return VENDOR_CACHE_NOT_FOUND (uint32_t 0xFFFFFFFF) wurde
// bei der impliziten Konvertierung nach int zu -1 - demselben Wert, den die
// Funktion auch fuer einen ECHTEN Cache-Miss zurueckgibt. Der Aufrufer
// verglich "cacheResult == VENDOR_CACHE_NOT_FOUND" (int gegen uint32_t),
// wobei -1 durch die ueblichen Arithmetik-Konvertierungsregeln ebenfalls zu
// 0xFFFFFFFF wurde -> JEDER echte Cache-Miss wurde faelschlich als
// Negativ-Treffer erkannt und lieferte sofort "---", ohne die echte Suche
// (getManufacturer) je aufzurufen. Fix: Rueckgabewert ist jetzt strikt nur
// noch -1 (Miss, MAC nicht im Cache) oder 0 (Treffer, egal ob positiv oder
// negativ) - die Unterscheidung positiv/negativ erfolgt ausschliesslich
// ueber outOffset (Sentinel-Vergleich beim Aufrufer), nicht mehr ueber den
// Funktions-Rueckgabewert.
int vendorCache_lookup(uint8_t *mac, uint32_t &outOffset)
{
  if (g_vendorCache == NULL || g_vendorCacheCount == 0) {
    return -1;  // Cache leer
  }
  
  for (int i = 0; i < g_vendorCacheCount; i++) {
    if (memcmp(g_vendorCache[i].mac, mac, 6) == 0) {
      // MAC gefunden - Offset immer setzen, Positiv/Negativ wird beim
      // Aufrufer anhand von outOffset unterschieden
      outOffset = g_vendorCache[i].vendorTextOffset;
      return 0;  // Treffer (positiv ODER negativ, siehe outOffset)
    }
  }
  
  return -1;  // Cache-Miss
}

// Fügt Eintrag zu Cache hinzu (oder tut nichts, wenn bereits voll)
void vendorCache_add_entry(uint8_t *mac, uint32_t offset)
{
  if (g_vendorCacheCount >= VENDOR_CACHE_MAX) {
    return;  // Cache voll, kein weiteres Hinzufügen
  }
  
  // Dynamisches Wachstum: in 8er-Schritten realloc, um Fragmentierung zu reduzieren
  if (g_vendorCache == NULL) {
    g_vendorCache = (VendorCacheEntry *) malloc(8 * sizeof(VendorCacheEntry));
  } else if (g_vendorCacheCount > 0 && g_vendorCacheCount % 8 == 0) {
    int newCapacity = ((g_vendorCacheCount / 8) + 1) * 8;
    if (newCapacity > VENDOR_CACHE_MAX) newCapacity = VENDOR_CACHE_MAX;
    g_vendorCache = (VendorCacheEntry *) realloc(g_vendorCache, 
                                                  newCapacity * sizeof(VendorCacheEntry));
  }
  
  if (g_vendorCache == NULL) {
    return;  // Allokation fehlgeschlagen
  }
  
  // Neuen Eintrag anhängen
  memcpy(g_vendorCache[g_vendorCacheCount].mac, mac, 6);
  g_vendorCache[g_vendorCacheCount].vendorTextOffset = offset;
  g_vendorCacheCount++;
}

// Liest eine Zeile direkt aus vendors.txt bei bekanntem Byte-Offset (Cache-Treffer-Fast-Path)
// Öffnet die Datei, springt zum Offset, liest bis Newline, trimmt und gibt String zurück.
String readVendorLineAtOffset(uint32_t offset)
{
  File f = LittleFS.open("/vendors.txt", "r");
  if (!f) {
    return F("---");
  }
  
  if (!f.seek(offset, SeekSet)) {
    f.close();
    return F("---");
  }
  
  String line = "";
  int c;
  while ((c = f.read()) >= 0 && c != '\n') {
    line += (char) c;
  }
  f.close();
  
  // Trim: Whitespace vom Ende entfernen
  while (line.length() > 0 && (line[line.length() - 1] == '\r' || 
                               line[line.length() - 1] == ' ' ||
                               line[line.length() - 1] == '\t')) {
    line.remove(line.length() - 1);
  }
  
  return line.length() > 0 ? line : F("---");
}

// Wrapper für Vendor-Lookup mit Cache-Integration
// Nutzt Cache wenn vorhanden, sonst normale getManufacturer()-Suche
// BUGFIX 2.26.1: nutzt jetzt den ECHTEN Byte-Offset aus getManufacturer()
// (Referenzparameter) statt einer Dummy-0, die beim naechsten Cache-Treffer
// faelschlich die allererste Zeile von vendors.txt geliefert haette.
// BUGFIX 2.26.2: cacheResult wird jetzt NUR noch auf -1 (Miss) / 0 (Treffer)
// geprueft. Positiv/Negativ wird ausschliesslich anhand von cachedOffset
// unterschieden (siehe vendorCache_lookup() fuer Details zum vorherigen
// signed/unsigned-Vergleichsfehler, der JEDEN Cache-Miss faelschlich als
// Negativ-Treffer behandelt und dadurch die echte Suche nie mehr aufgerufen
// hatte -> alle Vendor-Lookups lieferten "---").
String vendorCache_lookup_or_search(uint8_t *mac)
{
  ram_debug_sample(RDP_VENDOR_LOOKUP);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
  CallChainGuard __cc_guard(RDP_VENDOR_LOOKUP);  // NEU 2.30.35: Call-Chain-Erweiterung
  uint32_t cachedOffset = 0;
  int cacheResult = vendorCache_lookup(mac, cachedOffset);
  ram_debug_sample(RDP_VENDOR_CACHE);  // NEU 2.30.34: passive RAM-/Stack-Diagnose (nach Cache-Zugriff)
  
  if (cacheResult == 0) {
    // Treffer im Cache (MAC bereits gesehen) - Positiv oder Negativ wird
    // ausschliesslich anhand des Offsets unterschieden:
    if (cachedOffset == VENDOR_CACHE_NOT_FOUND) {
      // Negativ-Cache-Hit: wurde schon als "nicht gefunden" gecacht
      return F("---");
    }
    // Positiv-Cache-Hit: direkter Zeilen-Lookup aus vendors.txt (1 Dateizugriff,
    // kein Binaersuche-Overhead, siehe readVendorLineAtOffset)
    return readVendorLineAtOffset(cachedOffset);
  }
  
  // Cache-Miss (cacheResult == -1): normale Suche durchführen, dabei
  // Byte-Offset per Referenz mit abgreifen (getManufacturer ist String-
  // basiert, daher müssen wir die MAC in String-Format konvertieren)
  char macstr[13];
  snprintf_P(macstr, sizeof(macstr), PSTR("%02x%02x%02x%02x%02x%02x"),
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  uint32_t foundOffset = 0;
  String result = VendorLookup::getManufacturer(String(macstr), &foundOffset);
  
  // Ergebnis cachen (falls noch Platz)
  if (g_vendorCacheCount < VENDOR_CACHE_MAX) {
    if (result == "---") {
      // Negativ-Caching
      vendorCache_add_entry(mac, VENDOR_CACHE_NOT_FOUND);
    } else {
      // Positiv-Caching: ECHTER Byte-Offset der Zeile in vendors.txt
      vendorCache_add_entry(mac, foundOffset);
    }
  }
  
  return result;
}

// NEU 2.18.0: Kompakte Age-Zeit Formatierung
// >999s wird als "Xk" angezeigt statt vierstellig (z.B. "2437" -> "2k4", "17490" -> "17k")
// NEU 2.27.1: >99999s wird als "old" angezeigt statt "100k" (das haette die
// garantierte 3-Zeichen-Breite von format_age_field() gesprengt bzw. waere
// durch dessen Kappung zu einem irrefuehrenden "00k" verstuemmelt worden).
// Praktisch nahezu unerreichbar, da MAX_CLIENT_AGE=1000s Clients laengst
// aus clients_known[] entfernt, bevor ihr Alter in diese Groessenordnung
// kommt - dient als Sicherheitsnetz fuer den Fall, dass sich das mal aendert.
const char* format_age_compact(int age_sec)
{
  static char buf[6];
  if (age_sec > 99999) {
    snprintf_P(buf, sizeof(buf), PSTR("old"));
  } else if (age_sec <= 999) {
    snprintf_P(buf, sizeof(buf), PSTR("%d"), age_sec);
  } else if (age_sec <= 9999) {
    // Format: Xk (z.B. 2437 -> "2k4": 2k-Teil=2437/1000=2, Dezimal=4)
    int thousands = age_sec / 1000;
    int hundreds = (age_sec % 1000) / 100;
    snprintf_P(buf, sizeof(buf), PSTR("%dk%d"), thousands, hundreds);
  } else {
    // Format: XXk (z.B. 17490 -> "17k")
    int thousands = age_sec / 1000;
    snprintf_P(buf, sizeof(buf), PSTR("%dk"), thousands);
  }
  return buf;
}

// NEU 2.26.1 BUGFIX: gemeinsame Hilfsfunktion fuer das Age-Feld mit
// GARANTIERT konstanter Breite (3 Zeichen, rechtsbuendig). Single Source
// of Truth fuer Menue 3a (format_client_cell) UND Menue 4 (Watchlist) -
// vorher hatte jede Stelle ihre eigene, voneinander abweichende Formatierung
// (Watchlist nutzte gar nicht format_age_compact(), sondern eigenen Code mit
// einem zusaetzlichen Zeichen "k" ohne Kompensation -> Spaltenversatz).
// WICHTIG: %3s in printf ist eine MINIMUM-Breite, kein Maximum - bei einem
// (praktisch durch MAX_CLIENT_AGE=1000s nahezu ausgeschlossenen, aber nicht
// unmoeglichen) 4+-stelligen Ergebnis von format_age_compact() wuerde %3s
// NICHT kappen und die Spalte wuerde erneut verrutschen. Deshalb hier
// manuelles Padding MIT harter Kappung als Sicherheitsnetz.
const char* format_age_field(int age_sec)
{
  static char field[4];  // 3 Zeichen + Nullterminator, IMMER exakt 3 sichtbare Zeichen
  const char* raw = format_age_compact(age_sec);
  int len = strlen(raw);

  if (len >= 3) {
    // Kappung: bei ueberlangem Ergebnis die letzten 3 Zeichen anzeigen
    // (sollte in der Praxis wegen MAX_CLIENT_AGE=1000s nie eintreten)
    memcpy(field, raw + (len - 3), 3);
    field[3] = '\0';
  } else {
    // Rechtsbuendig mit Leerzeichen auffuellen (len ist 1 oder 2)
    int padCount = 3 - len;
    for (int p = 0; p < padCount; p++) field[p] = ' ';
    memcpy(field + padCount, raw, len);
    field[3] = '\0';
  }

  return field;
}

#define DEVICE_CELL_WIDTH 28

// Findet unter allen Eintraegen mit dieser Station-MAC denjenigen mit dem
// juengsten last_heard (die "aktive" Verbindung dieses Geraets, egal an
// welchem Access Point). Liefert den Index in clients_known[] oder -1.
// BUGFIX 2.27.3: periodisches yield() alle 64 Iterationen eingebaut. Diese
// Funktion ist der eigentliche Kostentreiber - sie wird pro betroffenem
// Client erneut aufgerufen (aus client_is_hideable()/format_client_cell()/
// der Watchlist-Zeile) und scannt dabei JEDES MAL komplett clients_known[].
// Bei vielen Treffern hintereinander (z.B. ein AP mit 45 von 362 Geraeten)
// summierten sich das zu tausenden Vergleichen ohne jede Gelegenheit fuer
// den WLAN-Stack, sich einzuklinken (register_beacon() laeuft aus
// wifi_set_promiscuous_rx_cb() heraus) - das WLAN-Empfangspakete verloren
// gehen liess, waehrend genau diese Zaehlung lief. Alle Aufrufstellen laufen
// im normalen Menue-Rendering-Kontext, nie in einem Callback selbst, daher
// ist yield() hier unbedenklich.
// BUGFIX 2.30.19 (Nutzer-Beobachtung, Menue 3a): verglich bisher die
// last_heard-Rohwerte DIREKT (>), ohne Bezug zu "now" - exakt dieselbe
// Fehlerklasse wie der ap_before()-Bug aus v2.30.18. Nach einem millis()-
// Ueberlauf (alle ~49,7 Tage Laufzeit) kann ein uralter, nie aufgeraeumter
// Geister-Eintrag (z.B. mit AP_IDX_NONE, weil zum Zeitpunkt seiner
// Erfassung noch kein AP-Beacon bekannt war - delete_old_clients() laeuft
// NICHT automatisch, nur ueber das manuelle Cleanup-Menue) einen
// scheinbar GROSSEN last_heard-Rohwert haben und dadurch faelschlich als
// "aktueller" gelten als ein gerade eben frisch aktualisierter Eintrag an
// einem echten, bekannten AP - der frische Eintrag zeigte dann faelschlich
// "gewechselt zu unbekanntem Ziel" (">?"), obwohl er selbst der wahre,
// aktuellste Eintrag war. Fix: wie bei ap_before() jetzt ueber "now -
// last_heard" mit demselben ueberlaufsicheren 32-Bit-Cast vergleichen.
int find_freshest_entry_for_station(uint8_t* station, uint64_t now)
{
  int best = -1;
  uint32_t best_age = 0;
  for (int i = 0; i < clients_known_count; i++) {
    if ((i & 0x3F) == 0) yield();  // alle 64 Iterationen
    if (! memcmp(clients_known[i].station, station, ETH_MAC_LEN)) {
      uint32_t age = (uint32_t)(now - clients_known[i].last_heard);
      if (best == -1 || age < best_age) {
        best = i;
        best_age = age;
      }
    }
  }
  return best;
}

// NEU 2.30.21: Watchlist-Transparenz Client/AP. Bisher durchsuchte die
// Watchlist-Anzeige/Rueckkehr-Signalisierung ausschliesslich clients_known[]
// (via find_freshest_entry_for_station()) - eine MAC, die NIE als Client/
// Station auftritt, sondern ausschliesslich als AP eigene Beacons sendet
// (Nutzer-Fall: Mobilhotspot im Auto), wurde dadurch nie als "gesehen"
// erkannt, obwohl print_mac() sie schon immer korrekt blau markiert hat
// (is_watched_mac() prueft rollenunabhaengig). Diese Funktion ist bewusst
// NUR fuer die Watchlist gedacht (find_freshest_entry_for_station() bleibt
// unveraendert fuer die Client-Roaming-Logik in format_client_cell() etc.,
// wo eine reine AP-Sichtung fachlich keinen Sinn ergibt). Liefert die
// juengste Sichtung ueber BEIDE Quellen hinweg, channel bereits um
// AP_CHANNEL_MASK bereinigt (einheitlich mit der Client-Seite, die das
// Flag-Bit gar nicht erst kennt). Rueckgabetyp watchlist_sighting ist ganz
// oben bei beaconinfo/clientinfo definiert (siehe dortiger Kommentar).
watchlist_sighting find_freshest_watchlist_sighting(uint8_t* mac, uint64_t now)
{
  watchlist_sighting result;
  result.found = false;
  uint32_t best_age = 0;

  for (int i = 0; i < clients_known_count; i++) {
    if ((i & 0x3F) == 0) yield();  // alle 64 Iterationen
    if (! memcmp(clients_known[i].station, mac, ETH_MAC_LEN)) {
      uint32_t age = (uint32_t)(now - clients_known[i].last_heard);
      if (! result.found || age < best_age) {
        result.found = true;
        best_age = age;
        result.last_heard = clients_known[i].last_heard;
        result.channel = clients_known[i].channel;
        result.rssi = clients_known[i].rssi;
      }
    }
  }

  for (int i = 0; i < aps_known_count; i++) {
    if (ap_slot_free(i)) continue;  // stale Sentinel-Slots ausschliessen
    if ((i & 0x3F) == 0) yield();
    if (! memcmp(aps_known[i].bssid, mac, ETH_MAC_LEN)) {
      uint32_t age = (uint32_t)(now - aps_known[i].last_heard);
      if (! result.found || age < best_age) {
        result.found = true;
        best_age = age;
        result.last_heard = aps_known[i].last_heard;
        result.channel = aps_known[i].channel & AP_CHANNEL_MASK;
        result.rssi = aps_known[i].rssi;
      }
    }
  }

  return result;
}

// Findet den Index eines Access Points in aps_known[] anhand seiner BSSID
// (entspricht der Auswahlnummer in Punkt 3). Liefert -1, falls unbekannt.
int find_ap_index_by_bssid(uint8_t* bssid)
{
  for (int i = 0; i < aps_known_count; i++) {
    if (ap_slot_free(i)) continue;  // NEU 2.29.10: stale bssid sonst falsch positiv
    if (! memcmp(aps_known[i].bssid, bssid, ETH_MAC_LEN)) return i;
  }
  return -1;
}

// NEU 2.29.12 BUGFIX: siehe Kommentar beim Prototyp weiter oben.
bool is_valid_ap_bssid(uint8_t *bssid)
{
  static const uint8_t all_zero[ETH_MAC_LEN] = {0, 0, 0, 0, 0, 0};
  if (! memcmp(bssid, all_zero, ETH_MAC_LEN)) return false;
  if (bssid[0] & 0x01) return false;  // Multicast/Broadcast-Bit gesetzt
  return true;
}

// Baut eine kompakte, auf feste Breite aufgefuellte Text-Zelle fuer einen
// Geraete-Eintrag (MAC/Kanal/Alter/RSSI/Trend). Aktualisiert dabei auch
// prev_shown_rssi[]. stale/trend werden fuer die Farbwahl zurueckgegeben.
// Baut eine kompakte Zelle fuer einen Geraete-Eintrag.
// Roaming-Logik: Gibt es fuer diese Station-MAC einen juengeren Eintrag
// (an einem anderen Access Point), wird statt des RSSI-Werts ">n" gezeigt
// (n = Auswahlnummer dieses APs in Punkt 3) und die Zeile ausgegraut.
// Ist die juengste bekannte Sichtung dieser Station insgesamt aelter als
// STALE_AGE_SEC, wird stattdessen "out" angezeigt (Geraet nirgends mehr
// aktiv gesehen).
// NEU 2.17.2: Reine Pruef-Funktion (keine Seiteneffekte!) fuer den
// Ignore-Filter (Taste 'i'). Bildet dieselbe station_gone/is_freshest-Logik
// wie format_client_cell() nach, aber OHNE prev_shown_rssi[] zu veraendern -
// so kann sie zum Vorfiltern der Anzeigeliste genutzt werden, ohne die
// RSSI-Trend-Erkennung beim eigentlichen Druckvorgang zu verfaelschen.
bool client_is_hideable(int slot, uint64_t now)
{
  clientinfo ci = clients_known[slot];
  int freshest = find_freshest_entry_for_station(ci.station, now);
  int freshest_age = (freshest >= 0) ? (int)(now - clients_known[freshest].last_heard) : (int)(now - ci.last_heard);
  bool station_gone = (freshest_age > STALE_AGE_SEC);
  bool is_freshest = (freshest == slot);
  return station_gone || !is_freshest;  // "out" oder auf anderen AP gewechselt
}

// NEU 2.29.7: eigene, schmalere Pruef-Funktion nur fuer den Ignore-Filter
// (Taste 'i') - der soll ab jetzt NUR NOCH AP-Wechsler ausblenden, "out"-
// Eintraege bleiben sichtbar (zeigen den letzten Pegel + "out" in der
// Kanal-/AP-Spalte, siehe format_client_cell). client_is_hideable() bleibt
// bewusst unveraendert, da print_ap_cell() sie fuer die Aktiv-Zaehlung im
// AP-Overview (Menue 3) braucht - dort soll "out" weiterhin NICHT als
// aktiv gezaehlt werden, das ist ein anderer Anwendungsfall als der
// Ignore-Filter in Menue 3a.
bool client_is_switched(int slot, uint64_t now)
{
  clientinfo ci = clients_known[slot];
  int freshest = find_freshest_entry_for_station(ci.station, now);
  return (freshest != slot);  // true = auf anderen AP gewechselt (unabhaengig von "out")
}

// NEU 2.29.7: zwei neue Output-Parameter out_is_out/out_switched_ap_idx -
// die db-Spalte (valuestr) zeigt jetzt IMMER den letzten registrierten
// Pegelwert, "out"/">N" wandert stattdessen in diese beiden Parameter und
// wird von den Aufrufern (print_client_cell/print_client_cell_ap_mode) in
// die Kanal- bzw. AP-Spalte gelegt. out_switched_ap_idx: -1 = nicht
// gewechselt ODER Ziel-AP unbekannt (siehe out_is_switched fuer die
// Unterscheidung).
void format_client_cell(char* macstr, char* buf, int bufsize, int slot, uint64_t now, bool* out_stale, int* out_trend, bool* out_is_out, bool* out_is_switched, int* out_switched_ap_idx)
{
  clientinfo ci = clients_known[slot];
  int age = (int)(now - ci.last_heard);

  for (int b = 0; b < 6; b++) sprintf_P(macstr + b * 2, PSTR("%02x"), ci.station[b]);
  macstr[12] = '\0';

  int freshest = find_freshest_entry_for_station(ci.station, now);
  int freshest_age = (freshest >= 0) ? (int)(now - clients_known[freshest].last_heard) : age;
  bool station_gone = (freshest_age > STALE_AGE_SEC);
  bool is_freshest = (freshest == slot);

  bool stale;
  int trend = 0;
  int delta = 0;
  char trend_slot_suffix[8] = "";  // NEU 2.30.16/2.30.20: Wechsel- ODER "out"-Hinweis fuer den Trend-Platz (statt der AP-Spalte)
  char valuestr[8];
  // NEU 2.29.7: db-Spalte zeigt immer den letzten registrierten Pegel,
  // unabhaengig von out/Wechsel-Status.
  snprintf_P(valuestr, sizeof(valuestr), PSTR("%d"), ci.rssi);

  *out_is_out = false;
  *out_is_switched = false;
  *out_switched_ap_idx = -1;

  // BUGFIX 2.30.15 (Nutzer-Beobachtung): Reihenfolge der beiden Pruefungen
  // getauscht. Vorher stand "station_gone" (out) an erster Stelle - sobald
  // der AKTUELLSTE Eintrag eines Clients (an dem AP, zu dem er zuletzt
  // gewechselt ist) 600s alt wurde, kippten dadurch ALLE Eintraege dieser
  // Station gleichzeitig auf "out" - auch alte, laengst nicht mehr aktuelle
  // Eintraege an frueheren APs, die bereits korrekt ">N" (gewechselt zu AP N)
  // zeigten. Das ueberschrieb die eigentlich dauerhafte historische
  // Tatsache "ist zu AP N gewechselt" mit dem spaeteren, unabhaengigen
  // Ereignis "ist inzwischen komplett aus der Reichweite". Jetzt gilt: ein
  // NICHT aktuellster Eintrag zeigt IMMER ">N" (dauerhaft eingefroren,
  // unabhaengig vom Alter) - "out" kann nur noch der jeweils aktuellste
  // Eintrag selbst werden.
  if (!is_freshest) {
    stale = true;
    *out_is_switched = true;
    // NEU 2.29.11 (Etappe 3): ap_idx ist bereits der Index, kein Lookup mehr noetig.
    int ap_idx = clients_known[freshest].ap_idx;
    *out_switched_ap_idx = (ap_idx < aps_known_count && !ap_slot_free(ap_idx)) ? ap_idx : -1;  // -1 = Ziel-AP nicht (mehr) gueltig
    // NEU 2.30.16 (Nutzerwunsch): Das Wechselziel ">N" stand bisher in der
    // AP-Spalte selbst und verdeckte dadurch, ZU WELCHEM AP dieser Eintrag
    // eigentlich gehoert (die eigene AP-Nummer war nicht mehr sichtbar).
    // Jetzt bleibt die AP-Spalte der eigenen AP-Nummer vorbehalten (siehe
    // print_client_cell()/print_client_cell_ap_mode()), das Wechselziel
    // wandert stattdessen hierher in den sonst bei einem gewechselten/
    // inaktiven Eintrag ungenutzten Trend-Platz. Bleibt automatisch so
    // lange stehen, bis DIESER Eintrag (dieser AP) selbst wieder der
    // aktuellste wird (is_freshest dann wieder true) - kein zusaetzlicher
    // Zeitstempel/Zustand noetig, ergibt sich direkt aus der bestehenden
    // Freshest-Logik.
    if (*out_switched_ap_idx >= 0) snprintf_P(trend_slot_suffix, sizeof(trend_slot_suffix), PSTR(" >%d"), *out_switched_ap_idx);
    else snprintf_P(trend_slot_suffix, sizeof(trend_slot_suffix), PSTR(" >?"));
  } else if (station_gone) {
    stale = true;
    *out_is_out = true;
    // NEU 2.30.20 (Nutzerwunsch): "out" stand bisher in der AP-Spalte
    // selbst und verdeckte dadurch, von WELCHEM AP aus der Client den
    // WLAN-Bereich komplett verlassen hat. Jetzt bleibt die AP-Spalte auch
    // hier der eigenen AP-Nummer vorbehalten (siehe print_client_cell()/
    // print_client_cell_ap_mode()), "out" wandert stattdessen - genau wie
    // schon das Wechselziel ">N" - in den sonst ungenutzten Trend-Platz.
    snprintf_P(trend_slot_suffix, sizeof(trend_slot_suffix), PSTR(" out"));
  } else {
    stale = (age > STALE_AGE_SEC);
    int prev = prev_shown_rssi[slot];
    if (prev > -1000) {
      delta = ci.rssi - prev;
      if (delta >= rssi_trend_threshold) trend = 1;
      else if (delta <= -rssi_trend_threshold) trend = 2;
    }
  }

  // Fuehrende MAC (12 Zeichen) entfaellt hier bewusst - sie wird separat
  // per print_mac() ausgegeben, damit sie unabhaengig von der restlichen
  // Zeilenfarbe blau markiert werden kann, falls sie auf der Watchlist steht.
  // NEU 2.18.0: Age-Format kompakt (>999s als "Xk" statt vierstellig)
  // BUGFIX 2.26.1: nutzt jetzt format_age_field() (garantiert konstante
  // Breite, harte Kappung als Sicherheitsnetz) statt %3s (das nur eine
  // Minimum-Breite ist und bei laengeren Strings nicht mehr ausgerichtet
  // haette). Dieselbe Funktion wird auch von der Watchlist (Menue 4)
  // verwendet, damit beide Ansichten synchron bleiben.
  const char* age_str = format_age_field(age);

  int len = snprintf_P(buf, bufsize, PSTR(" %-2d %s %3s"), ci.channel, age_str, valuestr);
  if (trend == 1) len += snprintf_P(buf + len, bufsize - len, PSTR(" ^+%d"), delta);
  else if (trend == 2) len += snprintf_P(buf + len, bufsize - len, PSTR(" v%d"), delta);
  else if (trend_slot_suffix[0] != '\0') len += snprintf_P(buf + len, bufsize - len, PSTR("%s"), trend_slot_suffix);  // NEU 2.30.16

  while (len < DEVICE_CELL_WIDTH - 12 && len < bufsize - 1) buf[len++] = ' ';
  buf[len] = '\0';

  prev_shown_rssi[slot] = ci.rssi;
  *out_stale = stale;
  *out_trend = trend;
}

// Druckt eine Geraete-Zelle inkl. Farbe (ohne Zeilenumbruch). Die MAC-
// Adresse wird ueber print_mac() ausgegeben und dadurch blau markiert,
// falls sie auf der Watchlist steht - unabhaengig von stale/Trend-Farbe.
// NEU 2.12.0: Wie print_client_cell(), aber zeigt die AP-Nummer statt des Kanals
// Wird in Modus 3 (Multi-AP) verwendet. Bei ausgegraut wird "--" angezeigt.
void print_client_cell_ap_mode(int slot, uint8_t *ap_indices, int ap_count, uint64_t now, Print* out)
{
  char macstr[13];
  char rest[48];
  bool stale;
  int trend;
  bool is_out, is_switched;
  int switched_ap_idx;
  format_client_cell(macstr, rest, sizeof(rest), slot, now, &stale, &trend, &is_out, &is_switched, &switched_ap_idx);

  // NEU 2.29.7: AP-Spalte auf 3 Zeichen erweitert (rechtsbuendig).
  // NEU 2.30.16 (Nutzerwunsch): bei Wechsel (is_switched) zeigt diese
  // Spalte die EIGENE AP-Nummer statt ">N" - sonst war nicht mehr
  // erkennbar, VON WELCHEM AP aus gewechselt wurde. Das Wechselziel ">N"
  // steht seit v2.30.16 stattdessen im Trend-Platz (Teil von rest).
  // NEU 2.30.20 (Nutzerwunsch): dasselbe jetzt auch bei "out" - die Spalte
  // zeigt weiterhin die eigene AP-Nummer, "out" steht seit v2.30.20
  // ebenfalls im Trend-Platz. Damit ist immer erkennbar, von welchem AP
  // aus der Client den WLAN-Bereich verlassen hat.
  char ap_str[4];
  {
    // NEU 2.29.11 (Etappe 3): ap_idx ist bereits der Index, kein Lookup mehr noetig.
    int ap_idx = clients_known[slot].ap_idx;
    bool ap_valid = (ap_idx < aps_known_count && !ap_slot_free(ap_idx));
    if (ap_valid) snprintf_P(ap_str, sizeof(ap_str), PSTR("%d"), ap_idx);
    else strcpy(ap_str, "--");
  }

  // NEU 2.28.0: Farbe nur auf der echten Konsole (out == &Serial) setzen.
  bool to_console = (out == &Serial);
  const char* line_color = stale ? "90" : (trend == 1 ? "32" : (trend == 2 ? "31" : NULL));
  if (to_console && line_color) vt_sgr(line_color);
  print_mac(clients_known[slot].station, line_color, out);

  // Das Kanal-Feld (erste 4 Zeichen von rest: " %-2d ") wird hier komplett
  // durch die AP-Spalte ersetzt statt nur vorangestellt - dadurch kein
  // ueberfluessiger Kanal-Wert mehr in dieser Ansicht, minimaler Abstand.
  char output[64];
  snprintf_P(output, sizeof(output), PSTR(" %3s %s"), ap_str, rest + 4);
  out->print(output);

  if (to_console && line_color) vt_color_reset();
}

void print_client_cell(int slot, uint64_t now, Print* out)
{
  char macstr[13];
  char rest[48];
  bool stale;
  int trend;
  bool is_out, is_switched;
  int switched_ap_idx;
  format_client_cell(macstr, rest, sizeof(rest), slot, now, &stale, &trend, &is_out, &is_switched, &switched_ap_idx);

  // NEU 2.29.7: die bisherige Kanal-Spalte auf 3 Zeichen rechtsbuendig
  // erweitert. NEU 2.30.16/2.30.20: zeigt bei Wechsel UND bei "out"
  // weiterhin den eigenen Kanal (wie im Normalfall) - siehe Kommentar in
  // print_client_cell_ap_mode().
  char ch_str[4];
  snprintf_P(ch_str, sizeof(ch_str), PSTR("%d"), clients_known[slot].channel);

  // NEU 2.28.0: Farbe nur auf der echten Konsole (out == &Serial) setzen.
  bool to_console = (out == &Serial);
  const char* line_color = stale ? "90" : (trend == 1 ? "32" : (trend == 2 ? "31" : NULL));
  if (to_console && line_color) vt_sgr(line_color);
  print_mac(clients_known[slot].station, line_color, out);

  // Kanal-Feld (erste 4 Zeichen von rest: " %-2d ") ersetzen, analog zu
  // print_client_cell_ap_mode.
  char output[64];
  snprintf_P(output, sizeof(output), PSTR(" %3s %s"), ch_str, rest + 4);
  out->print(output);

  if (to_console && line_color) vt_color_reset();
}

// AP_CELL_WIDTH/AP_CELL_SSID_WIDTH sind bereits am Dateianfang definiert

// Baut eine kompakte Zelle fuer eine SSID-Uebersichtszeile (Punkt 3a).
// ssid_width steuert, wie breit das SSID-Feld dargestellt wird (im
// zweispaltigen Modus schmaler, damit beide Spalten nebeneinander passen).
// Baut+druckt eine kompakte Zelle fuer eine SSID-Uebersichtszeile (Punkt 3,
// AP-Auswahl). Reihenfolge: # SSID Geraeteanzahl Kanal Pegel [MAC].
// Im zweispaltigen Modus (two_col=true) entfaellt die MAC-Adresse, damit
// beide Spalten unter 80 Zeichen passen. Keine "ch"/"G"/"dB"-Textlabels
// mehr pro Zeile - die stehen einmalig im Spaltenkopf.
// NEU 2.26.x: show_vendor - wenn aktiv, entfallen Geraete/Kanal/dB komplett
// (Aufrufer erzwingt dafuer two_col=false), stattdessen SSID, MAC, Hersteller
// in einer Zeile. Kein Cache-Fuellstand-Zaehl-Loop noetig in diesem Zweig,
// da dev_count/active_count hier gar nicht angezeigt werden.
void print_ap_cell(int idx, int ssid_width, bool two_col, uint64_t now, bool show_vendor, Print* out)
{
  // NEU 2.28.0: Farbe nur auf der echten Konsole (out == &Serial) setzen.
  bool to_console = (out == &Serial);
  beaconinfo bi = aps_known[idx];
  bool stale = ((int)(now - bi.last_heard) > STALE_AGE_SEC);
  bool is_open = (bi.channel & AP_OPEN_FLAG) != 0;  // NEU 2.29.8
  const char* line_color = stale ? "90" : NULL;

  if (show_vendor) {
    char buf[24];
    int len;
    if (is_open) {
      len = snprintf_P(buf, sizeof(buf), PSTR("%2d)(%-*.*s0 "),
                        idx, ssid_width, ssid_width, bi.ssid);
    } else {
      len = snprintf_P(buf, sizeof(buf), PSTR("%2d)[%-*.*s] "),
                        idx, ssid_width, ssid_width, bi.ssid);
    }
    buf[len] = '\0';
    if (to_console && stale) vt_sgr("90");
    out->print(buf);
    if (to_console && stale) vt_color_reset();
    // BUGFIX 2.30.17 (Nutzer-Beobachtung): print_mac() resettet die Farbe
    // intern NUR, wenn die MAC randomisiert/beobachtet ist UND dabei kein
    // restore_sgr uebergeben wurde - bei einer STALEN Zeile (restore_sgr=
    // "90") "restauriert" print_mac() bewusst auf Grau statt komplett
    // zurueckzusetzen, in der Erwartung, dass die aufrufende Stelle danach
    // noch selbst zurücksetzt (genau wie print_client_cell()/
    // print_client_cell_ap_mode() es schon tun). print_ap_cell() tat das
    // bisher NICHT - die Grau-Faerbung "leckte" dadurch in die naechste
    // Zeile, wenn print_mac() als letztes auf einer stalen Zeile lief. Jetzt
    // wie im Client-Pendant explizit vor/nach print_mac() eingerahmt.
    if (to_console && line_color) vt_sgr(line_color);
    print_mac(bi.bssid, line_color, out);
    if (to_console && line_color) vt_color_reset();
    out->print(F("  "));
    String vendor = vendorCache_lookup_or_search(bi.bssid);
    if (to_console && stale) vt_sgr("90");
    out->print(vendor.c_str());
    if (to_console && stale) vt_color_reset();
    return;
  }

  // BUGFIX 2.27.3: Diese Schleife kann bei langen Listen sehr teuer werden -
  // client_is_hideable() ruft intern find_freshest_entry_for_station() auf,
  // eine WEITERE komplette Schleife ueber clients_known_count. Fuer einen AP
  // mit z.B. 45 von 362 Geraeten sind das ca. 45*362 ≈ 16.300 Vergleiche,
  // OHNE jedes yield() dazwischen. register_beacon() wird aus dem
  // WLAN-Stack heraus per wifi_set_promiscuous_rx_cb() aufgerufen und
  // braucht regelmaessig Gelegenheit, sich einzuklinken - bleibt der Code
  // zu lange am Stueck ohne yield(), kann der Stack ausgehungert werden und
  // tatsaechlich eintreffende Pakete verlieren. Das erklaert, warum genau
  // die AP-Eintraege mit den MEISTEN Geraeten (= teuerste Zaehlung) die
  // niedrigste "aktiv"-Zahl zeigten: waehrend ihrer Zaehlung gingen Pakete
  // verloren, die den Age-Wert anderer, gerade aktiver Clients aufgefrischt
  // haetten. Periodisches yield() alle 32 Iterationen behebt das, ohne die
  // Zaehllogik selbst aendern zu muessen.
  int dev_count = 0;
  int active_count = 0;
  for (int c = 0; c < clients_known_count; c++) {
    if ((c & 0x1F) == 0) yield();  // alle 32 Iterationen
    if (clients_known[c].ap_idx == idx) {
      dev_count++;
      if (!client_is_hideable(c, now)) active_count++;
    }
  }

  char dev_str[12];
  snprintf_P(dev_str, sizeof(dev_str), PSTR("%d/%d"), dev_count,
           active_count);
  char buf[96];
  int len;
  
  // Schreibe nur den Index und die SSID in Klammern (rund = offenes WLAN,
  // NEU 2.29.8)
  if (is_open) {
    len = snprintf_P(buf, sizeof(buf), PSTR("%2d)(%-*.*s0"),
                   idx, ssid_width, ssid_width, bi.ssid);
  } else {
    len = snprintf_P(buf, sizeof(buf), PSTR("%2d)[%-*.*s]"),
                   idx, ssid_width, ssid_width, bi.ssid);
  }
  
  // Schreibe die Spalten direkt: Gesamte Ger-Spalte (%6s), Kanal (%2d), RSSI
  // %6s macht dev_str (z.B. "6/0", "33/10") rechtsbündig in 6 Zeichen Breite
  // Das ergibt die benötigten Abstände zwischen den Spalten
  // NEU 2.29.8: AP_CHANNEL_MASK, da Bit 7 jetzt das Offen-Flag sein kann
  len += snprintf_P(buf + len, sizeof(buf) - len, PSTR(" %6s %2d %d"),
                  dev_str, bi.channel & AP_CHANNEL_MASK, bi.rssi);
  buf[len] = '\0';
  
  if (to_console && stale) vt_sgr("90");
  out->print(buf);
  if (to_console && stale) vt_color_reset();
  
  // Im einspaltigem Modus: Age + MAC-Adresse anhängen
  // NEU 2.27.1 REQ-3: Age-Spalte zwischen dB und MAC eingefuegt (nur hier,
  // im zweispaltigen Modus bleibt es wie bisher ohne MAC/Age - kein Platz).
  // Nutzt dieselbe format_age_field()-Funktion wie Menue 3a/4 fuer
  // konsistente 3-Zeichen-Breite.
  if (!two_col) {
    int age_sec = (int)(now - bi.last_heard);
    out->print(F(" "));
    if (to_console && stale) vt_sgr("90");
    out->print(format_age_field(age_sec));
    if (to_console && stale) vt_color_reset();
    out->print(F(" "));
    // BUGFIX 2.30.17: siehe ausfuehrlichen Kommentar im show_vendor-Zweig
    // oben - print_mac() resettet nicht zuverlaessig, deshalb hier wie im
    // Client-Pendant explizit einrahmen.
    if (to_console && line_color) vt_sgr(line_color);
    print_mac(bi.bssid, line_color, out);
    if (to_console && line_color) vt_color_reset();
  }
}

void print_sort_legend()
{
  Serial.print(F(" Sort:"));
  // NEU 2.30.14: SORT_NONE (3) mit einschliessen, analog zur AP-Sortier-
  // Legende oben, die alle ApSortField-Werte durchlaeuft.
  for (int f = 0; f <= 3; f++) {
    SortField sf = (SortField) f;
    bool active = (sf == current_sort_field);
    Serial.print(F(" "));
    if (active) {
      Serial.print(F("["));
      Serial.print(sort_field_name(sf));
      Serial.print(sort_ascending ? "^]" : "v]");
    } else {
      Serial.print(sort_field_name(sf));
    }
  }
  Serial.printf_P(PSTR(" (u/m/a/r=Sortierung/Richtung)\r\n"));
}

void menu_enter_ssid_list(int ap_index)
{
  ram_debug_sample(RDP_CLIENT_LIST);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
  CallChainGuard __cc_guard(RDP_CLIENT_LIST);  // NEU 2.30.35: Call-Chain-Erweiterung
  menu_state = STATE_SSID_LIST;
  current_list_mode = 1;  // Modus 1 = einzelner AP
  current_list_ap_index = ap_index;
  ssid_list_combined = false;
  // NEU 2.30.6: 'w'-Eingabemodus (Client-Frame-Analyse) beim (Wieder-)Eintritt
  // zuruecksetzen - analog zum Reset in menu_enter_ssid_select().
  ssid_input_len = 0;
  client_select_analyze_mode = false;
  client_frametrap_mode = false;  // NEU 2.30.11
  led_force_off();  // NEU 2.17.6: zeitkritisch (lange Listenausgabe) - Status-LED aus
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  
  // NEU 2.26.0: Vendor-Cache beim Menueeintritt initialisieren
  vendorCache_begin();

  if (ap_index < 0 || ap_index >= aps_known_count || ap_slot_free(ap_index)) {
    Serial.println(F(" Ungueltige Auswahl."));
    Serial.println(F(" Backspace/ESC = zurueck"));
    return;
  }

  // Passende Clients zuerst sammeln, damit die Anzahl schon im Header steht
  // NEU 2.21.1 OPTIMIZATION: uint16_t statt int (konsistent mit sort_clients)
  // BUGFIX 2.30.10: war bisher "uint16_t matches[MAX_CLIENTS_TRACKED]" als
  // Stack-Array - bei MAX_CLIENTS_TRACKED=1000 sind das 2000 Byte, die
  // WAEHREND DER GESAMTEN FUNKTIONSLAUFZEIT auf dem ohnehin knappen
  // ESP8266-"cont"-Stack (Standard 4096 Byte) belegt blieben - allein
  // dieses eine Array also die HAELFTE des gesamten Stacks, fuer die
  // gesamte Dauer aller tiefer verschachtelten Aufrufe darunter. Genau das
  // liess den Vendor-Lookup-Aufrufpfad (siehe dessen eigene "RAM-Fix"-
  // Kommentare, an sich schon knapp bemessen) bei aktiviertem "Hersteller
  // anzeigen" in Menue 3a mit "Panic ... __yield" abstuerzen (Absturz tief
  // in getVendorByLineNumber(), aber verursacht durch fehlenden Stack-
  // Puffer hier oben). Fix: genau wie blockBuf/buffer in der VendorLookup-
  // Klasse selbst jetzt auf malloc()/free() umgestellt (Heap statt Stack) -
  // kein dauerhafter RAM-Verbrauch, nur waehrend dieser Funktion belegt.
  uint16_t *matches = (uint16_t*) malloc(MAX_CLIENTS_TRACKED * sizeof(uint16_t));
  if (matches == NULL) {
    Serial.println(F(" Fehler: kein Speicher fuer die Geraeteliste verfuegbar."));
    Serial.println(F(" Backspace/ESC = zurueck"));
    return;
  }
  uint16_t match_count = 0;
  uint64_t now = effective_now();  // NEU 2.20.9 BUG1: move before loop for hideable check
  
  for (int u = 0; u < clients_known_count; u++) {
    if (clients_known[u].ap_idx == ap_index) {
      // NEU 2.20.9 BUG1: Wenn list_hide_inactive=true, nur nicht-hideable Clients anzeigen (konsistent mit Mode 2)
      // GEAENDERT 2.29.7: blendet nur noch AP-Wechsler aus, "out" bleibt sichtbar
      if (list_hide_inactive && client_is_switched(u, now)) continue;
      
      matches[match_count] = u;
      match_count++;
    }
  }

  sort_clients(matches, match_count, now);

  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" %d Geraete fuer SSID: %s\r\n"), match_count, aps_known[ap_index].ssid);
  Serial.print(F(" AP-MAC: "));
  for (int i = 0; i < 6; i++) Serial.printf_P(PSTR("%02x"), aps_known[ap_index].bssid[i]);
  Serial.printf_P(PSTR(" %d dB"), aps_known[ap_index].rssi);
  
  // NEU 2.21.0: Hersteller des AP anzeigen, wenn aktiv
  if (show_vendors_in_menu3a) {
    // BUGFIX 2.26.1: nutzt jetzt tatsaechlich den Vendor-Cache statt direkt
    // VendorLookup::getManufacturer() aufzurufen (alter Aufruf auskommentiert):
    // String ap_vendor = VendorLookup::getManufacturer(String(ap_mac_str));
    String ap_vendor = vendorCache_lookup_or_search(aps_known[ap_index].bssid);
    Serial.printf_P(PSTR(" Hersteller: %s"), ap_vendor.c_str());
  }
  Serial.println();
  Serial.println(F("======================================================="));
  print_sort_legend();
  Serial.printf_P(PSTR(" RSSI-Trend-Schwelle: %d dB (t=aendern)\r\n"), rssi_trend_threshold);
  Serial.printf_P(PSTR(" Ignoriere AP-Wechsel/Out: %s (i=toggle)\r\n"), list_hide_inactive ? "EIN" : "AUS");
  Serial.printf_P(PSTR(" Aktualisierung: %ds (+ = +5s, - = -5s)\r\n"), list_refresh_sec);
  // NEU 2.21.0: Vendor-Info zur Hilfe hinzufügen
  Serial.printf_P(PSTR(" Hersteller anzeigen: %s (v=toggle)\r\n"), show_vendors_in_menu3a ? "EIN" : "AUS");
  // NEU 2.30.6: Hinweis auf Client-Frame-Analyse (nur Modus 1 - die Nummern
  // vor jeder Zeile unten sind der echte clients_known-Array-Index).
  Serial.println(F(" w+Zahl+Enter = naechstes Paket des Clients analysieren"));
  Serial.println(F(" wp+Zahl+Enter = FrameTrap wartet auf Probe Request, max.5"));
  Serial.println(F("wt+Zahl+Enter = TimeWatch aktivieren"));
  Serial.println(F("b = Hintergrundverkehr-Statistik dieses APs starten"));
  Serial.println(F("-------------------------------------------------------"));
  
  // NEU 2.21.0: Bei Vendor-Anzeige immer einspaltig (two_col = false)
  bool two_col = false;
  if (!show_vendors_in_menu3a) {
    two_col = (two_col_threshold_devices > 0 && match_count > two_col_threshold_devices);
  }
  
  if (show_vendors_in_menu3a) {
    // Header mit Hersteller-Spalte
    Serial.println(F("  #   MAC          ch  Age  db      Hersteller"));
    Serial.println(F("-------------------------------------------------------"));
  } else if (two_col) {
    // Standard zwei-spaltig
    Serial.println(F("  #   MAC          ch  Age  db        #   MAC          ch  Age  db"));
    Serial.println(F("----------------------------------------------------------------------"));
  } else {
    // Standard ein-spaltig
    Serial.println(F("  #   MAC          ch  Age  db"));
    Serial.println(F("-------------------------------------------------------"));
  }
  
  int half = two_col ? (match_count + 1) / 2 : match_count;
  for (int i = 0; i < half; i++) {
    Serial.print(F(" "));
    
    if (show_vendors_in_menu3a) {
      // Einspaltig mit Hersteller - On-Demand Lookup
      // NEU 2.30.6: Nummer (= echter clients_known-Index) davor, fuer
      // w+Zahl+Enter (Probe-Request-Analyse). print_client_cell() selbst
      // bleibt unveraendert (auch von Watchlist/ntfy genutzt).
      Serial.printf_P(PSTR("%3d) "), matches[i]);
      print_client_cell(matches[i], now);
      Serial.print(F(" "));
      
      // BUGFIX 2.26.1: nutzt jetzt tatsaechlich den Vendor-Cache statt bei
      // JEDEM Redraw erneut die volle Tabellensuche zu durchlaufen (alter
      // Aufruf auskommentiert):
      // char mac_str[18];
      // snprintf_P(mac_str, sizeof(mac_str), PSTR("%02x:%02x:%02x:%02x:%02x:%02x"), ...);
      // String vendor = VendorLookup::getManufacturer(String(mac_str));
      String vendor = vendorCache_lookup_or_search(clients_known[matches[i]].station);
      Serial.print(vendor.c_str());
    } else {
      // Standard-Ausgabe (zwei oder ein spaltig)
      // NEU 2.30.6: Nummer (= echter clients_known-Index) davor, siehe oben.
      Serial.printf_P(PSTR("%3d) "), matches[i]);
      print_client_cell(matches[i], now);
      if (two_col) {
        int right_i = half + i;
        if (right_i < match_count) {
          Serial.print(F("  "));
          Serial.printf_P(PSTR("%3d) "), matches[right_i]);
          print_client_cell(matches[right_i], now);
        }
      }
    }
    
    Serial.println();
    yield();
  }
  if (match_count == 0) {
    Serial.println(F(" (keine Geraete zu dieser SSID gefunden)"));
  }

  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Backspace = zurueck zur SSID-Auswahl, ESC = Menue."));
  last_list_refresh_time = millis() / 1000;
  free(matches);  // NEU 2.30.10: siehe Kommentar bei der malloc()-Stelle oben
  
  // BUGFIX 2.26.3: vendorCache_end() hier ENTFERNT - diese Funktion wird bei
  // JEDEM Redraw aufgerufen (nicht nur beim echten Eintritt), ein Aufruf
  // hier haette den Cache sofort nach jedem Bildschirmaufbau wieder
  // verworfen. Freigabe erfolgt jetzt ausschliesslich an den echten
  // Austrittspunkten (menu_go_back(), globaler ESC-Handler).
}

// Wie menu_enter_ssid_list(), zeigt aber nicht nur die Clients EINES
// Access Points, sondern aller Access Points, die dieselbe SSID senden
// wie der bei seed_ap_index ausgewaehlte (z.B. mehrere Repeater/APs im
// selben WLAN). Aufgerufen ueber S+Zahl+Enter in Punkt 3a.
void menu_enter_ssid_list_combined(int seed_ap_index)
{
  menu_state = STATE_SSID_LIST;
  current_list_mode = 2;  // Modus 2 = SSID-Bündelung (alle APs mit gleicher SSID)
  ssid_list_combined = true;
  led_force_off();  // NEU 2.17.6: zeitkritisch (lange Listenausgabe) - Status-LED aus
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  
  // NEU 2.26.0: Vendor-Cache beim Menueeintritt initialisieren
  vendorCache_begin();

  if (seed_ap_index < 0 || seed_ap_index >= aps_known_count || ap_slot_free(seed_ap_index)) {
    Serial.println(F(" Ungueltige Auswahl."));
    Serial.println(F(" Backspace/ESC = zurueck"));
    return;
  }

  memcpy(ssid_list_combined_ssid, aps_known[seed_ap_index].ssid, 32);
  ssid_list_combined_ssid[32] = '\0';
  current_list_ap_index = seed_ap_index;

  // NEU 2.21.0 OPTIMIZATION (Punkt 3.1): int zu uint8_t
  // BUGFIX 2.30.10: ap_matches/matches jetzt auf malloc()/free() umgestellt
  // (Heap statt Stack) - siehe ausfuehrlichen Kommentar in
  // menu_enter_ssid_list() zum selben Fix. Zusammen 2150 Byte Stack-
  // Ersparnis waehrend der gesamten Funktionslaufzeit.
  uint8_t *ap_matches = (uint8_t*) malloc(MAX_APS_TRACKED * sizeof(uint8_t));
  if (ap_matches == NULL) {
    Serial.println(F(" Fehler: kein Speicher fuer die AP-Liste verfuegbar."));
    Serial.println(F(" Backspace/ESC = zurueck"));
    return;
  }
  uint8_t ap_match_count = 0;
  for (int a = 0; a < aps_known_count; a++) {
    if (ap_slot_free(a)) continue;  // NEU 2.29.10: stale ssid sonst falsch positiv
    if (strcmp((const char*)aps_known[a].ssid, ssid_list_combined_ssid) == 0) {
      ap_matches[ap_match_count] = a;
      ap_match_count++;
    }
  }

  // Alle Clients sammeln, die zu einem dieser Access Points gehoeren
  // NEU 2.21.1 OPTIMIZATION: uint16_t statt int (konsistent mit sort_clients)
  uint16_t *matches = (uint16_t*) malloc(MAX_CLIENTS_TRACKED * sizeof(uint16_t));
  if (matches == NULL) {
    Serial.println(F(" Fehler: kein Speicher fuer die Geraeteliste verfuegbar."));
    Serial.println(F(" Backspace/ESC = zurueck"));
    free(ap_matches);
    return;
  }
  uint16_t match_count = 0;
  for (int u = 0; u < clients_known_count; u++) {
    for (int k = 0; k < ap_match_count; k++) {
      if (clients_known[u].ap_idx == ap_matches[k]) {
        matches[match_count] = u;
        match_count++;
        break;
      }
    }
  }

  uint64_t now = effective_now();

  // NEU 2.17.2, geaendert 2.29.7: Ignore-Filter (Taste 'i') - blendet nur noch AP-Wechsler aus, "out"-Eintraege bleiben sichtbar
  if (list_hide_inactive) {
    int filtered_count = 0;
    for (int i = 0; i < match_count; i++) {
      if (!client_is_switched(matches[i], now)) {
        matches[filtered_count++] = matches[i];
      }
    }
    match_count = filtered_count;
  }

  sort_clients(matches, match_count, now);

  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" %d Geraete fuer SSID: %s\r\n"), match_count, ssid_list_combined_ssid);
  Serial.printf_P(PSTR(" kombiniert, %d Access Points mit dieser SSID\r\n"), ap_match_count);
  Serial.println(F("======================================================="));
  print_sort_legend();
  Serial.printf_P(PSTR(" RSSI-Trend-Schwelle: %d dB (t=aendern)\r\n"), rssi_trend_threshold);
  Serial.printf_P(PSTR(" Ignoriere AP-Wechsel/Out: %s (i=toggle)\r\n"), list_hide_inactive ? "EIN" : "AUS");
  Serial.printf_P(PSTR(" Aktualisierung: %ds (+ = +5s, - = -5s)\r\n"), list_refresh_sec);
  // NEU 2.26.x: gleiches Flag wie Menue 3a Variante 1 (show_vendors_in_menu3a) -
  // eine gemeinsame Session-Einstellung fuer beide Varianten, kein eigenes
  // Flag noetig.
  Serial.printf_P(PSTR(" Hersteller anzeigen: %s (v=toggle)\r\n"), show_vendors_in_menu3a ? "EIN" : "AUS");
  // NEU 2.30.49: Auftrag 2 - jetzt auch in Modus 2 verfuegbar.
  Serial.println(F(" b = Hintergrundverkehr-Statistik dieses SSID-Buendels starten"));
  Serial.println(F("-------------------------------------------------------"));
  
  // NEU 2.26.x: Bei Vendor-Anzeige immer einspaltig (analog Variante 1)
  bool two_col = false;
  if (!show_vendors_in_menu3a) {
    two_col = (two_col_threshold_devices > 0 && match_count > two_col_threshold_devices);
  }
  
  if (show_vendors_in_menu3a) {
    Serial.println(F(" MAC          AP  Age  db      Hersteller"));
    Serial.println(F("-------------------------------------------------------"));
  } else if (two_col) {
    Serial.println(F(" MAC          AP  Age  db      MAC          AP  Age  db"));
    Serial.println(F("----------------------------------------------------------"));
  } else {
    Serial.println(F(" MAC          AP  Age  db"));
    Serial.println(F("-------------------------------------------------------"));
  }
  
  int half = two_col ? (match_count + 1) / 2 : match_count;
  for (int i = 0; i < half; i++) {
    Serial.print(F(" "));
    print_client_cell_ap_mode(matches[i], ap_matches, ap_match_count, now);
    if (show_vendors_in_menu3a) {
      // NEU 2.26.x: On-Demand Vendor-Lookup ueber den Cache (analog Var.1)
      Serial.print(F(" "));
      String vendor = vendorCache_lookup_or_search(clients_known[matches[i]].station);
      Serial.print(vendor.c_str());
    } else if (two_col) {
      int right_i = half + i;
      if (right_i < match_count) {
        Serial.print(F(" "));
        print_client_cell_ap_mode(matches[right_i], ap_matches, ap_match_count, now);
      }
    }
    Serial.println();
    yield();
  }
  if (match_count == 0) {
    Serial.println(F(" (keine Geraete zu dieser SSID gefunden)"));
  }

  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Backspace = zurueck zur SSID-Auswahl, ESC = Menue."));
  last_list_refresh_time = millis() / 1000;
  free(matches);     // NEU 2.30.10: siehe Kommentar bei den malloc()-Stellen oben
  free(ap_matches);
  
  // BUGFIX 2.26.3: vendorCache_end() hier ENTFERNT (siehe Begruendung in
  // menu_enter_ssid_list()) - Freigabe erfolgt an den echten Austrittspunkten.
}

// Zeichnet Punkt 3b neu, unabhaengig davon ob gerade ein einzelner AP
// oder die kombinierte SSID-Ansicht aktiv ist. Wird von allen Stellen
// verwendet, die die Liste nur aktualisieren (Sortierung, Auto-Refresh,
// Threshold-Aenderung, u/d), damit beide Modi darueber funktionieren.
void redraw_ssid_list()
{
  // NEU 2.12.0: Unterscheide zwischen 3 Modi
  if (current_list_mode == 1) {
    // Modus 1: einzelner AP
    menu_enter_ssid_list(current_list_ap_index);
  } else if (current_list_mode == 2) {
    // Modus 2: SSID-Bündelung (alle APs mit gleicher SSID)
    menu_enter_ssid_list_combined(current_list_ap_index);
  } else if (current_list_mode == 3) {
    // Modus 3: Multi-AP (selected_ap_indices[] ist noch gültig)
    menu_enter_ssid_list_multi();
  }
  // Fallback für unbekannte Modi (sollte nicht vorkommen)
}

// =====================================================================
// Punkt 4: MAC-Adress-Watchlist
// =====================================================================
// Frei gewaehlte MAC-Adressen mit Beschreibung, unabhaengig von einem
// bestimmten Access Point. Zeigt fuer jeden Eintrag die aktuellsten
// bekannten Geraetedaten im selben Zeilenformat wie die Geraeteliste
// (Punkt 3, print_client_cell/format_client_cell) an.

#define WATCHLIST_FILE "/watchlist.cfg"

void save_watchlist()
{
  File f = LittleFS.open(WATCHLIST_FILE, "w");
  if (!f) {
    Serial.println(F(" Fehler beim Speichern der Watchlist."));
    return;
  }
  for (int i = 0; i < watchlist_count; i++) {
    char macstr[13];
    for (int b = 0; b < 6; b++) sprintf_P(macstr + b * 2, PSTR("%02x"), watchlist[i].mac[b]);
    macstr[12] = '\0';
    f.printf_P(PSTR("%s=%s\r\n"), macstr, watchlist[i].desc);
  }
  f.close();
}

// Wird beim Boot aufgerufen. Existiert die Datei noch nicht, bleibt die
// Watchlist einfach leer.
void load_watchlist()
{
  watchlist_count = 0;
  if (!LittleFS.exists(WATCHLIST_FILE)) return;
  File f = LittleFS.open(WATCHLIST_FILE, "r");
  if (!f) return;
  while (f.available() && watchlist_count < MAX_WATCHLIST) {
    String line = f.readStringUntil('\n');
    line.trim();
    if (line.length() < 13) continue;   // mind. 12 Hex-Zeichen + "="
    if (line.charAt(12) != '=') continue;
    String mac_str = line.substring(0, 12);
    String desc = line.substring(13);
    parse_mac_hex(mac_str.c_str(), watchlist[watchlist_count].mac);
    desc.toCharArray(watchlist[watchlist_count].desc, 33);
    watchlist_count++;
  }
  f.close();
}

// Fuegt eine neue MAC+Beschreibung hinzu, oder aktualisiert die
// Beschreibung, falls die MAC bereits auf der Watchlist steht.
void add_or_update_watchlist_entry(uint8_t* mac, const char* desc)
{
  int idx = -1;
  for (int i = 0; i < watchlist_count; i++) {
    if (! memcmp(watchlist[i].mac, mac, ETH_MAC_LEN)) { idx = i; break; }
  }
  if (idx < 0) {
    if (watchlist_count >= MAX_WATCHLIST) {
      Serial.println(F(" Watchlist voll (max. 32 Eintraege) - nicht hinzugefuegt."));
      return;
    }
    idx = watchlist_count;
    memcpy(watchlist[idx].mac, mac, ETH_MAC_LEN);
    watchlist_count++;
  }
  strncpy(watchlist[idx].desc, desc, 32);
  watchlist[idx].desc[32] = '\0';
}

// NEU 2.30.11: prueft, ob ein Watchlist-Eintrag gerade als Mausefalle
// scharf ist (FRAMETRAP_CLIENT_MARKER in der Beschreibung enthalten).

// NEU 2.30.67: Erzeugt den LittleFS-Dateinamen
// /TW_<MAC 12 hex><Beschreibung max. 10>.txt
void timewatch_build_filename(const uint8_t *mac, const char *desc, char *out, size_t outlen)
{
  char macstr[13];
  for (int i = 0; i < 6; i++) sprintf_P(macstr + i * 2, PSTR("%02x"), mac[i]);
  macstr[12] = '\0';

  char clean[33];
  strncpy(clean, desc, 32);
  clean[32] = '\0';

  const char *markers[] = {
    TIMEWATCH_MARKER,
    FRAMETRAP_CLIENT_MARKER,
    FRAMETRAP_BEACON_MARKER,
    NULL
  };
  for (int m = 0; markers[m] != NULL; m++) {
    char *pos = strstr(clean, markers[m]);
    if (pos != NULL) *pos = '\0';
  }

  int len = strlen(clean);
  while (len > 0 && clean[len - 1] == ' ') clean[--len] = '\0';

  char shortdesc[11];
  int sn = 0;
  for (int i = 0; clean[i] != '\0' && sn < 10; i++) {
    char ch = clean[i];
    if (isalnum((unsigned char)ch) || ch == '_' || ch == '-') shortdesc[sn++] = ch;
  }
  shortdesc[sn] = '\0';
  snprintf_P(out, outlen, PSTR("/TW_%s%s.txt"), macstr, shortdesc);
}

void timewatch_build_timestamp(char *out, size_t outlen)
{
  if (ntp_synced) {
    time_t tz = current_unix_time_with_tz();
    struct tm *ti = localtime(&tz);
    snprintf_P(out, outlen, PSTR("%04d-%02d-%02d %02d:%02d:%02d"),
               ti->tm_year + 1900, ti->tm_mon + 1, ti->tm_mday,
               ti->tm_hour, ti->tm_min, ti->tm_sec);
  } else {
    uint32_t total_sec = millis() / 1000UL;
    uint32_t days = total_sec / 86400UL;
    uint32_t h = (total_sec % 86400UL) / 3600UL;
    uint32_t m = (total_sec % 3600UL) / 60UL;
    uint32_t s = total_sec % 60UL;
    snprintf_P(out, outlen, PSTR("boot+%lud %02lu:%02lu:%02lu"),
               (unsigned long)days, (unsigned long)h,
               (unsigned long)m, (unsigned long)s);
  }
}

int timewatch_get_state_slot(uint8_t *mac)
{
  int free_slot = -1;
  for (int i = 0; i < MAX_WATCHLIST; i++) {
    bool is_empty = true;
    for (int b = 0; b < 6; b++) {
      if (timewatch_state[i].mac[b] != 0) {
        is_empty = false;
        break;
      }
    }
    if (is_empty) {
      if (free_slot < 0) free_slot = i;
      continue;
    }
    if (memcmp(timewatch_state[i].mac, mac, 6) == 0) return i;
  }
  if (free_slot < 0) return -1;
  memcpy(timewatch_state[free_slot].mac, mac, 6);
  timewatch_state[free_slot].prev_state = 0;
  timewatch_state[free_slot].last_log_time = 0;
  return free_slot;
}

void timewatch_append_timestamp(uint8_t *mac, const char *desc)
{
  char path[33];
  timewatch_build_filename(mac, desc, path, sizeof(path));
  bool file_exists = LittleFS.exists(path);
  File f = LittleFS.open(path, file_exists ? "a" : "w");
  if (!f) {
    Serial.printf_P(PSTR(" TimeWatch: Datei %s nicht beschreibbar.\r\n"), path);
    return;
  }

  if (!file_exists) {
    f.println(F("======================================================="));
    f.println(F(" TimeWatch-Protokoll"));
    f.println(F("======================================================="));
    write_generated_file_header(f);
    f.print(F(" MAC: "));
    for (int i = 0; i < 6; i++) f.printf_P(PSTR("%02x"), mac[i]);
    f.println();

    char clean[33];
    strncpy(clean, desc, 32);
    clean[32] = '\0';
    const char *markers[] = {
      TIMEWATCH_MARKER,
      FRAMETRAP_CLIENT_MARKER,
      FRAMETRAP_BEACON_MARKER,
      NULL
    };
    for (int m = 0; markers[m] != NULL; m++) {
      char *pos = strstr(clean, markers[m]);
      if (pos != NULL) *pos = '\0';
    }
    f.printf_P(PSTR(" Beschreibung: %s\r\n"), clean);
    f.println(F("-------------------------------------------------------"));
  }

  char ts[32];
  timewatch_build_timestamp(ts, sizeof(ts));
  f.printf_P(PSTR("%s\r\n"), ts);
  f.close();
}

void timewatch_check_and_log(uint8_t *mac, uint32_t age, uint64_t now)
{
  int slot = timewatch_get_state_slot(mac);
  if (slot < 0) return;

  bool currently_out = (age > 3600UL);
  uint8_t prev = timewatch_state[slot].prev_state;

  if (currently_out) {
    timewatch_state[slot].prev_state = 2;
    return;
  }

  if (prev == 2 && (uint32_t)now - timewatch_state[slot].last_log_time >= 60UL) {
    const char *desc = "";
    for (int i = 0; i < watchlist_count; i++) {
      if (memcmp(watchlist[i].mac, mac, 6) == 0) {
        desc = watchlist[i].desc;
        break;
      }
    }
    timewatch_append_timestamp(mac, desc);
    timewatch_state[slot].last_log_time = (uint32_t)now;
    Serial.print(F(" TimeWatch: "));
    for (int b = 0; b < 6; b++) Serial.printf_P(PSTR("%02x"), mac[b]);
    Serial.println(F(" protokolliert."));
  }
  timewatch_state[slot].prev_state = 1;
}


bool watchlist_entry_is_trapped(int idx)
{
  if (idx < 0 || idx >= watchlist_count) return false;
  return strstr(watchlist[idx].desc, FRAMETRAP_CLIENT_MARKER) != NULL;
}

// NEU 2.30.11: Anzahl der gerade scharfen Fallen (fuer die Obergrenze
// FRAMETRAP_CLIENT_MAX_PENDING beim scharf machen).
int frametrap_client_armed_count()
{
  int n = 0;
  for (int i = 0; i < watchlist_count; i++) {
    if (watchlist_entry_is_trapped(i)) n++;
  }
  return n;
}

// NEU 2.30.11: reine Loeschen-Grundoperation (Array-Shift) - OHNE
// save_watchlist()/Ausgabe, damit sowohl der manuelle Loeschen-Dialog
// (Menue 4) als auch frametrap_client_disarm_or_remove() dieselbe Logik nutzen
// koennen, aber jeweils selbst entscheiden, was danach ausgegeben/
// gespeichert wird.
void remove_watchlist_entry(int idx)
{
  if (idx < 0 || idx >= watchlist_count) return;
  for (int j = idx; j < watchlist_count - 1; j++) watchlist[j] = watchlist[j + 1];
  watchlist_count--;
}

// NEU 2.30.11: macht eine Falle scharf (Menue 3a, "wp"+Zahl+Enter). Steht
// die MAC schon auf der Watchlist (z.B. zur Rueckkehr-Ueberwachung), wird
// der Marker an die bestehende Beschreibung angehaengt (bei Platzmangel
// wird die bestehende Beschreibung gekuerzt, der Marker geht nie verloren)
// - der urspruengliche Zweck des Eintrags bleibt so erhalten. Gibt false
// zurueck, wenn die Obergrenze erreicht ist oder die Watchlist voll ist.
bool frametrap_client_arm(uint8_t *mac)
{
  if (frametrap_client_armed_count() >= FRAMETRAP_CLIENT_MAX_PENDING) {
    Serial.printf_P(PSTR(" Maximal %d gleichzeitige FrameTraps erreicht - erst eine loesen.\r\n"), FRAMETRAP_CLIENT_MAX_PENDING);
    return false;
  }
  int idx = -1;
  for (int i = 0; i < watchlist_count; i++) {
    if (! memcmp(watchlist[i].mac, mac, ETH_MAC_LEN)) { idx = i; break; }
  }
  if (idx < 0) {
    if (watchlist_count >= MAX_WATCHLIST) {
      Serial.println(F(" Watchlist voll (max. 32 Eintraege) - Falle nicht scharf gemacht."));
      return false;
    }
    idx = watchlist_count;
    memcpy(watchlist[idx].mac, mac, ETH_MAC_LEN);
    watchlist[idx].desc[0] = '\0';
    watchlist_count++;
  }
  if (watchlist_entry_is_trapped(idx)) {
    Serial.println(F(" Diese MAC ist bereits ein scharfer FrameTrap."));
    return false;
  }
  // Bestehenden Text noetigenfalls kuerzen, damit der Marker sicher passt
  // (desc[33] = 32 nutzbare Zeichen + Nullterminator).
  int existing_len = strlen(watchlist[idx].desc);
  int marker_len = strlen(FRAMETRAP_CLIENT_MARKER);
  int max_existing = 32 - marker_len;
  if (max_existing < 0) max_existing = 0;
  if (existing_len > max_existing) watchlist[idx].desc[max_existing] = '\0';
  strncat(watchlist[idx].desc, FRAMETRAP_CLIENT_MARKER, 32 - strlen(watchlist[idx].desc));
  watchlist[idx].desc[32] = '\0';
  save_watchlist();
  return true;
}

// NEU 2.30.11: Gegenstueck zu frametrap_client_arm() - wird aufgerufen, sobald
// ein Probe Request eingefangen und verarbeitet wurde. Entfernt NUR den
// Marker (Variante B, siehe Absprache) - bestand vorher schon ein anderer
// Beschreibungstext (z.B. fuer die Rueckkehr-Ueberwachung), bleibt der
// Eintrag mit diesem Text erhalten; war der Eintrag nur fuer die Falle
// angelegt (Beschreibung wird durchs Entfernen leer), wird er komplett
// geloescht.
void frametrap_client_disarm_or_remove(uint8_t *mac)
{
  int idx = -1;
  for (int i = 0; i < watchlist_count; i++) {
    if (! memcmp(watchlist[i].mac, mac, ETH_MAC_LEN)) { idx = i; break; }
  }
  if (idx < 0) return;
  char *pos = strstr(watchlist[idx].desc, FRAMETRAP_CLIENT_MARKER);
  if (pos != NULL) {
    *pos = '\0';  // Rest (falls der Marker mittendrin stand) wird bewusst gekappt -
                   // FRAMETRAP_CLIENT_MARKER wird beim Anhaengen immer ans Ende gesetzt.
  }
  if (strlen(watchlist[idx].desc) == 0) {
    remove_watchlist_entry(idx);
  }
  save_watchlist();
}

// NEU 2.30.11: verarbeitet einen fertigen Mausefallen-Fang (aufgerufen aus
// menu_periodic() im Hauptloop, NIE aus promisc_cb()) - dekodiert den
// Probe-Request-Rohframe und schreibt ihn in eine eigene Datei statt auf
// die Konsole. Dieselbe IE-Dekodierung wie display_client_frame_analysis(),
// aber auf ein File& statt Serial gerichtet, und ohne den generischen
// Datenframe-Zweig (eine Mausefalle faengt ausschliesslich Probe Requests).
void frametrap_client_process_catch(int slot)
{
  uint8_t *f_ = frametrap_client_catches[slot].buf;
  uint16_t real_len = frametrap_client_catches[slot].reallen;
  uint16_t usable_len = (real_len > 0 && real_len < 112) ? real_len : 112;
  uint8_t *mac = frametrap_client_catches[slot].station;

  // SSID des zugehoerigen APs ermitteln (fuer Dateiname + Header) - ueber
  // den aktuellen clients_known-Eintrag dieser MAC, falls noch vorhanden.
  char ssid_full[33] = "";
  for (int c = 0; c < clients_known_count; c++) {
    if (memcmp(clients_known[c].station, mac, ETH_MAC_LEN) != 0) continue;
    uint8_t ap_idx = clients_known[c].ap_idx;
    if (ap_idx < aps_known_count && !ap_slot_free(ap_idx)) {
      strncpy(ssid_full, (const char*)aps_known[ap_idx].ssid, 32);
      ssid_full[32] = '\0';
    }
    break;
  }

  // Dateiname: "/PR_" + 12 Hex-Zeichen MAC + "_" + SSID(gekuerzt) + ".txt".
  // LittleFS erlaubt hier max. 32 Byte fuer den KOMPLETTEN Pfad (inkl. "/",
  // ".txt" und Nullterminator, siehe Kommentar bei auto_save_on_overflow) -
  // das laesst genau 10 Zeichen fuer die SSID. Gefiltert auf alnum/_/-,
  // wie beim bestehenden Speichern-Dateinamensfilter.
  char macstr[13];
  for (int b = 0; b < 6; b++) sprintf_P(macstr + b * 2, PSTR("%02x"), mac[b]);
  macstr[12] = '\0';
  char ssid_short[11];
  int sn = 0;
  for (int i = 0; ssid_full[i] != '\0' && sn < 10; i++) {
    char ch = ssid_full[i];
    if (isalnum((unsigned char)ch) || ch == '_' || ch == '-') {
      ssid_short[sn++] = ch;
    }
  }
  ssid_short[sn] = '\0';
  if (sn == 0) { strcpy(ssid_short, "unbekannt"); ssid_short[10] = '\0'; }
  char path[40];
  snprintf_P(path, sizeof(path), PSTR("/PR_%s_%s.txt"), macstr, ssid_short);
  if (!make_collision_safe_path(path,path,sizeof(path))) return;

  File file = LittleFS.open(path, "w");
  if (!file) {
    Serial.printf_P(PSTR(" FrameTrap: Datei %s konnte nicht angelegt werden.\r\n"), path);
  } else {
    file.println(F("======================================================="));
    file.println(F(" FrameTrap - eingefangener Probe Request"));
    file.println(F("======================================================="));
    file.print(F(" Client: ")); print_mac(mac, NULL, &file); file.println();
    file.printf_P(PSTR(" SSID des zugehoerigen APs: %s\r\n"), sn > 0 ? ssid_full : "(unbekannt)");
    if (ntp_synced) {
      time_t tz_now = current_unix_time_with_tz();
      struct tm* timeinfo = localtime(&tz_now);
      file.printf_P(PSTR(" Zeitstempel: %04d-%02d-%02d %02d:%02d:%02d | Programmversion: v%s\r\n"),
        timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
        timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, FIRMWARE_VERSION);
    } else {
      file.printf_P(PSTR(" Zeitstempel: nicht verfuegbar (kein NTP) | Programmversion: v%s\r\n"), FIRMWARE_VERSION);
    }
    file.printf_P(PSTR(" Signalstaerke bei Empfang: %d dBm\r\n"), frametrap_client_catches[slot].rssi);
    if (real_len > 112) {
      file.printf_P(PSTR(" Frame ist laut Funkmodul %u Byte lang, nur die ersten 112 Byte\r\n"), real_len);
      file.println(F(" wurden erfasst (Hardware-/SDK-Grenze)."));
    }
    file.println();

    // ---------- MAC-Header ----------
    file.println(F("--- MAC-Header (IEEE 802.11) ---"));
    uint16_t fc = f_[0] | (f_[1] << 8);
    file.printf_P(PSTR(" Byte  0- 1  Frame Control       : 0x%04X (Probe Request)\r\n"), fc);
    file.printf_P(PSTR("   Flags             : ToDS=%d FromDS=%d MoreFrag=%d Retry=%d PwrMgt=%d MoreData=%d Protected=%d Order=%d\r\n"),
                  (f_[1] >> 0) & 1, (f_[1] >> 1) & 1, (f_[1] >> 2) & 1, (f_[1] >> 3) & 1,
                  (f_[1] >> 4) & 1, (f_[1] >> 5) & 1, (f_[1] >> 6) & 1, (f_[1] >> 7) & 1);
    uint16_t duration = f_[2] | (f_[3] << 8);
    file.printf_P(PSTR(" Byte  2- 3  Duration/ID         : %u\r\n"), duration);
    file.print(F(" Byte  4- 9  Adresse 1 (DA)      : ")); print_mac(f_ + 4, NULL, &file); file.println();
    file.print(F(" Byte 10-15  Adresse 2 (SA)      : ")); print_mac(f_ + 10, NULL, &file);
    {
      String vendor = vendorCache_lookup_or_search(f_ + 10);
      file.printf_P(PSTR("  Hersteller: %s\r\n"), vendor.c_str());
    }
    file.print(F(" Byte 16-21  Adresse 3 (BSSID)   : ")); print_mac(f_ + 16, NULL, &file); file.println();
    uint16_t seqctl = f_[22] | (f_[23] << 8);
    file.printf_P(PSTR(" Byte 22-23  Sequence Control    : Fragment=%u Sequenznummer=%u\r\n"), seqctl & 0x0F, seqctl >> 4);
    file.println();

    // ---------- Information Elements ----------
    file.println(F("--- Information Elements ---"));
    int pos = 24;
    int ie_count = 0;
    while (pos + 2 <= usable_len) {
      uint8_t id = f_[pos];
      uint8_t ie_len = f_[pos + 1];
      int data_start = pos + 2;
      int available = usable_len - data_start;
      int shown_len = (ie_len <= available) ? ie_len : available;

      file.printf_P(PSTR(" ID %3d (%-28s) Laenge %3d: "), id, ie_element_name(id), ie_len);
      switch (id) {
        case 0: {
          char ssidbuf[33];
          int n = shown_len > 32 ? 32 : shown_len;
          memcpy(ssidbuf, f_ + data_start, n);
          ssidbuf[n] = '\0';
          if (n == 0) file.print(F("(leer/Broadcast-Probe)"));
          else file.printf_P(PSTR("\"%s\""), ssidbuf);
          break;
        }
        case 1: case 50: {
          for (int i = 0; i < shown_len; i++) {
            uint8_t v = f_[data_start + i];
            bool basic = (v & 0x80) != 0;
            int whole = (v & 0x7F) / 2;
            int frac = ((v & 0x7F) % 2) * 5;
            file.printf_P(PSTR("%s%d.%d%s"), i > 0 ? ", " : "", whole, frac, basic ? "*" : "");
          }
          if (shown_len > 0) file.print(F(" Mbps (* = Basisrate)"));
          break;
        }
        case 3:
          if (shown_len >= 1) file.printf_P(PSTR("Kanal %d"), f_[data_start]);
          break;
        case 221:
          if (shown_len >= 4) {
            uint8_t oui_as_mac[6] = { f_[data_start], f_[data_start + 1], f_[data_start + 2], 0, 0, 0 };
            String vendor = vendorCache_lookup_or_search(oui_as_mac);
            file.printf_P(PSTR("OUI %02x:%02x:%02x (%s), Typ %d"),
                          f_[data_start], f_[data_start + 1], f_[data_start + 2],
                          vendor.c_str(), f_[data_start + 3]);
          }
          break;
        default:
          break;
      }
      file.println();
      pos = data_start + ie_len;
      ie_count++;
      yield();
    }
    if (ie_count == 0) {
      file.println(F(" (keine Information Elements im erfassten Bereich)"));
    }
    file.println(F("-------------------------------------------------------"));
    file.close();
  }

  frametrap_client_disarm_or_remove(mac);
  free(frametrap_client_catches[slot].buf);
  frametrap_client_catches[slot].buf = NULL;
}

// NEU 2.30.46: prueft, ob ein Watchlist-Eintrag gerade als Beacon-FrameTrap
// scharf ist (FRAMETRAP_BEACON_MARKER in der Beschreibung enthalten) -
// Pendant zu watchlist_entry_is_trapped() (dort: Client-FrameTrap).
bool watchlist_entry_is_beacon_trapped(int idx)
{
  if (idx < 0 || idx >= watchlist_count) return false;
  return strstr(watchlist[idx].desc, FRAMETRAP_BEACON_MARKER) != NULL;
}

// NEU 2.30.46: Beacon-FrameTrap jetzt ueber die Watchlist verwaltet (wie der
// Client-FrameTrap) - erscheint dadurch markiert in Menue 4 und uebersteht
// einen Neustart.
int frametrap_beacon_armed_count()
{
  int n = 0;
  for (int i = 0; i < watchlist_count; i++) {
    if (watchlist_entry_is_beacon_trapped(i)) n++;
  }
  return n;
}

bool frametrap_beacon_is_armed(uint8_t *bssid)
{
  for (int i = 0; i < watchlist_count; i++) {
    if (! memcmp(watchlist[i].mac, bssid, ETH_MAC_LEN) && watchlist_entry_is_beacon_trapped(i)) return true;
  }
  return false;
}

// NEU 2.30.46: macht einen Beacon-FrameTrap scharf (Menue 3, "wt"+Zahl+Enter).
// Gleiches Vorgehen wie frametrap_client_arm(): steht die BSSID schon auf
// der Watchlist, wird der Marker an die bestehende Beschreibung angehaengt
// (Text wird bei Platzmangel gekuerzt, der Marker geht nie verloren).
bool frametrap_beacon_arm(uint8_t *bssid)
{
  if (frametrap_beacon_is_armed(bssid)) {
    Serial.println(F(" Diese BSSID ist bereits ein scharfer FrameTrap."));
    return false;
  }
  if (frametrap_beacon_armed_count() >= FRAMETRAP_BEACON_MAX_PENDING) {
    Serial.printf_P(PSTR(" Maximal %d gleichzeitige FrameTraps erreicht - erst einen loesen.\r\n"), FRAMETRAP_BEACON_MAX_PENDING);
    return false;
  }
  int idx = -1;
  for (int i = 0; i < watchlist_count; i++) {
    if (! memcmp(watchlist[i].mac, bssid, ETH_MAC_LEN)) { idx = i; break; }
  }
  if (idx < 0) {
    if (watchlist_count >= MAX_WATCHLIST) {
      Serial.println(F(" Watchlist voll (max. 32 Eintraege) - FrameTrap nicht scharf gemacht."));
      return false;
    }
    idx = watchlist_count;
    memcpy(watchlist[idx].mac, bssid, ETH_MAC_LEN);
    watchlist[idx].desc[0] = '\0';
    watchlist_count++;
  }
  int existing_len = strlen(watchlist[idx].desc);
  int marker_len = strlen(FRAMETRAP_BEACON_MARKER);
  int max_existing = 32 - marker_len;
  if (max_existing < 0) max_existing = 0;
  if (existing_len > max_existing) watchlist[idx].desc[max_existing] = '\0';
  strncat(watchlist[idx].desc, FRAMETRAP_BEACON_MARKER, 32 - strlen(watchlist[idx].desc));
  watchlist[idx].desc[32] = '\0';
  save_watchlist();
  return true;
}

// NEU 2.30.46: Gegenstueck zu frametrap_beacon_arm() - wird aufgerufen,
// sobald ein Beacon eingefangen und verarbeitet wurde (oder manuell zum
// Entschaerfen). Entfernt NUR den Marker (wie bei frametrap_client_disarm_
// or_remove()) - bestand vorher schon ein anderer Beschreibungstext, bleibt
// der Eintrag erhalten; war er nur fuer den FrameTrap angelegt, wird er
// komplett geloescht.
void frametrap_beacon_disarm(uint8_t *bssid)
{
  int idx = -1;
  for (int i = 0; i < watchlist_count; i++) {
    if (! memcmp(watchlist[i].mac, bssid, ETH_MAC_LEN)) { idx = i; break; }
  }
  if (idx < 0) return;
  char *pos = strstr(watchlist[idx].desc, FRAMETRAP_BEACON_MARKER);
  if (pos != NULL) {
    *pos = '\0';
  }
  if (strlen(watchlist[idx].desc) == 0) {
    remove_watchlist_entry(idx);
  }
  save_watchlist();
}

// NEU 2.30.45: verarbeitet einen fertigen Beacon-FrameTrap-Fang (aufgerufen
// aus menu_periodic() im Hauptloop, NIE aus promisc_cb()) - dekodiert den
// Beacon-Rohframe und schreibt ihn in eine eigene Datei, nach demselben
// Aufbau/Syntax wie frametrap_client_process_catch() oben (dort: Probe
// Request). Deckt bewusst denselben IE-Teilumfang ab wie dort (SSID/Rates/
// Kanal/Vendor) statt der vollen Serial-Anzeige aus display_beacon_frame_
// analysis() (dort zusaetzlich RSN-Decoder + Rohbyte-Dump je IE).
void frametrap_beacon_process_catch(int slot)
{
  uint8_t *f_ = frametrap_beacon_catches[slot].buf;
  uint16_t real_len = frametrap_beacon_catches[slot].reallen;
  uint16_t usable_len = (real_len > 0 && real_len < 112) ? real_len : 112;
  uint8_t *bssid = frametrap_beacon_catches[slot].bssid;

  // SSID ueber den aktuellen aps_known-Eintrag dieser BSSID, falls noch vorhanden.
  char ssid_full[33] = "";
  int found_ap = find_ap_index_by_bssid(bssid);
  if (found_ap >= 0) {
    strncpy(ssid_full, (const char*)aps_known[found_ap].ssid, 32);
    ssid_full[32] = '\0';
  }

  // Dateiname: "/BC_" + 12 Hex-Zeichen BSSID + "_" + SSID(gekuerzt) + ".txt".
  // Gleicher Aufbau/Laengenlimit wie beim Client-FrameTrap (siehe dort).
  char macstr[13];
  for (int b = 0; b < 6; b++) sprintf_P(macstr + b * 2, PSTR("%02x"), bssid[b]);
  macstr[12] = '\0';
  char ssid_short[11];
  int sn = 0;
  for (int i = 0; ssid_full[i] != '\0' && sn < 10; i++) {
    char ch = ssid_full[i];
    if (isalnum((unsigned char)ch) || ch == '_' || ch == '-') {
      ssid_short[sn++] = ch;
    }
  }
  ssid_short[sn] = '\0';
  if (sn == 0) { strcpy(ssid_short, "unbekannt"); ssid_short[10] = '\0'; }
  char path[40];
  snprintf_P(path, sizeof(path), PSTR("/BC_%s_%s.txt"), macstr, ssid_short);
  if (!make_collision_safe_path(path,path,sizeof(path))) return;

  File file = LittleFS.open(path, "w");
  if (!file) {
    Serial.printf_P(PSTR(" FrameTrap: Datei %s konnte nicht angelegt werden.\r\n"), path);
  } else {
    file.println(F("======================================================="));
    file.println(F(" FrameTrap - eingefangener Beacon"));
    file.println(F("======================================================="));
    file.print(F(" BSSID: ")); print_mac(bssid, NULL, &file); file.println();
    file.printf_P(PSTR(" SSID: %s\r\n"), sn > 0 ? ssid_full : "(unbekannt/versteckt)");
    if (ntp_synced) {
      time_t tz_now = current_unix_time_with_tz();
      struct tm* timeinfo = localtime(&tz_now);
      file.printf_P(PSTR(" Zeitstempel: %04d-%02d-%02d %02d:%02d:%02d | Programmversion: v%s\r\n"),
        timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
        timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, FIRMWARE_VERSION);
    } else {
      file.printf_P(PSTR(" Zeitstempel: nicht verfuegbar (kein NTP) | Programmversion: v%s\r\n"), FIRMWARE_VERSION);
    }
    file.printf_P(PSTR(" Signalstaerke bei Empfang: %d dBm\r\n"), frametrap_beacon_catches[slot].rssi);
    if (real_len > 112) {
      file.printf_P(PSTR(" Frame ist laut Funkmodul %u Byte lang, nur die ersten 112 Byte\r\n"), real_len);
      file.println(F(" wurden erfasst (Hardware-/SDK-Grenze)."));
    }
    file.println();

    // ---------- MAC-Header ----------
    file.println(F("--- MAC-Header (IEEE 802.11) ---"));
    uint16_t fc = f_[0] | (f_[1] << 8);
    file.printf_P(PSTR(" Byte  0- 1  Frame Control       : 0x%04X (Beacon)\r\n"), fc);
    file.printf_P(PSTR("   Flags             : ToDS=%d FromDS=%d MoreFrag=%d Retry=%d PwrMgt=%d MoreData=%d Protected=%d Order=%d\r\n"),
                  (f_[1] >> 0) & 1, (f_[1] >> 1) & 1, (f_[1] >> 2) & 1, (f_[1] >> 3) & 1,
                  (f_[1] >> 4) & 1, (f_[1] >> 5) & 1, (f_[1] >> 6) & 1, (f_[1] >> 7) & 1);
    uint16_t duration = f_[2] | (f_[3] << 8);
    file.printf_P(PSTR(" Byte  2- 3  Duration/ID         : %u\r\n"), duration);
    file.print(F(" Byte  4- 9  Adresse 1 (DA)      : ")); print_mac(f_ + 4, NULL, &file); file.println();
    file.print(F(" Byte 10-15  Adresse 2 (SA/BSSID): ")); print_mac(f_ + 10, NULL, &file);
    {
      String vendor = vendorCache_lookup_or_search(f_ + 10);
      file.printf_P(PSTR("  Hersteller: %s\r\n"), vendor.c_str());
    }
    file.print(F(" Byte 16-21  Adresse 3 (BSSID)   : ")); print_mac(f_ + 16, NULL, &file); file.println();
    uint16_t seqctl = f_[22] | (f_[23] << 8);
    file.printf_P(PSTR(" Byte 22-23  Sequence Control    : Fragment=%u Sequenznummer=%u\r\n"), seqctl & 0x0F, seqctl >> 4);
    file.println();

    // ---------- Feste Beacon-Felder (Timestamp/Beacon-Intervall/Capability) ----------
    file.println(F("--- Feste Beacon-Felder ---"));
    // BUGFIX 2.30.46 (Anwenderfehlerbericht): Byte 24-31 (Timestamp/TSF)
    // fehlte hier bisher komplett - Uebernahme derselben Logik/Darstellung
    // wie in display_beacon_frame_analysis() (Live-Anzeige, Menue 3 "w"+Zahl).
    {
      uint32_t ts_low = 0, ts_high = 0;
      for (int i = 3; i >= 0; i--) ts_low = (ts_low << 8) | f_[24 + i];
      for (int i = 3; i >= 0; i--) ts_high = (ts_high << 8) | f_[28 + i];
      uint64_t tsf = ((uint64_t) ts_high << 32) | (uint64_t) ts_low;
      char tsf_buf[21], days_buf[21];
      format_uint64_dec(tsf, tsf_buf, sizeof(tsf_buf));

      uint64_t total_seconds = tsf / 1000000ULL;
      uint32_t rem_us = (uint32_t)(tsf % 1000000ULL);
      uint32_t ms = rem_us / 1000UL;
      uint64_t days = total_seconds / 86400ULL;
      uint32_t rem_sec = (uint32_t)(total_seconds % 86400ULL);
      uint32_t hh = rem_sec / 3600UL;
      uint32_t mm = (rem_sec % 3600UL) / 60UL;
      uint32_t ss = rem_sec % 60UL;
      format_uint64_dec(days, days_buf, sizeof(days_buf));

      file.printf_P(PSTR(" Byte 24-31  Timestamp/TSF       : %s \xc2\xb5s\r\n"), tsf_buf);
      file.printf_P(PSTR("                                   ca. %s Tage %02lu:%02lu:%02lu.%03lu\r\n"),
                    days_buf, (unsigned long) hh, (unsigned long) mm, (unsigned long) ss, (unsigned long) ms);
    }
    uint16_t beacon_interval = f_[32] | (f_[33] << 8);
    uint32_t interval_us = (uint32_t) beacon_interval * 1024UL;
    file.printf_P(PSTR(" Byte 32-33  Beacon-Intervall    : %u TU (= %lu.%03lu ms)\r\n"),
                  beacon_interval, (unsigned long)(interval_us / 1000), (unsigned long)(interval_us % 1000));
    uint16_t capa = f_[34] | (f_[35] << 8);
    file.printf_P(PSTR(" Byte 34-35  Capability Info     : 0x%04X\r\n"), capa);
    file.printf_P(PSTR("   ESS=%d IBSS=%d Privacy=%d ShortPreamble=%d ShortSlotTime=%d\r\n"),
                  (capa >> 0) & 1, (capa >> 1) & 1, (capa >> 4) & 1, (capa >> 5) & 1, (capa >> 10) & 1);
    file.println();

    // ---------- Information Elements (gleicher Teilumfang wie Client-FrameTrap) ----------
    file.println(F("--- Information Elements ---"));
    int pos = 36;  // bei Beacons beginnen die IEs nach den festen Feldern (Byte 36), nicht bei 24 wie bei Probe Requests
    int ie_count = 0;
    while (pos + 2 <= usable_len) {
      uint8_t id = f_[pos];
      uint8_t ie_len = f_[pos + 1];
      int data_start = pos + 2;
      int available = usable_len - data_start;
      int shown_len = (ie_len <= available) ? ie_len : available;

      file.printf_P(PSTR(" ID %3d (%-28s) Laenge %3d: "), id, ie_element_name(id), ie_len);
      switch (id) {
        case 0: {
          char ssidbuf[33];
          int n = shown_len > 32 ? 32 : shown_len;
          memcpy(ssidbuf, f_ + data_start, n);
          ssidbuf[n] = '\0';
          if (n == 0) file.print(F("(leer/versteckt)"));
          else file.printf_P(PSTR("\"%s\""), ssidbuf);
          break;
        }
        case 1: case 50: {
          for (int i = 0; i < shown_len; i++) {
            uint8_t v = f_[data_start + i];
            bool basic = (v & 0x80) != 0;
            int whole = (v & 0x7F) / 2;
            int frac = ((v & 0x7F) % 2) * 5;
            file.printf_P(PSTR("%s%d.%d%s"), i > 0 ? ", " : "", whole, frac, basic ? "*" : "");
          }
          if (shown_len > 0) file.print(F(" Mbps (* = Basisrate)"));
          break;
        }
        case 3:
          if (shown_len >= 1) file.printf_P(PSTR("Kanal %d"), f_[data_start]);
          break;
        case 221:
          if (shown_len >= 4) {
            uint8_t oui_as_mac[6] = { f_[data_start], f_[data_start + 1], f_[data_start + 2], 0, 0, 0 };
            String vendor = vendorCache_lookup_or_search(oui_as_mac);
            file.printf_P(PSTR("OUI %02x:%02x:%02x (%s), Typ %d"),
                          f_[data_start], f_[data_start + 1], f_[data_start + 2],
                          vendor.c_str(), f_[data_start + 3]);
          }
          break;
        default:
          break;
      }
      file.println();
      pos = data_start + ie_len;
      ie_count++;
      yield();
    }
    if (ie_count == 0) {
      file.println(F(" (keine Information Elements im erfassten Bereich)"));
    }
    file.println(F("-------------------------------------------------------"));
    file.close();
  }

  frametrap_beacon_disarm(bssid);
  free(frametrap_beacon_catches[slot].buf);
  frametrap_beacon_catches[slot].buf = NULL;
}

// =====================================================================
// NEU 2.27.1 REQ-4: Implementierung der Rueckkehr-Signalisierungs-
// Zustandsverwaltung. Gleiches Muster wie der Vendor-Cache
// (vendorCache_begin/end): dynamisch beim ECHTEN Menue-4-Eintritt
// alloziert, bei jedem Redraw waehrend derselben Sitzung unveraendert
// (Guard-Flag), erst beim echten Verlassen wieder komplett freigegeben.
// =====================================================================
void watchlistPulse_begin()
{
  if (g_watchlistPulseSessionActive) {
    return;  // Sitzung laeuft bereits (Redraw) - Zustand bleibt erhalten
  }
  if (g_watchlistPulseState != NULL) {
    free(g_watchlistPulseState);
  }
  g_watchlistPulseState = NULL;
  g_watchlistPulseStateCount = 0;
  g_watchlistPulseSessionActive = true;
}

void watchlistPulse_end()
{
  if (g_watchlistPulseState != NULL) {
    free(g_watchlistPulseState);
    g_watchlistPulseState = NULL;
  }
  g_watchlistPulseStateCount = 0;
  g_watchlistPulseSessionActive = false;
}

// Prueft fuer EINEN Watchlist-Eintrag, ob eine Rueckkehr-Flanke vorliegt,
// aktualisiert dabei den gespeicherten Zustand und liefert true, wenn ein
// Impuls ausgeloest werden soll. Trigger-Bedingungen:
//   (a) letzter Redraw war "(noch out)", jetzt sichtbar (jede Art von
//       Wiederauftauchen aus kompletter Abwesenheit)
//   (b) letztes Alter war > 999s UND das aktuelle Alter ist kleiner als
//       das letzte (ein frisches Paket hat den Age-Zaehler zurueckgesetzt,
//       nachdem das Geraet laenger "im k-Bereich" war)
// Beim allerersten Auftreten einer MAC in dieser Sitzung wird NUR der
// Ausgangszustand gemerkt, es wird nie ausgeloest (sonst wuerde jeder
// Menueeintritt fuer alle sichtbaren Eintraege einen Impuls feuern).
bool watchlistPulse_check_and_update(uint8_t *mac, bool currently_out, uint32_t current_age)
{
  int found = -1;
  for (int i = 0; i < g_watchlistPulseStateCount; i++) {
    if (memcmp(g_watchlistPulseState[i].mac, mac, 6) == 0) {
      found = i;
      break;
    }
  }

  bool trigger = false;

  if (found < 0) {
    // Erstes Auftreten in dieser Sitzung - nur Ausgangszustand merken,
    // Array bei Bedarf wachsen lassen (in 8er-Bloecken, analog Vendor-Cache)
    if (g_watchlistPulseStateCount < MAX_WATCHLIST) {
      if (g_watchlistPulseState == NULL) {
        g_watchlistPulseState = (WatchlistPulseEntry *) malloc(8 * sizeof(WatchlistPulseEntry));
      } else if (g_watchlistPulseStateCount % 8 == 0) {
        int newCapacity = ((g_watchlistPulseStateCount / 8) + 1) * 8;
        if (newCapacity > MAX_WATCHLIST) newCapacity = MAX_WATCHLIST;
        g_watchlistPulseState = (WatchlistPulseEntry *) realloc(g_watchlistPulseState,
                                                                 newCapacity * sizeof(WatchlistPulseEntry));
      }
      if (g_watchlistPulseState != NULL) {
        memcpy(g_watchlistPulseState[g_watchlistPulseStateCount].mac, mac, 6);
        g_watchlistPulseState[g_watchlistPulseStateCount].last_age =
          currently_out ? WATCHLIST_PULSE_WAS_OUT : current_age;
        g_watchlistPulseStateCount++;
      }
    }
    return false;
  }

  uint32_t prev_age = g_watchlistPulseState[found].last_age;

  if (!currently_out) {
    if (prev_age == WATCHLIST_PULSE_WAS_OUT) {
      trigger = true;  // (a) aus "noch out" wieder aufgetaucht
    } else if (prev_age > 999 && current_age < prev_age) {
      trigger = true;  // (b) Age-Drop nach k-Bereich
    }
    g_watchlistPulseState[found].last_age = current_age;
  } else {
    g_watchlistPulseState[found].last_age = WATCHLIST_PULSE_WAS_OUT;
  }

  return trigger;
}

// NEU 2.28.0: Prueft die Rueckkehr-Signalisierung fuer ALLE Watchlist-
// Eintraege, unabhaengig davon, ob Menue 4 gerade angezeigt wird. Wird aus
// menu_periodic() heraus bei JEDEM Schleifendurchlauf aufgerufen (eigenes,
// nicht-blockierendes 1s-Zeitfenster) - vorher griff die Signalisierung nur,
// solange man sich tatsaechlich in Menue 4 aufhielt, weil die Pruefung
// bislang Teil von dessen Redraw-Schleife war. Nutzt denselben permanenten
// Zustand (g_watchlistPulseState, seit setup() aktiv) wie die Anzeige in
// Menue 4 - beide greifen auf dieselbe Zustandsverfolgung zu, ein Uebergang
// wird dadurch nur einmal ausgeloest, unabhaengig davon, welche der beiden
// Stellen zuerst dran ist.
uint32_t last_watchlist_bg_check_time = 0;

void watchlist_background_check()
{
  if (watchlist_count == 0) return;

  uint32_t now_ms = millis();
  if (now_ms - last_watchlist_bg_check_time < 1000) return;
  last_watchlist_bg_check_time = now_ms;

  uint64_t now = effective_now();
  bool pulse_enabled = enable_return_pulse && signal_pin >= 0 && signal_enabled;

  for (int i = 0; i < watchlist_count; i++) {
    watchlist_sighting sighting = find_freshest_watchlist_sighting(watchlist[i].mac, now);
    bool currently_out = !sighting.found;
    uint32_t age = currently_out ? 999999UL : (uint32_t)(now - sighting.last_heard);

    if (watchlist_entry_is_timewatched(i)) {
      timewatch_check_and_log(watchlist[i].mac, age, now);
    }

    if (pulse_enabled) {
      uint32_t pulse_age = currently_out ? 0 : age;
      if (watchlistPulse_check_and_update(watchlist[i].mac, currently_out, pulse_age)) {
        signal_start_return_pulse();
      }
    }
  }
}

void menu_enter_watchlist()
{
  ram_debug_sample(RDP_WATCHLIST);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
  CallChainGuard __cc_guard(RDP_WATCHLIST);  // NEU 2.30.35: Call-Chain-Erweiterung
  menu_state = STATE_WATCHLIST;
  watch_delete_mode = false;
  watch_delete_input_len = 0;
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  
  // NEU 2.26.0: Vendor-Cache beim Menueeintritt initialisieren
  vendorCache_begin();
  // NEU 2.27.1 REQ-4: Rueckkehr-Signalisierungs-Zustand beim Menueeintritt
  // initialisieren (No-Op bei Redraw waehrend laufender Sitzung, siehe
  // watchlistPulse_begin())
  watchlistPulse_begin();
  Serial.println(F("======================================================="));
  Serial.println(F(" MAC-Adress-Watchlist"));
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" Aktualisierung: %ds (u=+5s d=-5s)\r\n"), watchlist_refresh_sec);
  // NEU 2.23.0: Vendor-Info zur Hilfe hinzufuegen (analog Menue 3a)
  Serial.printf_P(PSTR(" Hersteller anzeigen: %s (v=toggle)\r\n"), show_vendors_in_watchlist ? "EIN" : "AUS");
  // NEU 2.27.1 REQ-4: Status der Rueckkehr-Signalisierung anzeigen
  Serial.printf_P(PSTR(" Rueckkehr-Signal: %s (p=toggle)%s\r\n"),
                enable_return_pulse ? "EIN" : "AUS",
                (enable_return_pulse && signal_pin < 0) ? "  [kein Pin konfiguriert!]" : "");
  Serial.println(F("-------------------------------------------------------"));
  if (show_vendors_in_watchlist) {
    // BUGFIX 2.27.1: Header war nicht auf die tatsaechliche Datenausgabe
    // abgestimmt (Ursachen: (a) Index "%d" statt "%2d" -> 1-/2-stellige
    // Eintragsnummern erzeugten unterschiedliche Zeilenlaengen, (b) der
    // "(noch out)"-Zweig war 1 Zeichen laenger als der Normalzweig, (c) die
    // Position von "Hersteller" im Header-String selbst passte an keiner
    // der beiden Stellen zur tatsaechlichen Spalte). Alle drei Ursachen
    // behoben.
    // BUGFIX 2.27.2: zusaetzlich kompakter gemacht (weniger Leerzeichen
    // ueberall, Beschreibung-Feld verschmalert) - "Hersteller" steht jetzt
    // exakt auf Spalte 41, rechnerisch gegen die reale printf-Ausgabe
    // verifiziert (nicht nur geschaetzt).
    Serial.println(F(" #  MAC          ch Age -db Beschreibung Hersteller"));
  } else {
    Serial.println(F(" #  MAC          ch Age -db Beschreibung"));
  }
  Serial.println(F("-------------------------------------------------------"));

  uint64_t now = effective_now();
  for (int i = 0; i < watchlist_count; i++) {
    // NEU 2.30.21: find_freshest_watchlist_sighting() statt find_freshest_
    // entry_for_station() - erkennt jetzt auch MACs, die nur als AP (Beacon-
    // Sender) auftreten, nicht nur als Client (Nutzer-Fall: Watchlist-Eintrag
    // war schon immer ausschliesslich AP, nie Client, wurde bisher trotz
    // sichtbarer Beacons immer als "out"/uralt angezeigt). MAC-Ausgabe nutzt
    // jetzt einheitlich watchlist[i].mac direkt statt clients_known[slot].
    // station - das ist per Konstruktion (memcmp-Treffer) ohnehin dieselbe
    // MAC, macht die Anzeige aber unabhaengig davon, aus welcher Quelle die
    // Sichtung stammt.
    watchlist_sighting sighting = find_freshest_watchlist_sighting(watchlist[i].mac, now);
    if (! sighting.found) {
      // NEU 2.19.0: Formatierung "(noch out)" für nie gesehene Geräte
      // NEU 2.20.3 BUG8: Beschreibung auch anzeigen wenn Gerät nie gesehen
      // BUGFIX 2.27.1: "%2d" statt "%d", damit beide Zweige gleich lang sind
      // (Grundlage fuer die Hersteller-Ausrichtung).
      // BUGFIX 2.27.2: auf Wunsch kompakter gemacht - kein zusaetzliches
      // fuehrendes Leerzeichen vor dem Index mehr (nur noch das aus "%2d"),
      // "(noch out)" ruemckt 1 Zeichen nach links, Beschreibung-Feld von 20
      // auf 12 Zeichen verschmalert (Breite = Laenge des Wortes
      // "Beschreibung" selbst) mit nur noch 1 Leerzeichen Abstand statt 3.
      Serial.printf_P(PSTR("%2d) "), i);
      print_mac(watchlist[i].mac, NULL);
      Serial.printf_P(PSTR(" (noch out) %-12.12s"), watchlist[i].desc);
    } else {
      // Format: "# MAC ch Age -db Beschreibung" (rechtsbündig)
      // BUGFIX 2.27.1: "%2d" statt "%d" - ein 1-stelliger Index (0-9) erzeugte
      // eine 1 Zeichen kuerzere Zeile als ein 2-stelliger (10-31, MAX_WATCHLIST
      // = 32), wodurch die Hersteller-Spalte je nach Eintragsnummer wanderte.
      Serial.printf_P(PSTR("%2d) "), i);
      print_mac(watchlist[i].mac, NULL);
      
      // Channel
      Serial.printf_P(PSTR(" %2d"), sighting.channel);
      
      // Age
      // BUGFIX 2.26.1: nutzte bisher eigenen, von Menue 3a unabhaengigen
      // Code mit einem Format-Bruch bei >=1000s (" %3d" = 4 Zeichen breit,
      // " %3dk" = 5 Zeichen breit -> 1 Zeichen Versatz, siehe Bug-Report).
      // Jetzt: gemeinsame format_age_field()-Funktion (garantiert konstante
      // 3-Zeichen-Breite), identisch zu Menue 3a/format_client_cell().
      int age_sec = now - sighting.last_heard;
      Serial.printf_P(PSTR(" %s"), format_age_field(age_sec));
      
      // RSSI
      Serial.printf_P(PSTR(" %3d"), sighting.rssi);
      
      // Beschreibung
      // BUGFIX 2.27.2: 3 Leerzeichen -> 1, Breite 20 -> 12 (siehe Begruendung
      // oben im "(noch out)"-Zweig)
      Serial.printf_P(PSTR(" %-12.12s"), watchlist[i].desc);
    }

    // NEU 2.28.0: Rueckkehr-Signalisierungs-Pruefung hier entfernt - laeuft
    // jetzt global im Hintergrund ueber watchlist_background_check() (siehe
    // menu_periodic()), unabhaengig davon, ob dieses Menue gerade offen ist.

    // NEU 2.23.0: Hersteller-Spalte hinter der Beschreibung, on-demand
    // (kein Batch-Cache) - unabhaengig davon, ob das Geraet aktuell "out"
    // ist, da die Watchlist-MAC selbst (watchlist[i].mac) immer bekannt ist.
    if (show_vendors_in_watchlist) {
      // BUGFIX 2.26.1: nutzt jetzt tatsaechlich den Vendor-Cache (alter
      // Aufruf auskommentiert):
      // char mac_str[18];
      // snprintf_P(mac_str, sizeof(mac_str), PSTR("%02x:%02x:%02x:%02x:%02x:%02x"), ...);
      // String vendor = VendorLookup::getManufacturer(String(mac_str));
      String vendor = vendorCache_lookup_or_search(watchlist[i].mac);
      Serial.printf_P(PSTR("   %s"), vendor.c_str());
    }

    Serial.println();
    yield();
  }
  if (watchlist_count == 0) {
    Serial.println(F(" (Watchlist ist leer)"));
  }
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" a = MAC-Adresse hinzufuegen"));
  Serial.println(F(" x+Zahl+Enter = Eintrag loeschen"));
  Serial.println(F(" Backspace/ESC = zurueck zum Menue"));
  last_watchlist_refresh_time = millis() / 1000;
  
  // BUGFIX 2.26.3: vendorCache_end() hier ENTFERNT (siehe Begruendung in
  // menu_enter_ssid_list()) - Freigabe erfolgt an den echten Austrittspunkten.
}

void menu_enter_watchlist_add_mac()
{
  menu_state = STATE_WATCHLIST_ADD_MAC;
  watch_mac_input_len = 0;
  watch_mac_input_buf[0] = '\0';
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Watchlist: neue MAC-Adresse hinzufuegen"));
  Serial.println(F("======================================================="));
  Serial.println(F(" MAC-Adresse eingeben (12 Hex-Zeichen, z.B. 0c80633c5d53)"));
  Serial.println(F(" Enter = weiter zur Beschreibung."));
  Serial.println(F(" Backspace bei leerer Eingabe/ESC = abbrechen."));
  Serial.print(F(" MAC: "));
  if (offline_banner_will_print()) Serial.println();  // BUGFIX 2.30.44
}

void menu_enter_watchlist_add_desc()
{
  menu_state = STATE_WATCHLIST_ADD_DESC;
  watch_desc_input_len = 0;
  watch_desc_input_buf[0] = '\0';
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Watchlist: Beschreibung eingeben"));
  Serial.println(F("======================================================="));
  char macstr[13];
  for (int b = 0; b < 6; b++) sprintf_P(macstr + b * 2, PSTR("%02x"), pending_watch_mac[b]);
  macstr[12] = '\0';
  Serial.printf_P(PSTR(" MAC: %s\r\n"), macstr);
  Serial.println(F(" Beschreibung eingeben (max. 32 Zeichen), Enter = speichern."));
  Serial.println(F(" Backspace bei leerer Eingabe/ESC = abbrechen."));
  Serial.print(F(" Beschreibung: "));
  if (offline_banner_will_print()) Serial.println();  // BUGFIX 2.30.44
}

// NEU 2.30.65: Formatiert die Systemlaufzeit (millis()) als 8-stelligen Code
// "ddhhmmss" (Tage/Stunden/Minuten/Sekunden seit dem letzten Boot, je
// zweistellig, ohne Trennzeichen) - Ersatz fuer den bisherigen rohen
// millis()-Wert (variable Laenge, bis zu 10 Stellen) in allen Dateinamen,
// die ohne NTP-Synchronisation entstehen. out muss mindestens 9 Byte gross
// sein (8 Ziffern + Nullterminator); outlen wird trotzdem respektiert.
// dd bleibt IMMER zweistellig: millis() (uint32_t) laeuft nach ca. 49,7
// Tagen ueber, der Tageszaehler kann also nie ueber 49 hinauskommen.

// NEU 2.30.67: Zwischenbildschirm fuer das Anlegen/Aktualisieren eines
// TimeWatch-Eintrags. Der vorhandene watch_desc_input_buf wird wiederverwendet.
void menu_enter_timewatch_add_desc()
{
  menu_state = STATE_TIMEWATCH_ADD_DESC;
  watch_desc_input_len = 0;
  watch_desc_input_buf[0] = '\0';
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;
  Serial.println(F("======================================================="));
  Serial.println(F(" TimeWatch: Beschreibung eingeben"));
  Serial.println(F("======================================================="));
  char macstr[13];
  for (int b = 0; b < 6; b++) sprintf_P(macstr + b * 2, PSTR("%02x"), pending_timewatch_mac[b]);
  macstr[12] = '\0';
  Serial.printf_P(PSTR(" MAC: %s\r\n"), macstr);
  Serial.println(F(" Beschreibung eingeben (max. 10 Zeichen fuer den Dateinamen),"));
  Serial.println(F(" Enter = speichern, leer = ohne Beschreibung."));
  Serial.println(F(" Backspace bei leerer Eingabe/ESC = abbrechen."));
  Serial.print(F(" Beschreibung: "));
  if (offline_banner_will_print()) Serial.println();
}


void format_uptime_ddhhmmss(char *out, size_t outlen)
{
  uint32_t total_sec = millis() / 1000;
  uint32_t dd = total_sec / 86400;
  uint32_t hh = (total_sec % 86400) / 3600;
  uint32_t mm = (total_sec % 3600) / 60;
  uint32_t ss = total_sec % 60;
  snprintf_P(out, outlen, PSTR("%02lu%02lu%02lu%02lu"),
    (unsigned long)dd, (unsigned long)hh, (unsigned long)mm, (unsigned long)ss);
}

// Schreibt die aktuellen Listen (Clients + APs) als Textdatei ins Flash
// NEU 2.12.0: Auto-Save mit Timestamp (mit NTP)
// Generiert Dateinamen wie "autosave_260731_001307.txt" (YYMMDD, seit 2.30.65)
// (Bindestriche → Unterstriche, weil SPIFFS Bindestriche nicht gut verträgt)
void perform_auto_save_with_timestamp()
{
  if (!ntp_synced) return;
  led_force_off();  // NEU 2.17.6: zeitkritisch (Dateitransfer/-schreiben) - Status-LED aus

  time_t tz_now = current_unix_time_with_tz();
  struct tm* timeinfo = localtime(&tz_now);
  
  char filename[50];
  // WICHTIG: OHNE .txt - wird von save_current_lists hinzugefügt!
  snprintf_P(filename, sizeof(filename), PSTR("autosave_%02d%02d%02d_%02d%02d%02d"),
    timeinfo->tm_year % 100, timeinfo->tm_mon + 1, timeinfo->tm_mday,
    timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
  
  Serial.printf_P(PSTR(" Auto-Save (NTP): speichern als '%s.txt' ...\r\n"), filename);
  int result = save_current_lists(filename);
  if (result > 0) {
    Serial.printf_P(PSTR(" Auto-Save erfolgreich: %d Eintraege gespeichert.\r\n"), result);
    // NEU 2.16.0: Markiere diese Datei als Auto-Load (last loaded)
    strncpy(autoload_filename, filename, 39);
    autoload_filename[39] = '\0';
    save_all_settings();  // Speichere den Dateinamen persistent
  } else {
    Serial.println(F(" Auto-Save FEHLER: Datei konnte nicht angelegt werden!"));
  }
}

// NEU 2.12.0: Auto-Save ohne Timestamp (ohne NTP)
// Generiert Dateinamen wie "autosave_123_45_00134502" (Clients-APs-ddhhmmss)
// .txt wird von save_current_lists hinzugefügt!
void perform_auto_save_without_timestamp()
{
  char filename[50];
  // NEU 2.30.65: millis() -> ddhhmmss (Muster "autosave_<Clients>_<APs>_..." unveraendert)
  char uptime[9];
  format_uptime_ddhhmmss(uptime, sizeof(uptime));
  // WICHTIG: OHNE .txt - wird von save_current_lists hinzugefügt!
  snprintf_P(filename, sizeof(filename), PSTR("autosave_%d_%d_%s"),
    clients_known_count, aps_known_live_count(), uptime);
  
  Serial.printf_P(PSTR(" Auto-Save (24h Timer): speichern als '%s.txt' ...\r\n"), filename);
  int result = save_current_lists(filename);
  if (result > 0) {
    Serial.printf_P(PSTR(" Auto-Save erfolgreich: %d Eintraege gespeichert.\r\n"), result);
    // NEU 2.16.0: Markiere diese Datei als Auto-Load (last loaded)
    strncpy(autoload_filename, filename, 39);
    autoload_filename[39] = '\0';
    save_all_settings();  // Speichere den Dateinamen persistent
  } else {
    Serial.println(F(" Auto-Save FEHLER: Datei konnte nicht angelegt werden!"));
  }
}

int save_current_lists(const char* filename){
  led_force_off();char path[40];snprintf_P(path,sizeof(path),PSTR("/%s.txt"),filename);if(!make_collision_safe_path(path,path,sizeof(path))){Serial.println(F(" Fehler: kollisionsfreier Dateiname nicht verfuegbar."));return -1;}File f=LittleFS.open(path,"w");if(!f){Serial.println(F(" Fehler: Datei konnte nicht angelegt werden."));return -1;}
  uint64_t now=effective_now();int entry_count=0;
  // NEU 2.30.62: Sniffing fuer die gesamte Speicherdauer pausieren (Klartext
  // wie komprimiert) - laeuft dadurch unterbrechungsfrei, register_client()/
  // register_beacon() koennen die gerade geschriebenen Listen nicht mehr
  // veraendern. go_online() kompensiert last_heard am Ende automatisch um
  // die Pausendauer (siehe dortiger Kommentar) - kein sichtbarer Age-Sprung.
  // War bereits (manuell) offline, bleibt es das auch danach - kein
  // ungewolltes Wiedereinschalten. #define RETURN_SAVE fasst alle
  // Rueckkehrpunkte zusammen, damit go_online() an keinem davon vergessen
  // werden kann.
  bool was_online=online_mode;if(was_online)go_offline();
  #define RETURN_SAVE(x) { if(was_online)go_online(); return (x); }
  if(!scenario_compression_enabled){
    // NEU 2.30.63: ausgelagert nach write_scenario_plaintext() - dieselbe
    // Funktion schreibt jetzt auch den ntfy-Anhang im Modus 0 (siehe dort),
    // damit beide Formate garantiert identisch bleiben.
    entry_count=write_scenario_plaintext(f,now);
  }else{
    if(f.write(SCENARIO_MAGIC_HEADER,4)!=4){f.close();LittleFS.remove(path);RETURN_SAVE(-1)}
    // NEU 2.30.62: Live-Pruefung des groessten zusammenhaengenden freien
    // Blocks unmittelbar vor der Allokation - Werte aus dem Diagnose-Menue
    // sind hierfuer nicht verwertbar (anderer Zeitpunkt, ggf. bei laufendem
    // Sniffing gemessen). RESERVE haelt dem WLAN-Stack Platz frei (Erfahrungs-
    // wert). Reicht der Block fuer Fenster+Hash nicht, faellt der Encoder auf
    // den reinen Fensterspeicher zurueck (e.hash bleibt NULL) - dann arbeitet
    // scenario_find_match() weiter linear wie bisher (langsamer, aber korrekt,
    // ohne weiteren RAM-Bedarf). Erst wenn selbst das Fenster allein nicht
    // passt, wird wie bisher abgebrochen.
    const uint32_t SCENARIO_RESERVE=3072;
    uint32_t free_block=(uint32_t)ESP.getMaxFreeBlockSize();
    bool use_hash=(free_block>=(uint32_t)SCENARIO_LZSS_WINDOW+SCENARIO_HASH_BYTES+SCENARIO_RESERVE);
    size_t alloc_size=SCENARIO_LZSS_WINDOW+(use_hash?SCENARIO_HASH_BYTES:0);
    uint8_t*w=(uint8_t*)malloc(alloc_size);if(!w){f.close();LittleFS.remove(path);Serial.println(F(" Fehler: Kompressionsfenster konnte nicht reserviert werden."));RETURN_SAVE(-1)}
    g_scenario_dbg_raw_bytes=0;g_scenario_dbg_rle_bytes=0;uint32_t dbg_t_start=millis();  // NEU 2.30.53
    ScenarioEncoder e;memset(&e,0,sizeof(e));e.file=&f;e.window=w;e.hash=use_hash?(uint16_t*)(w+SCENARIO_LZSS_WINDOW):NULL;e.ok=true;bool ok=true;char gen_ts[32];format_generation_timestamp(gen_ts,sizeof(gen_ts));
    ok=scenario_plain_fmt(e,PSTR("# Erzeugt: %s | Programmversion: v%s\r\n"),gen_ts,FIRMWARE_VERSION);if(ok)ok=scenario_plain_fmt(e,PSTR("# WiFi-Monitor Sicherung - %d Clients, %d Access Points\r\n"),clients_known_count,aps_known_live_count());if(ok)ok=scenario_plain_P(e,PSTR("-------------------------------------------------------------------------------------\r\n"));
    for(int u=0;ok&&u<clients_known_count;u++){clientinfo ci=clients_known[u];ok=scenario_plain_P(e,PSTR("DEVICE: "));for(int i=0;ok&&i<6;i++)ok=scenario_plain_fmt(e,PSTR("%02x"),ci.station[i]);if(ok)ok=scenario_plain_P(e,PSTR(" ==> "));bool known=(ci.ap_idx<aps_known_count&&!ap_slot_free(ci.ap_idx));if(ok&&known){ok=scenario_plain_fmt(e,PSTR("[%32s]  "),aps_known[ci.ap_idx].ssid);for(int i=0;ok&&i<6;i++)ok=scenario_plain_fmt(e,PSTR("%02x"),aps_known[ci.ap_idx].bssid[i]);}else if(ok)ok=scenario_plain_P(e,PSTR("[                                ??]  ????????????"));if(ok)ok=scenario_plain_fmt(e,PSTR(" %3d   %d   %d   %4d\r\n"),ci.channel,(int)(now-ci.last_heard),ci.reported,ci.rssi);entry_count++;yield();}
    for(int u=0;ok&&u<aps_known_count;u++){if(ap_slot_free(u))continue;beaconinfo bi=aps_known[u];ok=scenario_plain_fmt(e,PSTR("BEACON: <=============== [%32s]  "),bi.ssid);for(int i=0;ok&&i<6;i++)ok=scenario_plain_fmt(e,PSTR("%02x"),bi.bssid[i]);if(ok)ok=scenario_plain_fmt(e,PSTR(" %3d   %d   %d   %4d\r\n"),bi.channel&AP_CHANNEL_MASK,(int)(now-bi.last_heard),bi.reported,bi.rssi);entry_count++;yield();}
    if(ok)ok=scenario_plain_P(e,PSTR("# SETTINGS\r\n"));if(ok)ok=scenario_plain_fmt(e,PSTR("sort_field=%d\r\n"),(int)current_sort_field);if(ok)ok=scenario_plain_fmt(e,PSTR("sort_ascending=%d\r\n"),sort_ascending?1:0);if(ok)ok=scenario_plain_fmt(e,PSTR("ap_sort_field=%d\r\n"),(int)current_ap_sort_field);if(ok)ok=scenario_plain_fmt(e,PSTR("ap_sort_ascending=%d\r\n"),ap_sort_ascending?1:0);if(ok)ok=scenario_plain_fmt(e,PSTR("list_refresh_sec=%d\r\n"),list_refresh_sec);if(ok)ok=scenario_plain_fmt(e,PSTR("rssi_trend_threshold=%d\r\n"),rssi_trend_threshold);if(ok)ok=scenario_plain_fmt(e,PSTR("two_col_threshold_devices=%d\r\n"),two_col_threshold_devices);if(ok)ok=scenario_plain_fmt(e,PSTR("two_col_threshold_ssids=%d\r\n"),two_col_threshold_ssids);if(ok)ok=scenario_encoder_finish(e);free(w);
    uint32_t dbg_t_elapsed=millis()-dbg_t_start;  // NEU 2.30.53
    if(ok){  // NEU 2.30.53: Kompressions-Debug-Ausgabe (testweise), NEU 2.30.62: zusaetzlich Hash-Modus + freier Block
      uint32_t comp_size=(uint32_t)f.size();
      uint32_t pct_rle=g_scenario_dbg_raw_bytes?(uint32_t)(100UL*g_scenario_dbg_rle_bytes/g_scenario_dbg_raw_bytes):0;
      uint32_t pct_total=g_scenario_dbg_raw_bytes?(uint32_t)(100UL*comp_size/g_scenario_dbg_raw_bytes):0;
      Serial.printf_P(PSTR(" [Kompression-Debug] Original: %lu B | nach RLE: %lu B (%lu%%) | nach LZSS: %lu B (%lu%% v. Original) | Zeit: %lu ms | Hash: %s | Freier Block vorher: %lu B\r\n"),
        (unsigned long)g_scenario_dbg_raw_bytes,(unsigned long)g_scenario_dbg_rle_bytes,(unsigned long)pct_rle,
        (unsigned long)comp_size,(unsigned long)pct_total,(unsigned long)dbg_t_elapsed,use_hash?"an":"aus (RAM-Fallback)",(unsigned long)free_block);
    }
    if(!ok){f.close();LittleFS.remove(path);Serial.println(F(" Fehler: Szenario-Kompression fehlgeschlagen."));RETURN_SAVE(-1)}
  }
  f.close();Serial.printf_P(PSTR("\r\n Gespeichert als %s%s\r\n"),path,scenario_compression_enabled?" (komprimiert)":" (Klartext)");
  RETURN_SAVE(entry_count)
  #undef RETURN_SAVE
}

// Wandelt 12 Hex-Zeichen (z.B. "a1b2c3d4e5f6") in 6 Bytes um
void parse_mac_hex(const char* s, uint8_t* out)
{
  char byte_str[3];
  for (int i = 0; i < 6; i++) {
    byte_str[0] = s[i * 2];
    byte_str[1] = s[i * 2 + 1];
    byte_str[2] = '\0';
    out[i] = (uint8_t) strtol(byte_str, NULL, 16);
  }
}

// ============================================================================
// Szenario-Kompression v1 (CSZ1) - Implementierung
// NEU 2.30.50: Die 17 unten stehenden Funktionen waren im hochgeladenen
// Stand nur als Forward-Declaration vorhanden (siehe oben, Zeile ~4241 ff.),
// ohne jeden Funktionskoerper - das war die alleinige Ursache aller
// "undefined reference to scenario_..."-Linkerfehler. scenario_reader_
// reset()/scenario_reader_read_line()/scenario_print_file_content() waren
// bereits vollstaendig vorhanden und bleiben unveraendert (folgen direkt
// nach diesem Block).
//
// Format (ein Byte-Strom, WICHTIG: reine interne Kapselung - niemand
// ausserhalb dieser Funktionen liest den Bytestrom direkt, das Format kann
// also frei so gewaehlt werden, dass Kodierung/Dekodierung nachweisbar
// korrekt zusammenpassen):
//   4 Byte Magic-Header "CSZ1" (wird von save_current_lists() bereits davor
//   direkt geschrieben, siehe dort - hier NICHT nochmal).
//   Danach abwechselnd: 1 Flags-Byte + bis zu 8 Tokens (Bit i im Flags-Byte,
//   LSB zuerst = Token i ist ein Match; 0 = Literal-Byte).
//     Literal-Token: 1 Byte (der Rohwert).
//     Match-Token:   2 Byte, LSB-first gepackt:
//                    Bits 0-10  = (Rueckwaerts-Distanz - 1), 0..2047
//                    Bits 11-15 = (Laenge - SCENARIO_LZSS_MIN_MATCH), 0..31
//   Davor liegt eine einfache RLE-Vorstufe (siehe scenario_rle_input/_emit):
//   laengere Laeufe desselben Bytes werden als 3-Byte-Sequenz ESCAPE,Wert,
//   (Anzahl-1) in den LZSS-Literalstrom eingespeist. Ein echtes 0xFF-Literal
//   wird aus Eindeutigkeitsgruenden IMMER ueber dieselbe Escape-Sequenz
//   kodiert (Anzahl=1), auch wenn kein "Lauf" vorliegt.
//
// Match-Suche bewusst auf back >= len begrenzt (keine ueberlappenden,
// selbstreferenzierenden Matches) - das kostet in diesem stark strukturierten
// Textformat kaum Kompressionsgrad (lange Gleichlaeufe uebernimmt ohnehin
// die RLE-Vorstufe), vermeidet dafuer jedes Risiko einer fehlerhaften
// Sonderbehandlung ueberlappender Bereiche.
// ============================================================================

static void scenario_hist_put(ScenarioEncoder &e, uint8_t b)
{
  e.window[e.win_pos] = b;
  e.win_pos = (uint16_t)(e.win_pos + 1) & (SCENARIO_LZSS_WINDOW - 1);
  if (e.hist_len < SCENARIO_LZSS_WINDOW) e.hist_len++;
  e.abs_ctr++;  // NEU 2.30.62: siehe Kommentar bei scenario_find_match_hash
}

static uint8_t scenario_hist_byte(const ScenarioEncoder &e, uint16_t back)
{
  uint16_t idx = (uint16_t)(e.win_pos - back) & (SCENARIO_LZSS_WINDOW - 1);
  return e.window[idx];
}

// NEU 2.30.62: Hash ueber die ersten 3 Bytes des Lookahead-Puffers -
// Multiplikative Streuung (Knuth), obere SCENARIO_HASH_BITS Bit des
// Produkts als Bucket-Index. e.hash ist ein Feld aus SCENARIO_HASH_SIZE
// Buckets zu je SCENARIO_HASH_WAYS Kandidaten (juengster zuerst).
// WICHTIG: das Literal braucht das "u"-Suffix (uint32_t), NICHT "UL"
// (unsigned long) - der Algorithmus verlaesst sich bewusst auf einen
// Ueberlauf/Wraparound exakt bei 32 Bit. "unsigned long" ist auf dem
// ESP8266 zwar ebenfalls 32 Bit breit, auf vielen anderen Plattformen
// (u.a. 64-Bit-PCs, dort beim Testen der Kompression entdeckt) aber
// 64 Bit - dann faende der Ueberlauf nicht mehr statt und der
// Bucket-Index koennte weit ausserhalb von e.hash[] liegen.
static inline uint16_t scenario_hash3(uint8_t a, uint8_t b, uint8_t c)
{
  uint32_t v = (uint32_t)a | ((uint32_t)b << 8) | ((uint32_t)c << 16);
  return (uint16_t)((v * 2654435761u) >> (32 - SCENARIO_HASH_BITS));
}

// Traegt Position e.abs_ctr (= aktuelle Position von look[idx], siehe Aufruf
// in scenario_lzss_step) unter dem Hash von look[idx..idx+2] ein. Verdraengt
// bei SCENARIO_HASH_WAYS=2 einfach per Verschieben den aeltesten Kandidaten
// des Buckets - kein Suchen, kein Loeschen noetig.
static void scenario_hash_insert(ScenarioEncoder &e, uint8_t idx)
{
  uint16_t h = (uint16_t)(scenario_hash3(e.look[idx], e.look[idx + 1], e.look[idx + 2]) * SCENARIO_HASH_WAYS);
  for (uint8_t w = SCENARIO_HASH_WAYS - 1; w > 0; w--) e.hash[h + w] = e.hash[h + w - 1];
  e.hash[h] = e.abs_ctr;
}

// NEU 2.30.62: Hash-gestuetzte Variante von scenario_find_match() - prueft
// statt bis zu 2048 Positionen linear nur die SCENARIO_HASH_WAYS zuletzt
// unter demselben 3-Byte-Praefix eingetragenen Kandidaten. back wird ueber
// vorzeichenlose 16-Bit-Subtraktion aus abs_ctr berechnet; ein Ueberlauf von
// abs_ctr nach 65536 Bytes liefert dieselbe Differenz weiterhin korrekt
// (identisches Prinzip wie win_pos, nur mit Modulo 65536 statt 2048). Ein
// verwaister Kandidat (aus einer laengst verlassenen Fensterposition) wird
// durch den Test back<=e.hist_len zuverlaessig verworfen; im (praktisch nie
// eintretenden) Fall einer zufaelligen Ueberlauf-Kollision waere back
// scheinbar klein, der folgende Bytevergleich liefe dann einfach gegen
// aktuellen, aber falschen Fensterinhalt - keine Bufferueberschreitung,
// hoechstens ein verpasster oder suboptimaler Treffer.
static uint8_t scenario_find_match_hash(ScenarioEncoder &e, uint16_t &best_off)
{
  uint8_t best_len = 0;
  best_off = 0;
  uint8_t max_check = (e.look_len < SCENARIO_LZSS_MAX_MATCH) ? e.look_len : SCENARIO_LZSS_MAX_MATCH;
  if (max_check < SCENARIO_LZSS_MIN_MATCH || e.look_len < 3) return 0;
  uint16_t h = (uint16_t)(scenario_hash3(e.look[0], e.look[1], e.look[2]) * SCENARIO_HASH_WAYS);
  for (uint8_t w = 0; w < SCENARIO_HASH_WAYS; w++) {
    uint16_t back = (uint16_t)(e.abs_ctr - e.hash[h + w]);
    if (back == 0 || back > e.hist_len) continue;
    uint8_t limit = (back < max_check) ? (uint8_t)back : max_check;
    if (limit < SCENARIO_LZSS_MIN_MATCH) continue;
    uint8_t len = 0;
    while (len < limit && scenario_hist_byte(e, (uint16_t)(back - len)) == e.look[len]) len++;
    if (len > best_len) {
      best_len = len;
      best_off = back;
      if (best_len >= max_check) break;
    }
  }
  return (best_len >= SCENARIO_LZSS_MIN_MATCH) ? best_len : 0;
}

static uint8_t scenario_find_match(ScenarioEncoder &e, uint16_t &best_off)
{
  uint8_t best_len = 0;
  best_off = 0;
  uint8_t max_check = (e.look_len < SCENARIO_LZSS_MAX_MATCH) ? e.look_len : SCENARIO_LZSS_MAX_MATCH;
  if (max_check < SCENARIO_LZSS_MIN_MATCH) return 0;
  uint16_t max_back = (e.hist_len < SCENARIO_LZSS_WINDOW) ? e.hist_len : SCENARIO_LZSS_WINDOW;

  for (uint16_t back = 1; back <= max_back; back++) {
    // back >= len erzwingen (siehe Kommentar oben) - kein Zugriff auf noch
    // nicht committete Historie.
    uint8_t limit = (back < max_check) ? (uint8_t)back : max_check;
    if (limit < SCENARIO_LZSS_MIN_MATCH) continue;
    uint8_t len = 0;
    while (len < limit && scenario_hist_byte(e, (uint16_t)(back - len)) == e.look[len]) len++;
    if (len > best_len) {
      best_len = len;
      best_off = back;
      if (best_len >= max_check) break;  // laenger ist in diesem Schritt nicht mehr moeglich
    }
    if ((back & 0xFF) == 0) yield();
  }
  return (best_len >= SCENARIO_LZSS_MIN_MATCH) ? best_len : 0;
}

static bool scenario_encoder_flush(ScenarioEncoder &e)
{
  if (e.token_count == 0) return e.ok;
  bool ok = e.ok;
  if (ok) ok = (e.file->write(&e.flags, 1) == 1);
  if (ok && e.token_len > 0) ok = (e.file->write(e.token_buf, e.token_len) == e.token_len);
  e.flags = 0;
  e.token_count = 0;
  e.token_len = 0;
  e.ok = ok;
  return ok;
}

static bool scenario_encoder_token(ScenarioEncoder &e, bool literal, uint8_t a, uint8_t b)
{
  if (! literal) e.flags |= (uint8_t)(1 << e.token_count);
  e.token_buf[e.token_len++] = a;
  if (! literal) e.token_buf[e.token_len++] = b;
  e.token_count++;
  bool ok = e.ok;
  if (e.token_count >= 8) ok = scenario_encoder_flush(e);
  e.ok = e.ok && ok;
  return e.ok;
}

// Kodiert GENAU EIN Token aus dem aktuellen Lookahead-Puffer (look[]),
// schreibt die verbrauchten Rohbytes in die Historie und verschiebt look[]
// entsprechend nach links. Gemeinsam genutzt von scenario_lzss_push() (wenn
// der Lookahead-Puffer voll ist) und scenario_encoder_finish() (zum
// restlosen Leeren am Ende).
static bool scenario_lzss_step(ScenarioEncoder &e)
{
  uint16_t off = 0;
  // NEU 2.30.62: mit Hash-Tabelle (e.hash != NULL) die schnelle Suche
  // nutzen, sonst wie bisher linear (RAM-Fallback, siehe save_current_lists).
  uint8_t len = e.hash ? scenario_find_match_hash(e, off) : scenario_find_match(e, off);
  bool ok;
  if (len >= SCENARIO_LZSS_MIN_MATCH) {
    uint16_t packed = (uint16_t)((off - 1) & 0x07FF) | (uint16_t)((uint16_t)(len - SCENARIO_LZSS_MIN_MATCH) << 11);
    ok = scenario_encoder_token(e, false, (uint8_t)(packed & 0xFF), (uint8_t)((packed >> 8) & 0xFF));
  } else {
    len = 1;
    ok = scenario_encoder_token(e, true, e.look[0], 0);
  }
  // NEU 2.30.62: fuer jede committete Position, an der noch ein volles
  // 3-Byte-Praefix im Lookahead steht, einen Hash-Eintrag setzen - VOR dem
  // jeweiligen hist_put() (das look[] nicht veraendert, nur e.abs_ctr
  // hochzaehlt, siehe dortiger Kommentar), damit e.abs_ctr beim Eintragen
  // noch die Position von look[i] selbst ist.
  for (uint8_t i = 0; i < len; i++) {
    if (e.hash && (uint8_t)(i + 2) < e.look_len) scenario_hash_insert(e, i);
    scenario_hist_put(e, e.look[i]);
  }
  for (uint8_t i = len; i < e.look_len; i++) e.look[i - len] = e.look[i];
  e.look_len -= len;
  e.ok = e.ok && ok;
  return e.ok;
}

static bool scenario_lzss_push(ScenarioEncoder &e, uint8_t b)
{
  g_scenario_dbg_rle_bytes++;  // NEU 2.30.53: Debug-Zaehler, siehe oben
  e.look[e.look_len++] = b;
  if (e.look_len < SCENARIO_LZSS_MAX_MATCH) return e.ok;
  return scenario_lzss_step(e);
}

static bool scenario_rle_emit(ScenarioEncoder &e, uint8_t b)
{
  if (e.rle_count == 0) return e.ok;
  bool ok = e.ok;
  // Ein 0xFF-Byte MUSS unabhaengig von der Lauflaenge immer ueber die
  // Escape-Sequenz laufen, siehe Format-Kommentar oben.
  if (b == SCENARIO_RLE_ESCAPE || e.rle_count >= 4) {
    if (ok) ok = scenario_lzss_push(e, SCENARIO_RLE_ESCAPE);
    if (ok) ok = scenario_lzss_push(e, b);
    if (ok) ok = scenario_lzss_push(e, (uint8_t)(e.rle_count - 1));
  } else {
    for (uint8_t i = 0; ok && i < e.rle_count; i++) ok = scenario_lzss_push(e, b);
  }
  e.rle_count = 0;
  e.rle_pending = false;
  e.ok = ok;
  return ok;
}

static bool scenario_rle_input(ScenarioEncoder &e, uint8_t b)
{
  g_scenario_dbg_raw_bytes++;  // NEU 2.30.53: Debug-Zaehler, siehe oben
  if (e.rle_pending && b == e.rle_value && e.rle_count < 255) {
    e.rle_count++;
    return e.ok;
  }
  bool ok = true;
  if (e.rle_pending) ok = scenario_rle_emit(e, e.rle_value);
  e.rle_value = b;
  e.rle_count = 1;
  e.rle_pending = true;
  e.ok = e.ok && ok;
  return e.ok;
}

static bool scenario_encoder_finish(ScenarioEncoder &e)
{
  bool ok = e.ok;
  if (ok && e.rle_pending) ok = scenario_rle_emit(e, e.rle_value);
  while (ok && e.look_len > 0) ok = scenario_lzss_step(e);
  if (ok && e.token_count > 0) ok = scenario_encoder_flush(e);
  e.ok = ok;
  return ok;
}

static bool scenario_plain(ScenarioEncoder &e, const char *s)
{
  bool ok = e.ok;
  while (ok && *s) { ok = scenario_rle_input(e, (uint8_t)*s); s++; }
  e.ok = ok;
  return ok;
}

static bool scenario_plain_P(ScenarioEncoder &e, PGM_P s)
{
  bool ok = e.ok;
  char c;
  while (ok && (c = (char)pgm_read_byte(s)) != 0) { ok = scenario_rle_input(e, (uint8_t)c); s++; }
  e.ok = ok;
  return ok;
}

static bool scenario_plain_fmt(ScenarioEncoder &e, const char *fmt, ...)
{
  char buf[128];  // reicht fuer jede einzelne hier verwendete formatierte Zeile
  va_list args;
  va_start(args, fmt);
  vsnprintf_P(buf, sizeof(buf), fmt, args);
  va_end(args);
  return scenario_plain(e, buf);
}

// ---------------------------------------------------------------------
// Dekoder-Seite (spiegelbildlich zum Encoder oben)
// ---------------------------------------------------------------------

static void scenario_dec_hist_put(ScenarioDecoder &d, uint8_t b)
{
  d.window[d.win_pos] = b;
  d.win_pos = (uint16_t)(d.win_pos + 1) & (SCENARIO_LZSS_WINDOW - 1);
  if (d.hist_len < SCENARIO_LZSS_WINDOW) d.hist_len++;
}

static bool scenario_decode_lzss(ScenarioDecoder &d, uint8_t &out)
{
  if (d.match_left > 0) {
    uint16_t idx = (uint16_t)(d.win_pos - d.match_pos) & (SCENARIO_LZSS_WINDOW - 1);
    uint8_t b = d.window[idx];
    scenario_dec_hist_put(d, b);
    d.match_left--;
    out = b;
    return true;
  }
  if (d.eof) return false;

  if (d.flag_count >= 8) {
    if (! d.file->available()) { d.eof = true; return false; }
    int fb = d.file->read();
    if (fb < 0) { d.eof = true; return false; }
    d.flags = (uint8_t) fb;
    d.flag_count = 0;
  }
  bool is_match = ((d.flags >> d.flag_count) & 0x01) != 0;
  d.flag_count++;

  if (! is_match) {
    if (! d.file->available()) { d.eof = true; return false; }
    int lb = d.file->read();
    if (lb < 0) { d.eof = true; return false; }
    uint8_t b = (uint8_t) lb;
    scenario_dec_hist_put(d, b);
    out = b;
    return true;
  }

  if (! d.file->available()) { d.eof = true; return false; }
  int b1 = d.file->read();
  if (b1 < 0 || ! d.file->available()) { d.eof = true; return false; }
  int b2 = d.file->read();
  if (b2 < 0) { d.eof = true; return false; }
  uint16_t packed = (uint16_t)b1 | ((uint16_t)b2 << 8);
  d.match_pos = (uint16_t)(packed & 0x07FF) + 1;               // gespeicherte Distanz-1 -> Distanz
  d.match_left = (uint8_t)((packed >> 11) & 0x1F) + SCENARIO_LZSS_MIN_MATCH;

  uint16_t idx = (uint16_t)(d.win_pos - d.match_pos) & (SCENARIO_LZSS_WINDOW - 1);
  uint8_t b = d.window[idx];
  scenario_dec_hist_put(d, b);
  d.match_left--;
  out = b;
  return true;
}

static bool scenario_decode_rle(ScenarioDecoder &d, uint8_t &out)
{
  if (d.rle_mode) {
    out = d.rle_value;
    d.rle_left--;
    if (d.rle_left == 0) d.rle_mode = 0;
    return true;
  }
  uint8_t b;
  if (! scenario_decode_lzss(d, b)) return false;
  if (b != SCENARIO_RLE_ESCAPE) {
    out = b;
    return true;
  }
  uint8_t value, count_minus_1;
  if (! scenario_decode_lzss(d, value)) return false;
  if (! scenario_decode_lzss(d, count_minus_1)) return false;
  uint16_t count = (uint16_t)count_minus_1 + 1;
  out = value;
  if (count > 1) {
    d.rle_mode = 1;
    d.rle_value = value;
    d.rle_left = (uint16_t)(count - 1);
  }
  return true;
}

static int scenario_read_decompressed_byte(ScenarioDecoder &d)
{
  uint8_t b;
  if (! scenario_decode_rle(d, b)) return -1;
  return (int) b;
}

static bool scenario_is_compressed_file(File &f)
{
  uint8_t hdr[4];
  int got = f.read(hdr, 4);
  if (got == 4 && memcmp(hdr, SCENARIO_MAGIC_HEADER, 4) == 0) return true;
  f.seek(0);
  return false;
}

static void scenario_decoder_init(ScenarioDecoder &d, File &f, uint8_t *w)
{
  d.file = &f;
  d.window = w;
  d.win_pos = 0;
  d.hist_len = 0;
  d.flags = 0;
  d.flag_count = 8;   // erzwingt beim ersten Aufruf sofort das Nachladen einer Flag-Gruppe
  d.match_pos = 0;
  d.match_left = 0;
  d.eof = false;
  d.rle_mode = 0;
  d.rle_left = 0;
  d.rle_value = 0;
}

static void scenario_reader_reset(ScenarioLineReader &r)
{
  if (r.compressed) {
    r.file->seek(4);
    scenario_decoder_init(*r.decoder, *r.file, r.decoder->window);
  } else {
    r.file->seek(0);
  }
}

static bool scenario_reader_read_line(ScenarioLineReader &r, String &line)
{
  line = "";
  bool got = false;
  while (true) {
    int c;
    if (r.compressed) c = scenario_read_decompressed_byte(*r.decoder);
    else {
      if (!r.file->available()) break;
      c = r.file->read();
    }
    if (c < 0) break;
    got = true;
    line += (char)c;
    if (c == '\n') break;
  }
  return got;
}

// Laedt eine per Punkt 5 gesicherte Datei zurueck und ERSETZT damit
// komplett den aktuellen Scan-Zustand (clients_known[]/aps_known[]).
// "last seen" wird aus dem gespeicherten Alter wieder in einen
// last_heard-Zeitstempel relativ zu "jetzt" umgerechnet, damit die
// Anzeige plausibel weiterlaeuft.
bool load_scenario_file(const char* filename)
{
  led_force_off();  // NEU 2.17.6: zeitkritisch (Dateitransfer/-lesen) - Status-LED aus
  char path[40];
  snprintf_P(path, sizeof(path), PSTR("/%s.txt"), filename);  // WICHTIG: .txt anhängen!
  File f = LittleFS.open(path, "r");
  if (!f) {
    Serial.println(F(" Fehler: Datei konnte nicht geoeffnet werden."));
    return false;
  }

  bool compressed = scenario_is_compressed_file(f);
  uint8_t *decode_window = NULL;
  ScenarioDecoder decoder;
  ScenarioLineReader reader;
  reader.file = &f;
  reader.decoder = &decoder;
  reader.compressed = compressed;
  if (compressed) {
    decode_window = (uint8_t*)malloc(SCENARIO_LZSS_WINDOW);
    if (!decode_window) {
      f.close();
      Serial.println(F(" Fehler: 2-KB-Dekompressionsfenster konnte nicht reserviert werden."));
      return false;
    }
    scenario_decoder_init(decoder, f, decode_window);
  }

  clients_known_count = 0;
  aps_known_count = 0;
  roaming_pair_count = 0;  // BUGFIX 2.30.61: alte Paare sonst falschen, neu geladenen APs zugeordnet
  memset(timewatch_state, 0, sizeof(timewatch_state));  // NEU 2.30.67
  for (int i = 0; i < MAX_CLIENTS_TRACKED; i++) prev_shown_rssi[i] = -128;

  uint64_t now = effective_now();
  int loaded_clients = 0, loaded_aps = 0, skipped = 0;
  bool in_settings_section = false;

  // NEU 2.29.13 BUGFIX: Zwei Durchlaeufe statt einem - zuerst ALLE BEACON-
  // Zeilen (echte, damals gesicherte APs), danach erst die DEVICE-Zeilen.
  // Vorher wurde bei einer DEVICE-Zeile ohne (in der Datei noch nicht
  // gelesene) passende BEACON-Zeile per ensure_ap_index() sofort ein
  // Platzhalter angelegt - das ist beim LIVE-Scan sinnvoll (der echte
  // Beacon kommt normalerweise Millisekunden spaeter), aber im Offline-
  // Zustand nach dem Laden einer Datei kommt NIE mehr ein Beacon nach: der
  // Platzhalter blieb dauerhaft "...wartet auf Beacon" und blaehte die
  // AP-Liste mit Eintraegen fuer jede BSSID auf, die in der Datei nur per
  // Client-/Datenframe auftauchte, aber nie einen eigenen BEACON-Eintrag
  // hatte (z.B. 100 statt der tatsaechlich gesicherten 54 APs). Erst wenn
  // nach dem vollstaendigen ersten Durchlauf feststeht, welche APs die
  // Datei wirklich enthaelt, werden im zweiten Durchlauf die DEVICE-Zeilen
  // aufgeloest - ohne Platzhalter zu erzeugen: findet sich keine passende
  // BSSID, bekommt der Client AP_IDX_NONE (genau wie vor 2.29.11 als "??"
  // sichtbar), statt einen Phantom-AP zu erzeugen.

  // --- Durchlauf 1: nur BEACON-Zeilen ---
  scenario_reader_reset(reader);
  while (true) {
    String line;
    if (!scenario_reader_read_line(reader, line)) break;
    line.trim();
    yield();
    if (! line.startsWith("BEACON: ")) continue;

    int bracket1 = line.indexOf('[');
    int bracket2 = line.indexOf(']', bracket1);
    if (bracket1 < 0 || bracket2 < 0) { skipped++; continue; }

    String ssid = line.substring(bracket1 + 1, bracket2);
    ssid.trim();
    String rest = line.substring(bracket2 + 1);
    rest.trim();
    if (rest.length() < 12) { skipped++; continue; }
    String bssidhex = rest.substring(0, 12);
    String nums = rest.substring(12);

    int channel = 0, age = 0, reported = 0, rssi = 0;
    sscanf(nums.c_str(), "%d %d %d %d", &channel, &age, &reported, &rssi);

    beaconinfo bi;
    memset(&bi, 0, sizeof(bi));
    bi.ssid_len = ssid.length();
    ssid.toCharArray((char*)bi.ssid, 33);
    parse_mac_hex(bssidhex.c_str(), bi.bssid);
    bi.channel = channel;
    bi.err = 0;
    bi.rssi = rssi;
    // NEU 2.21.1 OPTIMIZATION: Entfernt (nicht genutzt): bi.capa, bi.header
    bi.last_heard = (uint32_t)(now - (uint64_t)age);
    // NEU 2.29.10: Sicherheitsnetz - falls dieser Wert (durch sehr alte
    // Sicherungsdateien o.ae.) zufaellig exakt dem Frei-Slot-Marker
    // entspricht, um 1 verschieben, damit der geladene AP nicht faelschlich
    // als freier Slot gilt.
    if (bi.last_heard == AP_SLOT_FREE_MARKER) bi.last_heard--;
    bi.reported = (uint8_t) reported;

    // Doppelter BEACON-Eintrag fuer dieselbe BSSID in der Datei (sollte
    // normalerweise nicht vorkommen) - neuesten Stand behalten statt
    // einen zweiten Eintrag anzulegen.
    int existing = find_ap_index_by_bssid(bi.bssid);
    if (existing >= 0) {
      aps_known[existing] = bi;
    } else {
      if (aps_known_count >= MAX_APS_TRACKED) { skipped++; continue; }
      aps_known[aps_known_count] = bi;
      aps_known_count++;
    }
    loaded_aps++;
  }

  // --- Durchlauf 2: DEVICE-Zeilen und # SETTINGS ---
  scenario_reader_reset(reader);
  in_settings_section = false;
  while (true) {
    String line;
    if (!scenario_reader_read_line(reader, line)) break;
    line.trim();
    yield();

    if (line.startsWith("DEVICE: ")) {
      if (clients_known_count >= MAX_CLIENTS_TRACKED) { skipped++; continue; }
      int arrow = line.indexOf("==>");
      int bracket1 = line.indexOf('[', arrow);
      int bracket2 = line.indexOf(']', bracket1);
      if (arrow < 0 || bracket1 < 0 || bracket2 < 0) { skipped++; continue; }

      String stationhex = line.substring(8, 20);  // nach "DEVICE: " (8 Zeichen)
      String rest = line.substring(bracket2 + 1);
      rest.trim();
      if (stationhex.length() < 12 || rest.length() < 12) { skipped++; continue; }
      String bssidhex = rest.substring(0, 12);
      String nums = rest.substring(12);

      int channel = 0, age = 0, reported = 0, rssi = 0;
      sscanf(nums.c_str(), "%d %d %d %d", &channel, &age, &reported, &rssi);

      uint8_t ap_mac[ETH_MAC_LEN];
      parse_mac_hex(bssidhex.c_str(), ap_mac);
      // NEU 2.29.13: Durchlauf 1 hat bereits ALLE in der Datei vorhandenen
      // BEACON-Eintraege geladen, ein Treffer hier oder keiner ist also
      // endgueltig - kein Platzhalter (siehe NEU 2.29.16, Rueckbau des
      // Platzhalter-Mechanismus).
      int found_idx = is_valid_ap_bssid(ap_mac) ? find_ap_index_by_bssid(ap_mac) : -1;
      uint8_t ap_idx = (found_idx >= 0) ? (uint8_t) found_idx : AP_IDX_NONE;

      clientinfo ci;
      parse_mac_hex(stationhex.c_str(), ci.station);
      ci.ap_idx = ap_idx;
      // NEU 2.21.1 OPTIMIZATION: Entfernt (nicht genutzt): ci.ap, ci.seq_n, ci.header
      ci.channel = channel;
      ci.err = 0;
      ci.rssi = rssi;
      ci.last_heard = (uint32_t)(now - (uint64_t)age);
      ci.reported = (uint8_t) reported;

      clients_known[clients_known_count] = ci;
      clients_known_count++;
      loaded_clients++;

    } else if (line.startsWith("BEACON: ")) {
      continue;  // schon in Durchlauf 1 verarbeitet

    } else if (line == "# SETTINGS") {
      in_settings_section = true;

    } else if (in_settings_section && line.indexOf('=') > 0) {
      int eq = line.indexOf('=');
      String key = line.substring(0, eq);
      int val = line.substring(eq + 1).toInt();
      if (key == "sort_field") current_sort_field = (SortField) val;
      else if (key == "sort_ascending") sort_ascending = (val != 0);
      else if (key == "ap_sort_field") current_ap_sort_field = (ApSortField) val;
      else if (key == "ap_sort_ascending") ap_sort_ascending = (val != 0);
      else if (key == "list_refresh_sec") list_refresh_sec = val;
      else if (key == "rssi_trend_threshold") rssi_trend_threshold = val;
      else if (key == "two_col_threshold_devices") two_col_threshold_devices = val;
      else if (key == "two_col_threshold_ssids") two_col_threshold_ssids = val;
    }
  }
  if (decode_window) free(decode_window);
  f.close();

  Serial.printf_P(PSTR(" Geladen: %d Clients, %d Access Points"), loaded_clients, loaded_aps);
  if (skipped > 0) Serial.printf_P(PSTR("  (%d Zeilen uebersprungen/Platz voll)"), skipped);
  Serial.println(in_settings_section ? " (inkl. gespeicherter Einstellungen)" : " (alte Datei ohne Einstellungsblock - aktuelle Einstellungen bleiben)");
  return true;
}

// Zeigt Gesamt-/belegten/freien LittleFS-Speicherplatz an
#define SETTINGS_FILE "/settings.cfg"

// Aktualisiert NUR einen einzelnen Schluessel in der Einstellungsdatei,
// laesst alle anderen dort bereits gespeicherten Werte unangetastet.
// Fuer Einstellungen, die sofort automatisch gesichert werden sollen
// (Start-Modus, Logo an/aus), damit nicht versehentlich auch andere,
// gerade nur im RAM geaenderte Einstellungen mit gespeichert werden.
void save_single_setting(const char* key, int value)
{
  String content = "";
  if (LittleFS.exists(SETTINGS_FILE)) {
    File f = LittleFS.open(SETTINGS_FILE, "r");
    while (f.available()) {
      String line = f.readStringUntil('\n');
      line.trim();
      if (line.length() == 0) continue;
      int eq = line.indexOf('=');
      if (eq > 0 && line.substring(0, eq) == key) continue;  // alte Zeile verwerfen
      content += line + "\n";
    }
    f.close();
  }
  content += String(key) + "=" + String(value) + "\n";

  File fw = LittleFS.open(SETTINGS_FILE, "w");
  if (fw) {
    fw.print(content);
    fw.close();
  }
}

// Speichert ALLE aktuellen Einstellungen auf einmal (ueberschreibt die
// Datei komplett) - wird nur ueber den expliziten Menuepunkt
// "Einstellungen speichern" ausgeloest, nicht automatisch.
void save_all_settings()
{
  ram_debug_sample(RDP_LITTLEFS);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
  CallChainGuard __cc_guard(RDP_LITTLEFS);  // NEU 2.30.35: Call-Chain-Erweiterung
  File f = LittleFS.open(SETTINGS_FILE, "w");
  if (!f) {
    Serial.println(F(" Fehler beim Speichern der Einstellungen."));
    return;
  }
  f.printf_P(PSTR("sort_field=%d\r\n"), (int)current_sort_field);
  f.printf_P(PSTR("sort_ascending=%d\r\n"), sort_ascending ? 1 : 0);
  f.printf_P(PSTR("ap_sort_field=%d\r\n"), (int)current_ap_sort_field);
  f.printf_P(PSTR("ap_sort_ascending=%d\r\n"), ap_sort_ascending ? 1 : 0);
  f.printf_P(PSTR("status_led_pin=%d\r\n"), status_led_pin);
  f.printf_P(PSTR("status_led_active_low=%d\r\n"), status_led_active_low ? 1 : 0);
  // NEU 2.21.0: Signalisierungspin Config speichern
  f.printf_P(PSTR("signal_pin=%d\r\n"), signal_pin);
  f.printf_P(PSTR("signal_enabled=%d\r\n"), signal_enabled ? 1 : 0);
  f.printf_P(PSTR("signal_active_low=%d\r\n"), signal_active_low ? 1 : 0);
  // NEU 2.30.15: Rueckkehr-Signalisierung (Menue 4, Taste 'p') war bisher
  // reine Session-Variable - jetzt persistiert, auf Nutzerwunsch.
  f.printf_P(PSTR("enable_return_pulse=%d\r\n"), enable_return_pulse ? 1 : 0);
  f.printf_P(PSTR("list_refresh_sec=%d\r\n"), list_refresh_sec);
  f.printf_P(PSTR("rssi_trend_threshold=%d\r\n"), rssi_trend_threshold);
  f.printf_P(PSTR("two_col_threshold_devices=%d\r\n"), two_col_threshold_devices);
  f.printf_P(PSTR("two_col_threshold_ssids=%d\r\n"), two_col_threshold_ssids);
  f.printf_P(PSTR("color_enabled=%d\r\n"), color_enabled ? 1 : 0);
  f.printf_P(PSTR("startup_online=%d\r\n"), startup_online ? 1 : 0);
  f.printf_P(PSTR("show_logo=%d\r\n"), show_logo ? 1 : 0);
  f.printf_P(PSTR("notif_enabled=%d\r\n"), notif_enabled ? 1 : 0);
  f.printf_P(PSTR("notif_wifi_ssid=%s\r\n"), notif_wifi_ssid);
  f.printf_P(PSTR("notif_wifi_pass=%s\r\n"), notif_wifi_pass);
  f.printf_P(PSTR("notif_channel=%s\r\n"), notif_channel);
  f.printf_P(PSTR("notif_header_text=%s\r\n"), notif_header_text);  // NEU 2.20.1 FEATURE 5
  f.printf_P(PSTR("notif_interval_min=%d\r\n"), notif_interval_min);
  f.printf_P(PSTR("notif_content_mode=%d\r\n"), notif_content_mode);
  f.printf_P(PSTR("notif_ssid_filter=%s\r\n"), notif_ssid_filter);
  f.printf_P(PSTR("auto_save_on_overflow=%d\r\n"), auto_save_on_overflow ? 1 : 0);
  f.printf_P(PSTR("auto_offline_on_overflow=%d\r\n"), auto_offline_on_overflow ? 1 : 0);
  f.printf_P(PSTR("ntp_enabled=%d\r\n"), ntp_enabled ? 1 : 0);
  f.printf_P(PSTR("ntp_wifi_ssid=%s\r\n"), ntp_wifi_ssid);
  f.printf_P(PSTR("ntp_wifi_pass=%s\r\n"), ntp_wifi_pass);
  f.printf_P(PSTR("ntp_server=%s\r\n"), ntp_server);
  // NEU 2.12.0: Timezone speichern, NEU 2.17.8: dst_enabled statt ntp_use_mesz
  f.printf_P(PSTR("ntp_timezone_hours=%d\r\n"), ntp_timezone_hours);
  f.printf_P(PSTR("dst_enabled=%d\r\n"), dst_enabled ? 1 : 0);
  f.printf_P(PSTR("auto_save_enabled=%d\r\n"), auto_save_enabled ? 1 : 0);
  // NEU 2.13.0: Channel-Filter und Dwell-Zeit speichern
  f.printf_P(PSTR("channel_filter=%s\r\n"), channel_filter);
  f.printf_P(PSTR("channel_dwell_ms=%u\r\n"), channel_dwell_ms);
  // NEU 2.16.0: Auto-Load Dateiname speichern
  f.printf_P(PSTR("autoload_filename=%s\r\n"), autoload_filename);
  f.printf_P(PSTR("scenario_compression_enabled=%d\r\n"), scenario_compression_enabled ? 1 : 0);
  // NEU 2.29.0: ADC-Kalibrierung speichern
  f.printf_P(PSTR("adc_calib_raw=%d\r\n"), adc_calib_raw);
  f.printf_P(PSTR("adc_calib_mv=%d\r\n"), adc_calib_mv);
  // NEU 2.30.5: AP-Modus speichern
  f.printf_P(PSTR("ap_mode_enabled=%d\r\n"), ap_mode_enabled ? 1 : 0);
  f.printf_P(PSTR("ap_mode_ssid=%s\r\n"), ap_mode_ssid);
  f.printf_P(PSTR("ap_mode_pass=%s\r\n"), ap_mode_pass);
  f.close();
  Serial.println(F(" Einstellungen gespeichert."));
}

// Wird beim Boot aufgerufen. Existiert die Datei noch nicht (Erst-
// installation), bleiben einfach die Standardwerte aktiv.
void load_all_settings()
{
  if (!LittleFS.exists(SETTINGS_FILE)) return;
  File f = LittleFS.open(SETTINGS_FILE, "r");
  if (!f) return;
  while (f.available()) {
    String line = f.readStringUntil('\n');
    line.trim();
    int eq = line.indexOf('=');
    if (eq <= 0) continue;
    String key = line.substring(0, eq);
    String valstr = line.substring(eq + 1);
    int val = valstr.toInt();
    if (key == "sort_field") current_sort_field = (SortField) val;
    else if (key == "sort_ascending") sort_ascending = (val != 0);
    else if (key == "ap_sort_field") current_ap_sort_field = (ApSortField) val;
    else if (key == "ap_sort_ascending") ap_sort_ascending = (val != 0);
    else if (key == "status_led_pin") status_led_pin = val;
    else if (key == "status_led_active_low") status_led_active_low = (val != 0);
    // NEU 2.21.0: Signalisierungspin Config laden
    else if (key == "signal_pin") signal_pin = val;
    else if (key == "signal_enabled") signal_enabled = (val != 0);
    else if (key == "signal_active_low") signal_active_low = (val != 0);
    // NEU 2.30.15: siehe Kommentar bei save_all_settings()
    else if (key == "enable_return_pulse") enable_return_pulse = (val != 0);
    else if (key == "list_refresh_sec") list_refresh_sec = val;
    else if (key == "rssi_trend_threshold") rssi_trend_threshold = val;
    else if (key == "two_col_threshold_devices") two_col_threshold_devices = val;
    else if (key == "two_col_threshold_ssids") two_col_threshold_ssids = val;
    else if (key == "color_enabled") color_enabled = (val != 0);
    else if (key == "startup_online") startup_online = (val != 0);
    else if (key == "show_logo") show_logo = (val != 0);
    else if (key == "notif_enabled") notif_enabled = (val != 0);
    else if (key == "notif_wifi_ssid") valstr.toCharArray(notif_wifi_ssid, 33);
    else if (key == "notif_wifi_pass") valstr.toCharArray(notif_wifi_pass, 65);
    else if (key == "notif_channel") valstr.toCharArray(notif_channel, 24);  // NEU 2.17.9
    else if (key == "notif_header_text") valstr.toCharArray(notif_header_text, 33);  // NEU 2.20.1 FEATURE 5
    else if (key == "notif_interval_min") notif_interval_min = (val < 1) ? 1 : val;
    else if (key == "notif_content_mode") notif_content_mode = val;
    else if (key == "notif_ssid_filter") valstr.toCharArray(notif_ssid_filter, 64);  // NEU 2.17.9
    else if (key == "auto_save_on_overflow") auto_save_on_overflow = (val != 0);
    else if (key == "auto_offline_on_overflow") auto_offline_on_overflow = (val != 0);
    else if (key == "ntp_enabled") ntp_enabled = (val != 0);
    else if (key == "ntp_wifi_ssid") valstr.toCharArray(ntp_wifi_ssid, 33);
    else if (key == "ntp_wifi_pass") valstr.toCharArray(ntp_wifi_pass, 65);
    else if (key == "ntp_server") valstr.toCharArray(ntp_server, 65);
    // NEU 2.12.0: Timezone und Auto-Save laden
    else if (key == "ntp_timezone_hours") ntp_timezone_hours = val;
    else if (key == "dst_enabled") dst_enabled = (val != 0);
    // NEU 2.17.8: Kompatibilitaet mit alten settings.cfg-Dateien (vor der
    // Umbenennung MESZ -> Daylight Saving Time)
    else if (key == "ntp_use_mesz") dst_enabled = (val != 0);
    else if (key == "auto_save_enabled") auto_save_enabled = (val != 0);
    // NEU 2.13.0: Channel-Filter und Dwell-Zeit laden
    else if (key == "channel_filter") valstr.toCharArray(channel_filter, 32);  // NEU 2.17.9
    else if (key == "channel_dwell_ms") channel_dwell_ms = val;
    // NEU 2.16.0: Auto-Load Dateiname laden
    else if (key == "autoload_filename") valstr.toCharArray(autoload_filename, 32);  // NEU 2.17.9
    else if (key == "scenario_compression_enabled") scenario_compression_enabled = (val != 0);
    // NEU 2.29.0: ADC-Kalibrierung laden
    else if (key == "adc_calib_raw") adc_calib_raw = (uint16_t)val;
    else if (key == "adc_calib_mv") adc_calib_mv = (uint16_t)val;
    // NEU 2.30.5: AP-Modus laden
    else if (key == "ap_mode_enabled") ap_mode_enabled = (val != 0);
    else if (key == "ap_mode_ssid") valstr.toCharArray(ap_mode_ssid, 33);
    else if (key == "ap_mode_pass") valstr.toCharArray(ap_mode_pass, 65);
  }
  f.close();
}

void print_fs_info()
{
  FSInfo info;
  if (LittleFS.info(info)) {
    unsigned free_bytes = (unsigned)(info.totalBytes - info.usedBytes);
    // NEU 2.30.45 (Anwenderwunsch): absoluter freier Speicher statt Prozent-
    // Anzeige, mit Tausenderpunkten (wie an anderen Stellen im Programm).
    Serial.printf_P(PSTR(" Speicher: %s Byte frei\r\n"), format_number_with_dots(free_bytes));
  } else {
    Serial.println(F(" Speicherinfo nicht verfuegbar."));
  }
}

void menu_enter_save_filename()
{
  menu_state = STATE_SAVE_FILENAME;
  save_filename_len = 0;
  save_filename_buf[0] = '\0';
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" Aktuelle Listen speichern"));
  Serial.println(F("======================================================="));
  print_fs_info();
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Dateiname eingeben (Buchstaben/Zahlen/_/-, max. 24"));
  Serial.println(F(" Zeichen, ohne Endung), Enter = speichern."));
  Serial.println(F(" Backspace bei leerem Namen/ESC = abbrechen."));
  Serial.print(F(" Name: "));
  if (offline_banner_will_print()) Serial.println();  // BUGFIX 2.30.44
}

static void scenario_print_file_content(const char *path)
{
  File f = LittleFS.open(path, "r");
  if (!f) {
    Serial.println(F(" Datei konnte nicht geoeffnet werden."));
    return;
  }
  if (!scenario_is_compressed_file(f)) {
    while (f.available()) {
      Serial.write(f.read());
      yield();
    }
    f.close();
    return;
  }

  uint8_t *window = (uint8_t*)malloc(SCENARIO_LZSS_WINDOW);
  if (!window) {
    Serial.println(F(" Datei ist komprimiert, aber das 2-KB-Dekompressionsfenster konnte nicht reserviert werden."));
    f.close();
    return;
  }
  ScenarioDecoder decoder;
  f.seek(4);
  scenario_decoder_init(decoder, f, window);
  int c;
  while ((c = scenario_read_decompressed_byte(decoder)) >= 0) {
    Serial.write((uint8_t)c);
    if ((c & 0x3F) == 0) yield();
  }
  free(window);
  f.close();
}

void menu_enter_file_list()
{
  ram_debug_sample(RDP_FILE_LIST);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
  CallChainGuard __cc_guard(RDP_FILE_LIST);  // NEU 2.30.35: Call-Chain-Erweiterung
  menu_state = STATE_FILE_LIST;
  file_input_len = 0;
  file_delete_mode = false;
  file_load_mode = false;
  file_send_mode = false;
  file_view_waiting = false;
  file_protect_mode = false;  // NEU 2.25.0: File Protection Mode zurücksetzen
  file_protect_input_len = 0;
  
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  // NEU 2.30.45 (Anwenderwunsch): Gesamtzahl ALLER tatsaechlich vorhandenen
  // Dateien (inkl. geschuetzter/versteckter) in der Kopfzeile - unabhaengig
  // von der Anzeigebegrenzung (max. 20 Zeilen) und vom "h"-Toggle weiter
  // unten, der nur die SICHTBARKEIT in der Liste steuert.
  int total_file_count = 0;
  {
    Dir count_dir = LittleFS.openDir("/");
    while (count_dir.next()) total_file_count++;
  }
  Serial.println(F("======================================================="));
  Serial.printf_P(PSTR(" Gespeicherte Dateien %d\r\n"), total_file_count);
  Serial.println(F("======================================================="));
  print_fs_info();
  
  // NEU 2.25.0: Hinweis wenn Systemdateien ausgeblendet sind
  if (protected_count > 0 && !show_hidden) {
    Serial.println(F(" [Geschuetzte Dateien ausgeblendet]"));
  }
  Serial.println(F("-------------------------------------------------------"));

  file_list_count = 0;
  Dir dir = LittleFS.openDir("/");
  while (dir.next() && file_list_count < 32) {
    String fn = dir.fileName();
    if (fn.length() > 0 && fn[0] == '/') {
      fn = fn.substring(1);  // LittleFS liefert (wie zuvor SPIFFS) oft "/name.txt" statt "name.txt"
    }
    
    // NEU 2.25.0: Prüfe ob Datei geschützt und ausgeblendet werden soll
    bool protected_flag = is_file_protected(fn.c_str());
    if (protected_flag && !show_hidden) {
      continue;  // Überspringe diese Datei wenn geschützt und verborgen
    }
    
    fn.toCharArray(file_list_names[file_list_count], 32);  // NEU 2.20.0: 28 → 32 für volle Array-Größe!
    
    // NEU 2.25.0: Zeige [PROTECTED] Label wenn Datei geschützt
    char display_name[64]; strncpy(display_name,fn.c_str(),sizeof(display_name)-1); display_name[sizeof(display_name)-1]=0;
    size_t dnlen=strlen(display_name);
    if(dnlen>=4 && strcmp(display_name+dnlen-4,".txt")==0) display_name[dnlen-4]='\0';
    char decoded_time[24];
    bool has_timestamp=parse_file_timestamp(fn.c_str(),decoded_time,sizeof(decoded_time));
    char sizebuf[16]; strncpy(sizebuf,format_number_with_dots((uint32_t)dir.fileSize()),sizeof(sizebuf)-1); sizebuf[sizeof(sizebuf)-1]='\0';
    if(protected_flag) {
      Serial.printf_P(PSTR("%2d) %-26.26s  %7s Byte  [PROTECTED]\r\n"),file_list_count,display_name,sizebuf);
    } else {
      Serial.printf_P(PSTR("%2d) %-26.26s  %7s Byte\r\n"),file_list_count,display_name,sizebuf);
    }
    if(has_timestamp) Serial.printf_P(PSTR("       (%s)\r\n"),decoded_time);
    file_list_count++;
  }
  if (file_list_count == 0) {
    Serial.println(F(" (keine Dateien vorhanden)"));
  }
  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Zahl+Enter = Inhalt anzeigen"));
  Serial.println(F(" d+Zahl+Enter = loeschen"));
  Serial.println(F(" l+Zahl+Enter = als aktiven Scan-Zustand laden."));
  Serial.println(F(" s+Zahl+Enter = Datei per ntfy versenden"));
  Serial.println(F(" h = Geschuetzte Dateien anzeigen / ausblenden"));  // NEU 2.25.0
  Serial.println(F(" h+Zahl+Enter = Dateischutz ein/aus"));  // NEU 2.25.0
  Serial.println(F(" Backspace/ESC = zurueck zum Menue"));
  Serial.print(F(" Auswahl: "));
  if (offline_banner_will_print()) Serial.println();  // BUGFIX 2.30.44: siehe Kommentar bei offline_banner_will_print()
}

// ===================== HTTP-Datei-Server (Punkt 7, NEU 2.30.0) =====================
//
// Gesamtes Konzept siehe Changelog-Eintrag Version 2.30.0 am Dateianfang.
// Kurzfassung der Risikominimierung:
//  - g_http_server existiert nur waehrend Punkt 7 aktiv ist (new/delete).
//  - WLAN-Verbindungsaufbau/-abbau und Promiscuous-Mode-Steuerung sind
//    1:1 aus sync_ntp_time()/notif_send_now() uebernommen (dieselbe
//    vollstaendige Befehlsreihenfolge), da genau diese Stellen in der
//    Vergangenheit schon Probleme gemacht hatten, wenn sie verkuerzt
//    wurden.
//  - Alle Dateiuebertragungen sind gestreamt, es wird nie eine komplette
//    Datei im RAM gehalten.

// Liefert den passenden Content-Type anhand der Dateiendung. Nur fuer die
// Anzeige/Uebertragung relevant, keine Sicherheitsfunktion.
static const char http_ct_jpeg[] PROGMEM = "image/jpeg";
static const char http_ct_png[] PROGMEM = "image/png";
static const char http_ct_txt[] PROGMEM = "text/plain";
static const char http_ct_html[] PROGMEM = "text/html";
static const char http_ct_octet[] PROGMEM = "application/octet-stream";

const char* http_content_type_for(const String& filename)
{
  static char buf[32];
  PGM_P src = http_ct_octet;
  if (filename.endsWith(".jpg") || filename.endsWith(".jpeg")) src = http_ct_jpeg;
  else if (filename.endsWith(".png")) src = http_ct_png;
  else if (filename.endsWith(".txt")) src = http_ct_txt;
  else if (filename.endsWith(".html") || filename.endsWith(".htm")) src = http_ct_html;
  strncpy_P(buf, src, sizeof(buf) - 1);
  buf[sizeof(buf) - 1] = '\0';
  return buf;
}

// Liest den Query-Parameter "f" (Dateiname), entfernt einen evtl. schon
// vorhandenen fuehrenden "/" und weist alles mit "." oder "/" darin
// zurueck (Schutz vor Pfad-Traversal / Zugriff auf Unterordner - LittleFS
// auf dem ESP8266 kennt ohnehin keine echten Unterordner, aber so bleibt
// der Parameter garantiert ein einfacher Dateiname). Leerer String bei
// ungueltiger/fehlender Angabe.
String http_get_safe_filename()
{
  if (!g_http_server->hasArg("f")) return "";
  String fn = g_http_server->arg("f");
  if (fn.length() == 0 || fn.length() > 31) return "";
  if (fn[0] == '/') fn = fn.substring(1);
  if (fn.indexOf('/') >= 0 || fn.indexOf("..") >= 0) return "";
  return fn;
}

// Fuegt, falls /banner.jpg im Flash liegt, ein Banner-Bild am Seitenanfang
// ein. Wird auf allen Seiten AUSSER der Startseite aufgerufen.
void http_send_banner_if_present()
{
  if (LittleFS.exists("/banner.jpg")) {
    // BUGFIX 2.30.9: "margin:0 auto" zentrierte den Banner innerhalb des
    // 600px-Containers, waehrend Ueberschrift/Tabelle darunter (ganz normale
    // Block-Elemente, kein eigenes Alignment) linksbuendig am Container-Rand
    // stehen. Ist der Banner schmaler als der Container, rueckt er dadurch
    // sichtbar nach rechts ein - Banner und restliche Ausgabe liegen dann
    // NICHT auf derselben linken Kante ("gegeneinander verschoben"). Fix:
    // Banner jetzt genauso linksbuendig wie alles andere (kein auto-Margin
    // mehr), damit alle Elemente dieselbe linke Kante teilen.
    g_http_server->sendContent(F("<img src=\"/banner.jpg\" style=\"max-width:100%;display:block;margin:0 0 12px 0;\"><br>\r\n"));
  }
}

// NEU 2.30.4 RAM-FIX: Jede Antwort schliesst die Verbindung explizit statt
// sie (HTTP/1.1-Standard) offen zu halten. ESP8266WebServer haelt bei
// Keep-Alive pro Client zusaetzliche TCP-Strukturen im RAM, die sich bei
// mehreren aufeinanderfolgenden Seitenaufrufen (Seite laden, Bild laden,
// Upload starten...) aufsummieren koennen, bevor der Browser die
// Verbindung von sich aus schliesst. Mit "Connection: close" gibt der
// ESP8266 die Verbindung nach jeder Antwort sofort wieder frei - bei so
// knappem Heap wichtiger als der (minimale) Geschwindigkeitsvorteil von
// Keep-Alive.
void http_close_after_response()
{
  g_http_server->sendHeader("Connection", "close");
}

// "/" - Startseite. Zeigt /hlogo.jpg (falls vorhanden) und wartet per
// JavaScript auf einen beliebigen Tastendruck ODER Klick/Touch, bevor sie
// zu "/dateien" weiterschaltet. Ohne hlogo.jpg wird sofort weitergeleitet.
void http_handle_root()
{
  http_close_after_response();
  if (!LittleFS.exists("/hlogo.jpg")) {
    g_http_server->sendHeader("Location", "/dateien");
    g_http_server->send(302, "text/plain", "");
    return;
  }
  // BUGFIX 2.30.1: setContentLength(CONTENT_LENGTH_UNKNOWN) VOR send()
  // ist zwingend noetig, wenn der Seiteninhalt per sendContent() gestreamt
  // wird (nicht komplett als ein String an send() uebergeben wird). Ohne
  // das setzt send(200, "text/html", "") den Content-Length-Header auf 0
  // (weil der uebergebene Body-String leer ist) - der Browser liest dann
  // genau 0 Byte und zeigt eine leere weisse Seite, obwohl der Server ueber
  // die nachfolgenden sendContent()-Aufrufe brav weitere Daten schickt.
  // Mit CONTENT_LENGTH_UNKNOWN schaltet der Server stattdessen auf Chunked
  // Transfer Encoding um, wodurch beliebig viele sendContent()-Aufrufe nach
  // send() folgen duerfen.
  g_http_server->setContentLength(CONTENT_LENGTH_UNKNOWN);
  g_http_server->send(200, "text/html", "");
  g_http_server->sendContent(F(
    "<!DOCTYPE html><html><head><meta charset=\"utf-8\">"
    "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
    "<title>WiFi-Monitor</title>"
    "<style>html,body{height:100%;height:100dvh;margin:0;background:#111;overflow:hidden;}"
    "body{display:flex;align-items:center;justify-content:center;}"
    // BUGFIX 2.30.9: reines 100vh/100vw beruecksichtigt auf vielen mobilen
    // Browsern NICHT die ein-/ausblendende Adressleiste - die sichtbare
    // Hoehe/Breite aendert sich, 100vh aber bleibt auf dem urspruenglichen
    // (zu grossen) Wert stehen, wodurch sich das Logo nicht sauber an die
    // tatsaechliche Bildschirmgroesse anpasst. dvh/dvw ("dynamic viewport")
    // loest genau das, wird aber von aelteren Browsern nicht verstanden -
    // deshalb zuerst vh/vw als Fallback setzen (wird ignoriert, wo dvh/dvw
    // unterstuetzt wird) und dvh/dvw DANACH als Override angeben.
    "img{max-width:100vw;max-width:100dvw;max-height:100vh;max-height:100dvh;width:auto;height:auto;object-fit:contain;}"
    "</style></head><body>"
    "<img src=\"/hlogo.jpg\" alt=\"Logo\">"
    "<script>"
    "function weiter(){window.location='/dateien';}"
    "document.onkeydown=weiter;"
    "document.onclick=weiter;"
    "document.ontouchstart=weiter;"
    "</script></body></html>"));
}

// "/hlogo.jpg" bzw. "/banner.jpg" - liefert das jeweilige Bild direkt aus
// LittleFS aus (gestreamt, nicht komplett im RAM gepuffert). Existiert die
// Datei nicht, 404.
void http_handle_hlogo()
{
  http_close_after_response();
  File f = LittleFS.open("/hlogo.jpg", "r");
  if (!f) { g_http_server->send(404, "text/plain", "nicht gefunden"); return; }
  g_http_server->streamFile(f, "image/jpeg");
  f.close();
}
void http_handle_banner()
{
  http_close_after_response();
  File f = LittleFS.open("/banner.jpg", "r");
  if (!f) { g_http_server->send(404, "text/plain", "nicht gefunden"); return; }
  g_http_server->streamFile(f, "image/jpeg");
  f.close();
}

// "/dateien" - Dateiverwaltung: Liste, Download-/Loeschen-Links, Upload-
// Formular. Nutzt dieselbe Schutzliste (is_file_protected()) wie Punkt 6.
void http_handle_files_page()
{
  // BUGFIX 2.30.1: siehe ausfuehrlichen Kommentar in http_handle_root() -
  // ohne setContentLength(CONTENT_LENGTH_UNKNOWN) zeigt der Browser hier
  // eine leere weisse Seite, obwohl der Server die Daten sendet.
  http_close_after_response();
  g_http_server->setContentLength(CONTENT_LENGTH_UNKNOWN);
  g_http_server->send(200, "text/html", "");
  g_http_server->sendContent(F(
    "<!DOCTYPE html><html><head><meta charset=\"utf-8\">"
    "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
    "<title>WiFi-Monitor - Dateien</title>"
    "<style>body{font-family:sans-serif;max-width:600px;margin:0 auto;padding:8px;}"
    "table{width:100%;border-collapse:collapse;}td{padding:4px;border-bottom:1px solid #ccc;}"
    "a{margin-right:8px;}</style></head><body>"));
  http_send_banner_if_present();
  g_http_server->sendContent(F("<h3>Flashinhalt (WiFi-Monitor v" FIRMWARE_VERSION ")</h3><table>\r\n"));

  Dir dir = LittleFS.openDir("/");
  while (dir.next()) {
    String fn = dir.fileName();
    if (fn.length() > 0 && fn[0] == '/') fn = fn.substring(1);
    bool prot = is_file_protected(fn.c_str());
    String display_fn = fn;
    char decoded_time[24]; if(parse_file_timestamp(fn.c_str(),decoded_time,sizeof(decoded_time))) { int us=display_fn.lastIndexOf('_'); if(us>=0) display_fn=display_fn.substring(0,us)+" ("+decoded_time+")"; }
    g_http_server->sendContent(F("<tr><td>"));
    g_http_server->sendContent(display_fn);
    g_http_server->sendContent(F("</td><td>"));
    g_http_server->sendContent(String((unsigned)dir.fileSize()));
    g_http_server->sendContent(F(" Byte</td><td>"));
    g_http_server->sendContent(F("<a href=\"/download?f="));
    g_http_server->sendContent(fn);
    g_http_server->sendContent(F("\">Download</a>"));
    if (prot) {
      g_http_server->sendContent(F(" [geschuetzt]"));
    } else {
      g_http_server->sendContent(F("<a href=\"/delete?f="));
      g_http_server->sendContent(fn);
      g_http_server->sendContent(F("\" onclick=\"return confirm('Wirklich loeschen?');\">Loeschen</a>"));
    }
    g_http_server->sendContent(F("</td></tr>\r\n"));
  }
  g_http_server->sendContent(F(
    "</table><hr>"
    "<form method=\"POST\" action=\"/upload\" enctype=\"multipart/form-data\">"
    "<input type=\"file\" name=\"datei\"> "
    "<input type=\"submit\" value=\"Hochladen\"></form><hr>"
    "<p>Server ueber die serielle Konsole beenden (beliebige Taste), oder "
    "hier: <a href=\"/beenden\">Server beenden</a></p>"
    "</body></html>"));
}

// "/download?f=NAME" - liefert die Datei gestreamt zum Download aus.
void http_handle_download()
{
  http_close_after_response();
  String fn = http_get_safe_filename();
  if (fn.length() == 0) { g_http_server->send(400, "text/plain", "ungueltiger Dateiname"); return; }
  String path = "/" + fn;
  if (!LittleFS.exists(path)) { g_http_server->send(404, "text/plain", "nicht gefunden"); return; }
  File f = LittleFS.open(path, "r");
  g_http_server->sendHeader("Content-Disposition", "attachment; filename=\"" + fn + "\"");
  g_http_server->streamFile(f, http_content_type_for(fn));
  f.close();
}

// "/delete?f=NAME" - loescht eine Datei, respektiert die Schutzliste
// (dieselbe Pruefung wie serverseitig bei Punkt 6).
void http_handle_delete()
{
  http_close_after_response();
  String fn = http_get_safe_filename();
  if (fn.length() == 0) { g_http_server->send(400, "text/plain", "ungueltiger Dateiname"); return; }
  if (is_file_protected(fn.c_str())) {
    g_http_server->send(403, "text/plain", "Datei ist geschuetzt");
    return;
  }
  LittleFS.remove("/" + fn);
  g_http_server->sendHeader("Location", "/dateien");
  g_http_server->send(302, "text/plain", "");
}

// HTTPUpload-Callback: wird waehrend "POST /upload" mehrfach aufgerufen
// (START einmalig, WRITE mehrfach mit jeweils einem Chunk, END einmalig).
// Schreibt jeden Chunk sofort in die Zieldatei - es wird nie der komplette
// Uploadinhalt im RAM gehalten.
void http_handle_upload_data()
{
  ram_debug_sample(RDP_HTTP_DOWNLOAD);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
  CallChainGuard __cc_guard(RDP_HTTP_DOWNLOAD);  // NEU 2.30.35: Call-Chain-Erweiterung
  HTTPUpload& upload = g_http_server->upload();
  if (upload.status == UPLOAD_FILE_START) {
    g_http_upload_rejected = false;
    g_http_upload_reject_reason = "";
    uint32_t freeHeapNow = ESP.getFreeHeap();

    String fn = upload.filename;
    int slash = fn.lastIndexOf('/');
    if (slash >= 0) fn = fn.substring(slash + 1);
    if (fn.length() == 0 || fn.length() > 31) {
      g_http_upload_rejected = true;
      g_http_upload_reject_reason = "Ungueltiger Dateiname";
      return;
    }
    if (is_file_protected(fn.c_str())) {
      g_http_upload_rejected = true;
      g_http_upload_reject_reason = "Datei ist geschuetzt";
      return;
    }
    char upload_path[40]; String requested_upload_path = "/" + fn;
    strncpy(upload_path, requested_upload_path.c_str(), sizeof(upload_path)-1); upload_path[sizeof(upload_path)-1]=0;
    if (!make_collision_safe_path(upload_path, upload_path, sizeof(upload_path))) { g_http_upload_rejected = true; g_http_upload_reject_reason = "Kollisionsfreier Dateiname nicht verfuegbar"; return; }
    g_http_upload_file = LittleFS.open(upload_path, "w");
    if (!g_http_upload_file) {
      g_http_upload_rejected = true;
      g_http_upload_reject_reason = "Datei konnte nicht angelegt werden";
    }
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (!g_http_upload_rejected && g_http_upload_file) {
      g_http_upload_file.write(upload.buf, upload.currentSize);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (g_http_upload_file) g_http_upload_file.close();
  }
}

// Wird NACH vollstaendig abgeschlossenem Upload (http_handle_upload_data()
// durchlief UPLOAD_FILE_END) genau einmal aufgerufen, um dem Browser eine
// Antwort zu schicken.
void http_handle_upload_done()
{
  http_close_after_response();
  if (g_http_upload_rejected) {
    g_http_server->send(400, "text/plain", String("Upload abgelehnt: ") + g_http_upload_reject_reason);
    return;
  }
  g_http_server->sendHeader("Location", "/dateien");
  g_http_server->send(302, "text/plain", "");
}

// "/beenden" - Server ueber den Browser sauber beenden (Alternative zur
// seriellen Konsole).
void http_handle_stop_request()
{
  http_close_after_response();
  g_http_server->send(200, "text/html", "<html><body>Server wird beendet.</body></html>");
  // BUGFIX 2.30.5: siehe Kommentar bei g_http_stop_requested - hier NUR
  // das Flag setzen, http_server_stop() wird ausserhalb dieses Aufrufs
  // (in menu_periodic()) ausgefuehrt.
  g_http_stop_requested = true;
}

void http_handle_not_found()
{
  http_close_after_response();
  g_http_server->send(404, "text/plain", "nicht gefunden");
}

// Punkt 7: verbindet mit einem WLAN und startet den HTTP-Server. Zwei
// Varianten (NEU 2.30.5 - siehe Einstellungen > AP-Modus):
//  - ap_mode_enabled == false (Standard, unveraendertes Verhalten seit
//    v2.30.0): STA-Verbindung mit einem bestehenden Router, Zugangsdaten
//    aus den ntfy-Einstellungen (notif_wifi_ssid/notif_wifi_pass).
//  - ap_mode_enabled == true: eigener Access Point (ap_mode_ssid/
//    ap_mode_pass), kein bestehendes WLAN noetig.
void menu_enter_http_server()
{
  ram_debug_sample(RDP_HTTP_SERVER);  // NEU 2.30.34: passive RAM-/Stack-Diagnose
  CallChainGuard __cc_guard(RDP_HTTP_SERVER);  // NEU 2.30.35: Call-Chain-Erweiterung
  vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
  Serial.println(F("======================================================="));
  Serial.println(F(" HTTP-Datei-Server"));
  Serial.println(F("======================================================="));

  // Vollstaendiger Moduswechsel (OFF -> STA/AP), identisch im Prinzip zu
  // sync_ntp_time()/notif_send_now() - ein verkuerzter Wechsel hatte in
  // der Vergangenheit schon zu einem "tauben" Funkchip gefuehrt (siehe
  // dortige Kommentare).
  wifi_promiscuous_enable(disable);

  if (ap_mode_enabled) {
    // ---------------- Eigener Access Point ----------------
    if (ap_mode_pass[0] != '\0' && strlen(ap_mode_pass) < 8) {
      Serial.println(F(" FEHLER: AP-Passwort muss leer (offenes WLAN) oder"));
      Serial.println(F(" mindestens 8 Zeichen lang sein (WPA2-Minimum)."));
      Serial.println(F(" Bitte in Einstellungen > AP-Modus korrigieren."));
      delay(2500);
      wifi_promiscuous_enable(disable);
      delay(50);
      wifi_set_opmode(STATION_MODE);
      delay(50);
      wifi_set_channel(channel);
      delay(50);
      wifi_set_promiscuous_rx_cb(promisc_cb);
      wifi_promiscuous_enable(enable);
      nothing_new = 0;
      menu_state = STATE_MENU;
      menu_draw();
      return;
    }

    Serial.printf_P(PSTR(" Starte eigenen Access Point '%s' ...\r\n"), ap_mode_ssid);
    WiFi.mode(WIFI_OFF);
    delay(200);
    WiFi.mode(WIFI_AP);
    delay(100);
    bool apOk = (ap_mode_pass[0] != '\0') ? WiFi.softAP(ap_mode_ssid, ap_mode_pass)
                                           : WiFi.softAP(ap_mode_ssid);
    delay(200);

    if (!apOk) {
      Serial.println(F(" FEHLER: Access Point konnte nicht gestartet werden."));
      WiFi.softAPdisconnect(true);
      delay(100);
      wifi_promiscuous_enable(disable);
      delay(50);
      wifi_set_opmode(STATION_MODE);
      delay(50);
      wifi_set_channel(channel);
      delay(50);
      wifi_set_promiscuous_rx_cb(promisc_cb);
      wifi_promiscuous_enable(enable);
      nothing_new = 0;
      delay(2000);
      menu_state = STATE_MENU;
      menu_draw();
      return;
    }

    g_http_server_is_ap = true;
    Serial.println(F(" Access Point gestartet. Server laeuft:"));
    Serial.print(F("   WLAN: ")); Serial.println(ap_mode_ssid);
    Serial.print(F("   http://")); Serial.println(WiFi.softAPIP());

  } else {
    // ---------------- Bestehendes WLAN (STA) - unveraendert seit 2.30.0 ----------------
    if (notif_wifi_ssid[0] == '\0') {
      Serial.println(F(" FEHLER: Kein WLAN konfiguriert (Einstellungen > Benachrichtigung)."));
      Serial.println(F(" Alternativ: Einstellungen > AP-Modus aktivieren, dann ist kein"));
      Serial.println(F(" vorhandenes WLAN noetig."));
      delay(2500);
      wifi_promiscuous_enable(disable);
      delay(50);
      wifi_set_opmode(STATION_MODE);
      delay(50);
      wifi_set_channel(channel);
      delay(50);
      wifi_set_promiscuous_rx_cb(promisc_cb);
      wifi_promiscuous_enable(enable);
      nothing_new = 0;
      menu_state = STATE_MENU;
      menu_draw();
      return;
    }

    Serial.printf_P(PSTR(" Verbinde mit '%s' ...\r\n"), notif_wifi_ssid);
    WiFi.mode(WIFI_OFF);
    delay(200);
    WiFi.mode(WIFI_STA);
    delay(100);
    WiFi.begin(notif_wifi_ssid, notif_wifi_pass);

    uint32_t start = millis();
    bool connected = false;
    while (millis() - start < 15000) {
      if (WiFi.status() == WL_CONNECTED) { connected = true; break; }
      delay(200);
      yield();
    }

    if (!connected) {
      Serial.println(F(" FEHLER: WLAN-Verbindung fehlgeschlagen (Timeout nach 15s)."));
      WiFi.disconnect(true);
      delay(100);
      // Promiscuous-Mode trotz Fehlschlag vollstaendig wiederherstellen,
      // damit das Sniffing danach normal weiterlaeuft.
      wifi_promiscuous_enable(disable);
      delay(50);
      wifi_set_opmode(STATION_MODE);
      delay(50);
      wifi_set_channel(channel);
      delay(50);
      wifi_set_promiscuous_rx_cb(promisc_cb);
      wifi_promiscuous_enable(enable);
      nothing_new = 0;
      delay(2000);
      menu_state = STATE_MENU;
      menu_draw();
      return;
    }

    g_http_server_is_ap = false;
    Serial.println(F(" Verbunden. Server laeuft:"));
    Serial.print(F("   http://"));
    Serial.println(WiFi.localIP());
  }

  g_http_server = new ESP8266WebServer(80);
  g_http_server->on("/", HTTP_GET, http_handle_root);
  g_http_server->on("/hlogo.jpg", HTTP_GET, http_handle_hlogo);
  g_http_server->on("/banner.jpg", HTTP_GET, http_handle_banner);
  g_http_server->on("/dateien", HTTP_GET, http_handle_files_page);
  g_http_server->on("/download", HTTP_GET, http_handle_download);
  g_http_server->on("/delete", HTTP_GET, http_handle_delete);
  g_http_server->on("/beenden", HTTP_GET, http_handle_stop_request);
  g_http_server->on("/upload", HTTP_POST, http_handle_upload_done, http_handle_upload_data);
  g_http_server->onNotFound(http_handle_not_found);
  g_http_server->begin();

  menu_state = STATE_HTTP_SERVER;

  Serial.println(F("-------------------------------------------------------"));
  Serial.println(F(" Waehrend der Server laeuft, ist das Sniffing pausiert"));
  Serial.println(F(" (das WLAN-Funkmodul kann nicht beides gleichzeitig)."));
  Serial.println(F(" Beliebige Taste hier auf der Konsole = Server beenden."));
  Serial.println(F("======================================================="));
}

// Beendet den HTTP-Server, trennt das WLAN und stellt den Promiscuous-Mode
// vollstaendig wieder her (identische Befehlsreihenfolge wie beim Boot/
// nach sync_ntp_time()/notif_send_now()).
void http_server_stop()
{
  if (g_http_server != nullptr) {
    g_http_server->stop();
    delete g_http_server;
    g_http_server = nullptr;
  }
  // NEU 2.30.5: je nachdem, ob Punkt 7 als eigener AP oder als STA-Client
  // eines bestehenden WLANs lief, muss unterschiedlich abgebaut werden.
  if (g_http_server_is_ap) {
    WiFi.softAPdisconnect(true);
  } else {
    WiFi.disconnect(true);
  }
  delay(100);

  wifi_promiscuous_enable(disable);
  delay(50);
  wifi_set_opmode(STATION_MODE);
  delay(50);
  wifi_set_channel(channel);
  delay(50);
  wifi_set_promiscuous_rx_cb(promisc_cb);
  wifi_promiscuous_enable(enable);
  nothing_new = 0;

  menu_state = STATE_MENU;
  menu_draw();
}

// Wird bei Bedarf zurueck zum jeweils vorherigen Menue-Zustand aufgerufen
// (Backspace-Navigation)
void menu_go_back()
{
  switch (menu_state) {
    case STATE_LIVE:
      menu_state = STATE_MENU;
      menu_draw();
      break;
    case STATE_SSID_SELECT:
      menu_state = STATE_MENU;
      menu_draw();
      break;
    case STATE_SSID_LIST:
      // BUGFIX 2.26.3: echter Austritt aus Menue 3a/3b - Cache jetzt freigeben
      vendorCache_end();
      menu_enter_ssid_select();
      break;
    case STATE_TRAFFIC_STATS:
      traffic_stats_release_lock();
      vendorCache_end();
      menu_state = STATE_MENU;
      menu_draw();
      break;
    case STATE_TRAFFIC_DETAIL:
      // BUGFIX 2.30.44: menu_state wurde hier nie auf STATE_TRAFFIC_STATS
      // zurueckgesetzt, bevor traffic_stats_redraw() aufgerufen wird - diese
      // Funktion bricht aber sofort ab, wenn menu_state nicht bereits
      // STATE_TRAFFIC_STATS ist. Ergebnis: der Bildschirm blieb stehen und
      // menu_state haengte dauerhaft auf STATE_TRAFFIC_DETAIL fest, Backspace
      // wirkte nie wieder (nur ESC, weil das global ueberschreibt).
      traffic_detail_stop();
      menu_state = STATE_TRAFFIC_STATS;
      traffic_stats_redraw();
      break;
    case STATE_BEACON_ANALYSIS:
      // NEU 2.29.17: Erfassung abbrechen/Puffer freigeben, zurueck zu Menue 3
      // (Unterseite, wie STATE_SSID_LIST oben).
      cancel_beacon_capture();
      menu_enter_ssid_select();
      break;
    case STATE_CLIENT_ANALYSIS:
      // NEU 2.30.6: Erfassung abbrechen/Puffer freigeben - anders als beim
      // Beacon-Pendant zurueck in DIESELBE Geraeteliste (Menue 3a), da hier
      // aus der Geraeteliste heraus gestartet wird (nicht aus der AP-Liste).
      cancel_client_capture();
      redraw_ssid_list();
      break;
    case STATE_SETTINGS:
      menu_state = STATE_MENU;
      menu_draw();
      break;
    case STATE_HELP:
      menu_state = STATE_MENU;
      menu_draw();
      break;
    case STATE_INFO:
      menu_state = STATE_MENU;
      menu_draw();
      break;
    case STATE_HIDDEN_SETTINGS:
      menu_enter_settings();
      break;
    case STATE_SAVE_FILENAME:
      menu_state = STATE_MENU;
      menu_draw();
      break;
    case STATE_FILE_LIST:
      menu_state = STATE_MENU;
      menu_draw();
      break;
    case STATE_NTP_SETTINGS:
      menu_enter_settings();
      break;
    case STATE_ADC_SETTINGS:
      // NEU 2.30.32: ADC-Einstellungen sind jetzt Teil der Hidden Settings ->
      // Backspace/ESC fuehrt entsprechend dorthin zurueck (statt zu den
      // normalen Einstellungen).
      menu_enter_hidden_settings();
      break;
    case STATE_RAM_DEBUG:
      // NEU 2.30.34: Debug RAM Memory ist Teil der Hidden Settings.
      menu_enter_hidden_settings();
      break;
    case STATE_CALL_CHAIN_VIEW:
      // NEU 2.30.35: Call-Chain-Anzeige ist Teil von Debug RAM Memory.
      menu_enter_ram_debug();
      break;
    case STATE_NTP_TEXT_EDIT:
      // NEU 2.29.0: bei ADC-Kalibrierung (Marker 11) zurueck zu den
      // ADC-Einstellungen statt (wie sonst bei diesem geteilten Text-Edit-
      // State) zu den NTP-Einstellungen.
      if (ntp_edit_target == 11) menu_enter_adc_settings();
      else menu_enter_ntp_settings();
      break;
    case STATE_FACTORY_RESET_CONFIRM:
      menu_enter_hidden_settings();
      break;
    case STATE_WATCHLIST:
      // BUGFIX 2.26.3: echter Austritt aus Menue 4 - Cache jetzt freigeben
      vendorCache_end();
      // NEU 2.27.1 REQ-4: Rueckkehr-Signalisierungs-Zustand ebenfalls freigeben
      watchlistPulse_end();
      menu_state = STATE_MENU;
      menu_draw();
      break;
    case STATE_WATCHLIST_ADD_MAC:
    case STATE_WATCHLIST_ADD_DESC:
      // Eingabe leer -> Vorgang abbrechen, zurueck zur Watchlist-Ansicht
      // (nicht bis ganz ins Hauptmenue, da Punkt 4 ein Unterschritt ist)
      menu_enter_watchlist();
      break;
    case STATE_TIMEWATCH_ADD_DESC:
      {
        int origin = timewatch_return_to;
        timewatch_return_to = 0;
        watch_desc_input_len = 0;
        watch_desc_input_buf[0] = '\0';
        if (origin == 1) menu_enter_ssid_select();
        else if (origin == 2) redraw_ssid_list();
        else { menu_state = STATE_MENU; menu_draw(); }
      }
      break;
    case STATE_NOTIF_SETTINGS:
      menu_enter_settings();
      break;
    case STATE_NOTIF_TEXT_EDIT:
      menu_enter_notif_settings();
      break;
    case STATE_APMODE_SETTINGS:
      menu_enter_settings();
      break;
    case STATE_APMODE_TEXT_EDIT:
      menu_enter_apmode_settings();
      break;
    case STATE_CLEANUP:
      menu_state = STATE_MENU;
      menu_draw();
      break;
    // NEU 2.30.24: Punkt 2 Filter-Untermenue - jeweils EINEN Schritt zurueck
    // (nicht direkt bis STATE_MENU), analog zu STATE_WATCHLIST_ADD_MAC/_DESC
    // oben. STATE_FILTER_LIVE geht explizit auf Nutzerwunsch zurueck zu den
    // Kriterien (nicht bis ins Hauptmenue).
    case STATE_FILTER_MENU:
      menu_state = STATE_MENU;
      menu_draw();
      break;
    case STATE_FILTER_MAC_INPUT:
      menu_enter_filter_menu();
      break;
    case STATE_FILTER_CRITERIA:
      if (filter_has_mac) menu_enter_filter_mac_input();
      else menu_enter_filter_menu();
      break;
    case STATE_FILTER_SUB_PROBE:
    case STATE_FILTER_SUB_MGMT:
    case STATE_FILTER_SUB_CTRL:
    case STATE_FILTER_SUB_DATA:
      menu_enter_filter_criteria();
      break;
    case STATE_FILTER_LIVE:
      filter_channel_unlock_if_active();  // NEU 2.30.29
      menu_enter_filter_criteria();
      break;
    // NEU 2.30.29: Punkt 2.3 "MAC-Adresse nachschlagen"
    case STATE_MAC_LOOKUP_INPUT:
      menu_enter_filter_menu();
      break;
    case STATE_MAC_LOOKUP_RESULT:
      menu_enter_mac_lookup_input();
      break;
    // NEU 2.30.32: Punkt 2.4 "Diagnose: scharfer Timing-Test"
    case STATE_TIMING_TEST_MAC_INPUT:
      menu_enter_filter_menu();
      break;
    case STATE_TIMING_TEST_RUNNING:
      // Konsistent mit dem Abbruch-Pfad in timing_test_process_packet():
      // auch hier das bisher Aufgezeichnete anzeigen statt es wegzuwerfen.
      timing_test_finish();
      break;
    case STATE_TIMING_TEST_RESULT:
      menu_enter_filter_menu();
      break;
    case STATE_ROAMING_GROUPS:
      // NEU 2.30.60: Punkt v - zurueck ins Hauptmenue
      menu_state = STATE_MENU;
      menu_draw();
      break;
    case STATE_MENU:
      menu_draw();
      break;
  }
}

// Vom Hauptloop periodisch aufgerufen (nicht blockierend), realisiert den
// Auto-Refresh der Geraeteliste (Punkt 3)
void menu_periodic()
{
  // NEU 2.30.11/2.30.45: FrameTrap (Client + Beacon) - unabhaengig vom
  // aktuellen Menue-Zustand (deshalb ganz am Anfang, noch vor dem HTTP-
  // Server-Handling): fertige Faenge aus promisc_cb() abarbeiten
  // (dekodieren + Datei schreiben + Eintrag/Liste aufraeumen). Das
  // eigentliche Einsammeln der Rohbytes geschah bereits im Callback (nur
  // memcpy) - hier passiert die "langsame" Datei-I/O sicher im Hauptloop-
  // Kontext.
  for (int s = 0; s < FRAMETRAP_CLIENT_MAX_PENDING; s++) {
    if (frametrap_client_catches[s].buf != NULL) {
      frametrap_client_process_catch(s);
    }
  }
  for (int s = 0; s < FRAMETRAP_BEACON_MAX_PENDING; s++) {
    if (frametrap_beacon_catches[s].buf != NULL) {
      frametrap_beacon_process_catch(s);
    }
  }

  // NEU 2.30.0: Waehrend Punkt 7 aktiv ist, muss der HTTP-Server in jedem
  // Schleifendurchlauf bedient werden (nicht blockierend). Bewusst ganz
  // am Anfang, damit Anfragen zuegig beantwortet werden, unabhaengig
  // davon, was weiter unten sonst noch an periodischen Aufgaben laeuft.
  if (menu_state == STATE_HTTP_SERVER && g_http_server != nullptr) {
    g_http_server->handleClient();
    // BUGFIX 2.30.5: erst HIER, nach Rueckkehr aus handleClient(), darf
    // der Server tatsaechlich gestoppt/geloescht werden (siehe Kommentar
    // bei g_http_stop_requested).
    if (g_http_stop_requested) {
      g_http_stop_requested = false;
      http_server_stop();
    }
  }

  // NEU 2.28.0: Rueckkehr-Signalisierung (Watchlist) - laeuft unabhaengig
  // vom aktuellen Menuestatus, damit sie an jeder Menuestelle greift.
  watchlist_background_check();

  // NEU 2.29.0: Akkuspannungs-Ueberwachung - laeuft ebenso unabhaengig vom
  // aktuellen Menuestatus (eigene interne 5s-Taktung, hier nur angestossen).
  adc_voltage_monitor();

  // NEU 2.29.1: Wartendes Listen-Ueberlauf-Ereignis sicher im Hauptloop
  // bearbeiten (siehe Kommentar bei pending_overflow_type).
  process_pending_overflow();

  // NEU 2.27.4: Auto-Refresh fuer Menue 3 (SSID-/AP-Uebersicht). Gleiche
  // Logik wie bei den anderen Menues (Zeitfenster + online_mode-Gate),
  // zusaetzlich per input_field_active() abgesichert - sonst wuerde ein
  // Auto-Refresh waehrend der Eingabe einer AP-Nummer diese loeschen
  // (menu_enter_ssid_select() setzt ssid_input_len beim Aufruf zurueck).
  if (menu_state == STATE_SSID_SELECT && !input_field_active() && online_mode) {
    uint32_t now = millis() / 1000;
    if (now - last_ssid_select_refresh_time >= ssid_select_refresh_sec) {
      menu_enter_ssid_select();
    }
  }
  if (menu_state == STATE_TRAFFIC_STATS && online_mode) {
    if (millis() - traffic_stats_last_refresh >= TRAFFIC_STATS_REFRESH_SEC * 1000UL) {
      traffic_stats_redraw();
    }
  }
  if (menu_state == STATE_TRAFFIC_DETAIL && online_mode) {
    if (millis() - traffic_detail_last_refresh >= TRAFFIC_STATS_REFRESH_SEC * 1000UL) {
      traffic_detail_redraw();
    }
  }
  if (menu_state == STATE_SSID_LIST && !threshold_input_active && online_mode) {
    uint32_t now = millis() / 1000;
    if (now - last_list_refresh_time >= list_refresh_sec) {
      redraw_ssid_list();
    }
  }
  if (menu_state == STATE_WATCHLIST && !watch_delete_mode && watch_delete_input_len == 0 && online_mode) {
    uint32_t now = millis() / 1000;
    if (now - last_watchlist_refresh_time >= watchlist_refresh_sec) {
      menu_enter_watchlist();
    }
  }
  // NEU 2.29.17: Beacon-Frame-Analyse (Punkt 3, "w"+Zahl) - Warten auf den
  // naechsten Beacon der gewaehlten BSSID (siehe promisc_cb()) mit Timeout.
  if (menu_state == STATE_BEACON_ANALYSIS && beacon_capture_armed) {
    if (millis() - beacon_capture_start_ms > BEACON_ANALYSIS_TIMEOUT_MS) {
      beacon_capture_armed = false;
      if (beacon_capture_buf != NULL) { free(beacon_capture_buf); beacon_capture_buf = NULL; }
      Serial.println();
      Serial.println(F(" Zeitueberschreitung - in der Wartezeit wurde kein Beacon dieses"));
      Serial.println(F(" APs empfangen (schwaches Signal oder Kanal-Hopping-Pech moeglich -"));
      Serial.println(F(" erneuter Versuch ueber Punkt 3 jederzeit moeglich)."));
      Serial.println();
      Serial.println(F(" Backspace/ESC = zurueck"));
    }
  }
  if (menu_state == STATE_BEACON_ANALYSIS && beacon_capture_done) {
    beacon_capture_done = false;
    display_beacon_frame_analysis();
    if (beacon_capture_buf != NULL) { free(beacon_capture_buf); beacon_capture_buf = NULL; }
    Serial.println();
    Serial.println(F(" Backspace/ESC = zurueck"));
  }

  // NEU 2.30.8: Client-Frame-Analyse (Menue 3a, "w"+Zahl) - Pendant zum
  // Beacon-Block oben, wartet auf das naechste Paket (Datenframe ODER
  // Management-Frame) der gewaehlten Station-MAC (siehe promisc_cb()) mit
  // Timeout.
  if (menu_state == STATE_CLIENT_ANALYSIS && client_capture_armed) {
    if (millis() - client_capture_start_ms > BEACON_ANALYSIS_TIMEOUT_MS) {
      client_capture_armed = false;
      if (client_capture_buf != NULL) { free(client_capture_buf); client_capture_buf = NULL; }
      Serial.println();
      Serial.println(F(" Zeitueberschreitung - in der Wartezeit wurde kein Paket dieses"));
      Serial.println(F(" Clients empfangen (schwaches Signal, Client inaktiv/im Energie-"));
      Serial.println(F(" sparmodus, oder Kanal-Hopping-Pech moeglich - erneuter Versuch"));
      Serial.println(F(" jederzeit moeglich)."));
      Serial.println();
      Serial.println(F(" Backspace/ESC = zurueck"));
    }
  }
  if (menu_state == STATE_CLIENT_ANALYSIS && client_capture_done) {
    client_capture_done = false;
    display_client_frame_analysis();
    if (client_capture_buf != NULL) { free(client_capture_buf); client_capture_buf = NULL; }
    Serial.println();
    Serial.println(F(" Backspace/ESC = zurueck"));
  }
}


// Verarbeitet alle aktuell verfuegbaren Serial-Zeichen, nicht blockierend.
// true, solange gerade Text/Zahlen in ein Eingabefeld getippt werden -
// in diesem Fall soll Strg+O NICHT die Ansicht wechseln (wuerde die
// Eingabe durch das Neuzeichnen verwerfen).
bool input_field_active()
{
  if (menu_state == STATE_SAVE_FILENAME) return true;
  if (menu_state == STATE_SSID_SELECT && (ssid_input_len > 0 || ssid_select_combined || ssid_select_delete_mode)) return true;
  if (menu_state == STATE_SSID_LIST && (threshold_input_active || client_select_analyze_mode)) return true;
  if (menu_state == STATE_TRAFFIC_STATS && traffic_detail_selecting) return true;
  if (menu_state == STATE_FILE_LIST && (file_input_len > 0 || file_delete_mode || file_load_mode || file_send_mode)) return true;
  if (menu_state == STATE_SETTINGS && settings_input_active) return true;
  if (menu_state == STATE_WATCHLIST_ADD_MAC) return true;
  if (menu_state == STATE_WATCHLIST_ADD_DESC) return true;
  if (menu_state == STATE_TIMEWATCH_ADD_DESC) return true;
  if (menu_state == STATE_FILTER_MAC_INPUT) return true;  // NEU 2.30.24
  if (menu_state == STATE_MAC_LOOKUP_INPUT) return true;   // NEU 2.30.29
  if (menu_state == STATE_TIMING_TEST_MAC_INPUT) return true;  // NEU 2.30.32
  if (menu_state == STATE_WATCHLIST && (watch_delete_mode || watch_delete_input_len > 0)) return true;
  if (menu_state == STATE_NOTIF_SETTINGS && notif_interval_input_len > 0) return true;
  if (menu_state == STATE_NOTIF_TEXT_EDIT) return true;
  if (menu_state == STATE_APMODE_TEXT_EDIT) return true;
  if (menu_state == STATE_NTP_SETTINGS) return true;
  if (menu_state == STATE_ADC_SETTINGS) return true;
  if (menu_state == STATE_NTP_TEXT_EDIT) return true;
  if (menu_state == STATE_FACTORY_RESET_CONFIRM) return true;
  if (menu_state == STATE_CLEANUP && (cleanup_input_len > 0 || !cleanup_age_phase)) return true;
  if (menu_state == STATE_BEACON_ANALYSIS) return true;
  if (menu_state == STATE_CLIENT_ANALYSIS) return true;
  return false;
}

// Zeichnet den aktuell sichtbaren Bildschirm neu (z.B. nach Strg+O, damit
// die Offline-Warnzeile sofort erscheint/verschwindet).
void refresh_current_screen()
{
  switch (menu_state) {
    case STATE_MENU: menu_draw(); break;
    case STATE_SSID_SELECT: menu_enter_ssid_select(); break;
    case STATE_SSID_LIST: redraw_ssid_list(); break;
    case STATE_SETTINGS: menu_enter_settings(); break;
    case STATE_HELP: menu_enter_help(); break;
    case STATE_INFO: menu_enter_info(); break;
    case STATE_HIDDEN_SETTINGS: menu_enter_hidden_settings(); break;
    case STATE_FILE_LIST: menu_enter_file_list(); break;
    case STATE_WATCHLIST: menu_enter_watchlist(); break;
    case STATE_NOTIF_SETTINGS: menu_enter_notif_settings(); break;
    case STATE_APMODE_SETTINGS: menu_enter_apmode_settings(); break;
    case STATE_NTP_SETTINGS: menu_enter_ntp_settings(); break;
    case STATE_ADC_SETTINGS: menu_enter_adc_settings(); break;
    case STATE_RAM_DEBUG: menu_enter_ram_debug(); break;
    case STATE_CALL_CHAIN_VIEW: menu_enter_call_chain_view(); break;
    case STATE_CLEANUP: menu_enter_cleanup(); break;
    case STATE_TRAFFIC_STATS: traffic_stats_redraw(); break;
    case STATE_TRAFFIC_DETAIL: traffic_detail_redraw(); break;
    case STATE_ROAMING_GROUPS: menu_enter_roaming_groups(); break;  // NEU 2.30.60
    case STATE_TIMEWATCH_ADD_DESC: menu_enter_timewatch_add_desc(); break;  // NEU 2.30.67
    case STATE_LIVE:
      vt_clear_screen();
      Serial.println(F("Standardausgabe aktiv. ESC/Backspace = Menue."));
      print_offline_banner_now();  // NEU 2.30.32: steht jetzt am Ende der Ausgabe
      break;
    // NEU 2.30.24: Filter-Untermenue
    case STATE_FILTER_MENU: menu_enter_filter_menu(); break;
    case STATE_FILTER_MAC_INPUT:
      // Eingabe geht beim Neuzeichnen verloren (wie bei anderen Text-
      // Eingabefeldern in diesem Dispatcher auch nicht extra abgefangen) -
      // deshalb steht dieser State bewusst auch in input_field_active(),
      // sodass Strg+O/Strg+D hier gar nicht erst durchgreifen.
      menu_enter_filter_mac_input();
      break;
    case STATE_FILTER_CRITERIA: draw_filter_criteria_screen(); break;
    case STATE_FILTER_SUB_PROBE: menu_enter_filter_sub_probe(); break;
    case STATE_FILTER_SUB_MGMT: menu_enter_filter_sub_mgmt(); break;
    case STATE_FILTER_SUB_CTRL: menu_enter_filter_sub_ctrl(); break;
    case STATE_FILTER_SUB_DATA: menu_enter_filter_sub_data(); break;
    case STATE_FILTER_LIVE: menu_enter_filter_live(); break;
    // NEU 2.30.29: Punkt 2.3
    case STATE_MAC_LOOKUP_INPUT: menu_enter_mac_lookup_input(); break;
    case STATE_MAC_LOOKUP_RESULT: menu_enter_mac_lookup_result(); break;
    // NEU 2.30.32: STATE_TIMING_TEST_RUNNING bewusst NICHT hier aufgefuehrt -
    // ein Neuzeichnen wuerde ueber menu_enter_timing_test_running() den Test
    // neu starten (Zaehler/Startzeit zuruecksetzen), was bei einem Strg+O/
    // Strg+D-Refresh nicht gewuenscht ist. Faellt auf "default: break;"
    // zurueck (keine Neuzeichnung waehrend des laufenden Tests - so soll es
    // sein, siehe "keine Ausgabe bis zum Ende").
    case STATE_TIMING_TEST_MAC_INPUT: menu_enter_timing_test_mac_input(); break;
    case STATE_TIMING_TEST_RESULT: timing_test_finish(); break;
    default: break;
  }
}

void menu_handle_serial()
{
  ram_debug_sample(RDP_INPUT);  // NEU 2.30.34: passive RAM-/Stack-Diagnose (Eingabeverarbeitung)
  CallChainGuard __cc_guard(RDP_INPUT);  // NEU 2.30.35: Call-Chain-Erweiterung

  // NEU 2.30.32: Sicherheitsnetz fuer den Timing-Test (Punkt 2.4) - der
  // eigentliche Timeout-Check sitzt in timing_test_process_packet() und
  // wird nur bei eintreffenden Paketen ausgewertet. Traefe waehrend des
  // gesamten Testfensters (rein theoretisch) ueberhaupt kein Paket ein,
  // wuerde dieser Check hier trotzdem greifen, da menu_handle_serial() bei
  // jedem loop()-Durchlauf aufgerufen wird, unabhaengig vom Funkverkehr.
  if (timing_test_active && millis() - timing_test_start_ms >= timing_test_duration_s * 1000UL) {
    timing_test_finish();
  }

  while (Serial.available() > 0) {
    char c = Serial.read();

    // NEU 2.30.0: Waehrend Punkt 7 (HTTP-Datei-Server) aktiv ist, beendet
    // EIN BELIEBIGER Tastendruck auf der seriellen Konsole den Server
    // sauber - unabhaengig vom Inhalt (auch ESC/Backspace/Buchstaben),
    // deshalb muss dies VOR allen anderen Sonderzeichen-Behandlungen
    // abgefangen werden. So bleibt der Server
    // auch dann jederzeit beendbar, wenn im Netz kein Client mehr
    // erreichbar ist.
    if (menu_state == STATE_HTTP_SERVER) {
      http_server_stop();
      continue;
    }

    if (c == 15 && !input_field_active()) {  // Strg+O - Online/Offline umschalten
      toggle_online_mode();
      refresh_current_screen();
      continue;
    }

    if (c == 27) {  // ESC - jederzeit zurueck zum Hauptmenue
      if (traffic_stats_start_confirm_pending) {
        traffic_stats_start_confirm_pending = false;
        traffic_stats_pending_mode = 0;
        traffic_stats_pending_ap_idx = -1;
        traffic_stats_pending_ssid[0] = '\0';
      }
      // NEU 2.29.17: laufende/abgeschlossene Beacon-Erfassung abbrechen und
      // den Zwischenpuffer freigeben, falls ESC waehrend STATE_BEACON_ANALYSIS
      // gedrueckt wird (analog zum Cache-Aufraeumen bei Menue 3a/4 unten).
      if (menu_state == STATE_BEACON_ANALYSIS) {
        cancel_beacon_capture();
      }
      // NEU 2.30.6: analog zu STATE_BEACON_ANALYSIS oben, aber fuer die
      // Client-Frame-Analyse (Probe Request).
      if (menu_state == STATE_CLIENT_ANALYSIS) {
        cancel_client_capture();
      }
      // NEU 2.30.29: Kanal-Lock aufheben, falls ESC waehrend der Punkt-2.1-
      // Live-Ausgabe gedrueckt wird (Backspace-Weg siehe menu_go_back()).
      if (menu_state == STATE_FILTER_LIVE) {
        filter_channel_unlock_if_active();
      }
      // NEU 2.30.32: laufenden Timing-Test sauber beenden, falls ESC
      // waehrend STATE_TIMING_TEST_RUNNING gedrueckt wird (Backspace-Weg
      // siehe menu_go_back()). Nur das Flag loeschen reicht hier, da ESC
      // ohnehin direkt zu STATE_MENU springt und das Ergebnis nicht mehr
      // gezeigt werden muss.
      if (menu_state == STATE_TIMING_TEST_RUNNING) {
        timing_test_active = false;
      }
      // NEU 2.30.39: Statistikpuffer beim direkten ESC-Austritt freigeben.
      if (menu_state == STATE_TRAFFIC_DETAIL) {
        traffic_detail_stop();
        // NEU 2.30.81: ESC beendet nur die Detailansicht; die uebergeordnete
        // Hintergrundverkehr-Aufzeichnung und ihre Puffer bleiben erhalten.
      }
      if (menu_state == STATE_TRAFFIC_STATS) {
        traffic_stats_release_lock();
      }
      // BUGFIX 2.26.3: ESC springt von JEDEM Zustand direkt zu STATE_MENU,
      // ueberspringt also menu_go_back() - Cache muss deshalb auch hier
      // freigegeben werden, falls wir gerade in Menue 3a/3b oder 4 (inkl.
      // dessen Unterschritte "MAC hinzufuegen"/"Beschreibung hinzufuegen")
      // waren. NEU 2.30.6: STATE_CLIENT_ANALYSIS ergaenzt, da von dort
      // (aus Menue 3a heraus gestartet) derselbe Vendor-Cache aktiv ist.
      if (menu_state == STATE_SSID_LIST || menu_state == STATE_TRAFFIC_STATS || menu_state == STATE_TRAFFIC_DETAIL || menu_state == STATE_CLIENT_ANALYSIS ||
          menu_state == STATE_WATCHLIST ||
          menu_state == STATE_WATCHLIST_ADD_MAC || menu_state == STATE_WATCHLIST_ADD_DESC) {
        vendorCache_end();
      }
      // NEU 2.27.1 REQ-4: dieselbe Logik fuer den Rueckkehr-Signalisierungs-
      // Zustand, nur fuer die Watchlist-relevanten Zustaende (nicht SSID_LIST)
      if (menu_state == STATE_WATCHLIST || menu_state == STATE_WATCHLIST_ADD_MAC ||
          menu_state == STATE_WATCHLIST_ADD_DESC) {
        watchlistPulse_end();
      }
      if (menu_state == STATE_TIMEWATCH_ADD_DESC) {
        timewatch_return_to = 0;
        watch_desc_input_len = 0;
        watch_desc_input_buf[0] = '\0';
      }
      ssid_select_timewatch_prefix = false;
      ssid_select_timewatch_mode = false;
      client_timewatch_mode = false;
      menu_state = STATE_MENU;
      menu_draw();
      continue;
    }

    if (c == 8 || c == 127) {  // Backspace/DEL
      // Sonderfaelle: solange schon Zeichen in einem Eingabefeld stehen,
      // loescht Backspace erst die Eingabe, statt das Menue zu wechseln.
      if (menu_state == STATE_SSID_SELECT && ssid_input_len > 0) {
        ssid_input_len--;
        ssid_input_buf[ssid_input_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_SSID_SELECT && ssid_input_len == 0 && ssid_select_timewatch_mode) {
        ssid_select_timewatch_mode = false;
        Serial.write(8); Serial.write(' '); Serial.write(8);
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_SSID_SELECT && ssid_input_len == 0 && ssid_select_timewatch_prefix) {
        ssid_select_timewatch_prefix = false;
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_SSID_SELECT && ssid_input_len == 0 && ssid_select_combined) {
        ssid_select_combined = false;
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_SSID_LIST && threshold_input_active && threshold_input_len > 0) {
        threshold_input_len--;
        threshold_input_buf[threshold_input_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_SSID_LIST && client_select_analyze_mode && ssid_input_len > 0) {
        // NEU 2.30.6: Ziffer der Client-Nummer loeschen (Menue 3a, 'w'-Modus)
        ssid_input_len--;
        ssid_input_buf[ssid_input_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_SSID_LIST && client_select_analyze_mode && ssid_input_len == 0 && client_frametrap_mode) {
        // NEU 2.30.11: noch keine Ziffer eingegeben - 'p'-Praefix zuruecknehmen (zurueck zu reinem 'w')
        client_frametrap_mode = false;
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_SSID_LIST && client_select_analyze_mode && ssid_input_len == 0 && client_timewatch_mode) {
        client_timewatch_mode = false;
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_SSID_LIST && client_select_analyze_mode && ssid_input_len == 0) {
        // NEU 2.30.6: noch keine Ziffer eingegeben - 'w'-Praefix zuruecknehmen
        client_select_analyze_mode = false;
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_TRAFFIC_STATS && traffic_detail_selecting && traffic_detail_input_len > 0) {
        traffic_detail_input_len--;
        traffic_detail_input_buf[traffic_detail_input_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_TRAFFIC_STATS && traffic_detail_selecting) {
        traffic_detail_selecting = false;
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_SAVE_FILENAME && save_filename_len > 0) {
        save_filename_len--;
        save_filename_buf[save_filename_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_FILE_LIST && file_protect_input_len > 0) {  // NEU 2.25.0
        file_protect_input_len--;
        file_protect_input_buf[file_protect_input_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_FILE_LIST && file_protect_mode) {  // NEU 2.25.0
        file_protect_mode = false;
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_FILE_LIST && file_input_len > 0) {
        file_input_len--;
        file_input_buf[file_input_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_FILE_LIST && file_delete_mode) {
        file_delete_mode = false;
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_FILE_LIST && file_send_mode) {
        file_send_mode = false;
      } else if (menu_state == STATE_FILE_LIST && file_load_mode) {
        file_load_mode = false;
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_SETTINGS && settings_input_active && settings_input_len > 0) {
        settings_input_len--;
        settings_input_buf[settings_input_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_WATCHLIST && watch_delete_input_len > 0) {
        watch_delete_input_len--;
        watch_delete_input_buf[watch_delete_input_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_WATCHLIST && watch_delete_mode) {
        watch_delete_mode = false;
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_WATCHLIST_ADD_MAC && watch_mac_input_len > 0) {
        watch_mac_input_len--;
        watch_mac_input_buf[watch_mac_input_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_FILTER_MAC_INPUT && filter_mac_input_len > 0) {
        // NEU 2.30.24
        filter_mac_input_len--;
        filter_mac_input_buf[filter_mac_input_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_MAC_LOOKUP_INPUT && lookup_mac_input_len > 0) {
        // NEU 2.30.29
        lookup_mac_input_len--;
        lookup_mac_input_buf[lookup_mac_input_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_TIMING_TEST_MAC_INPUT && timing_test_mac_input_len > 0) {
        // NEU 2.30.32
        timing_test_mac_input_len--;
        timing_test_mac_input_buf[timing_test_mac_input_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_WATCHLIST_ADD_DESC && watch_desc_input_len > 0) {
        watch_desc_input_len--;
        watch_desc_input_buf[watch_desc_input_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_TIMEWATCH_ADD_DESC && watch_desc_input_len > 0) {
        watch_desc_input_len--;
        watch_desc_input_buf[watch_desc_input_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_NOTIF_SETTINGS && notif_interval_input_len > 0) {
        notif_interval_input_len--;
        notif_interval_input_buf[notif_interval_input_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_NOTIF_TEXT_EDIT && notif_text_edit_len > 0) {
        notif_text_edit_len--;
        notif_text_edit_buf[notif_text_edit_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_NTP_TEXT_EDIT && ntp_text_edit_len > 0) {
        ntp_text_edit_len--;
        ntp_text_edit_buf[ntp_text_edit_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else if (menu_state == STATE_FACTORY_RESET_CONFIRM && factory_reset_input_len > 0) {
        factory_reset_input_len--;
        factory_reset_input_buf[factory_reset_input_len] = '\0';
        Serial.write(8); Serial.write(' '); Serial.write(8);
      } else {
        menu_go_back();
      }
      continue;
    }

    switch (menu_state) {
      case STATE_LIVE:
        if (c == 13) {
          Serial.println(F("\n-------------------------------------------------------------------------------------\n"));
          for (int u = 0; u < clients_known_count; u++) { print_client(clients_known[u]); yield(); }
          for (int u = 0; u < aps_known_count; u++) { if (!ap_slot_free(u)) { print_beacon(aps_known[u]); yield(); } }
          Serial.println(F("\n-------------------------------------------------------------------------------------\n"));
        }
        break;

      case STATE_MENU:
        if (c == 'b' && traffic_stats_active) {
          traffic_stats_reapply_lock();
          menu_state = STATE_TRAFFIC_STATS;
          traffic_stats_redraw();
        } else if (c == '1') {
          menu_state = STATE_LIVE;
          vt_clear_screen();
  OfflineBannerGuard __banner_guard;  // NEU 2.30.32: Banner (OFFLINE/Channel-Warnung) wird erst beim Verlassen dieser Funktion ausgegeben (RAII) -> steht damit immer ganz unten
          Serial.println(F("Standardausgabe aktiv. ESC/Backspace = Menue."));
          Serial.println(F("Type:   /-------MAC------/-----WiFi Access Point SSID-----/  /----MAC---/  Chnl  RSSI"));
        } else if (c == '2') {
          menu_enter_filter_menu();
        } else if (c == '3') {
          menu_enter_ssid_select();
        } else if (c == '5') {
          menu_enter_save_filename();
        } else if (c == '6') {
          menu_enter_file_list();
        } else if (c == '7') {
          menu_enter_http_server();
        } else if (c == '4') {
          menu_enter_watchlist();
        } else if (c == 'e') {
          menu_enter_settings();
        } else if (c == 'i') {
          menu_enter_info();
        } else if (c == 'h') {
          menu_enter_help();
        } else if (c == 'm') {
          menu_enter_cleanup();
        } else if (c == 'v') {
          menu_enter_roaming_groups();  // NEU 2.30.60
        }
        break;

      case STATE_CLEANUP:
        if (cleanup_age_phase) {
          if (c == 'o' || c == 'O') {
            uint64_t now = effective_now();
            Serial.println();
            Serial.println(F(" Loesche alte 0/0-APs ..."));
            int n = delete_old_empty_aps(now);
            Serial.printf_P(PSTR(" %d alte 0/0-AP(s) geloescht.\r\n"), n);
            menu_state = STATE_MENU;
            menu_draw();
            break;
          } else if (c >= '0' && c <= '9') {
            if (cleanup_input_len < 7) {
              cleanup_input_buf[cleanup_input_len] = c;
              cleanup_input_len++;
              cleanup_input_buf[cleanup_input_len] = '\0';
              Serial.print(c);
            }
          } else if (c == 13) {
            Serial.println();
            int val = atoi(cleanup_input_buf);
            if (val <= 0) {
              cleanup_input_len = 0;
              cleanup_input_buf[0] = '\0';
              Serial.println(F(" Ungueltiger Wert."));
              Serial.print(F(" Alter in Sekunden eingeben (Eintraege AELTER werden geloescht): "));
            } else {
              cleanup_age_threshold = val;
              cleanup_age_phase = false;
              Serial.printf_P(PSTR(" Alter: %d Sekunden.\r\n"), cleanup_age_threshold);
              Serial.println(F(" Was loeschen? c=nur Clients, a=nur Access Points, b=beides"));
            }
          }
        } else {
          uint64_t now = effective_now();
          if (c == 'c') {
            int n = delete_old_clients(cleanup_age_threshold, now);
            Serial.printf_P(PSTR(" %d Client(s) geloescht.\r\n"), n);
            menu_state = STATE_MENU;
            menu_draw();
          } else if (c == 'a') {
            int n = delete_old_aps(cleanup_age_threshold, now);
            Serial.printf_P(PSTR(" %d Access Point(s) geloescht.\r\n"), n);
            menu_state = STATE_MENU;
            menu_draw();
          } else if (c == 'b') {
            int nc = delete_old_clients(cleanup_age_threshold, now);
            int na = delete_old_aps(cleanup_age_threshold, now);
            Serial.printf_P(PSTR(" %d Client(s) und %d Access Point(s) geloescht.\r\n"), nc, na);
            menu_state = STATE_MENU;
            menu_draw();
          }
        }
        break;

      case STATE_SSID_SELECT:
        if ((c == 's' || c == 'S') && ssid_input_len == 0) {
          ssid_select_combined = true;
          Serial.print('S');
        } else if (c == 'd' && ssid_input_len == 0 && !ssid_select_combined) {
          // NEU 2.17.5: d+Zahl+Enter loescht gezielt einen einzelnen AP
          // aus der Hauptliste (analog zu Punkt 6, Datei loeschen).
          ssid_select_delete_mode = true;
          Serial.print('d');
        } else if (c == 'w' && ssid_input_len == 0 && !ssid_select_combined && !ssid_select_delete_mode && !ssid_select_timewatch_prefix && !ssid_select_timewatch_mode) {
          // NEU 2.29.17: w+Zahl+Enter startet die Beacon-Frame-Rohanalyse
          // des gewaehlten APs.
          ssid_select_analyze_mode = true;
          Serial.print('w');
        } else if (c == 't' && ssid_input_len == 0 && !ssid_select_combined &&
                   !ssid_select_delete_mode && !ssid_select_analyze_mode &&
                   !ssid_select_timewatch_prefix && !ssid_select_timewatch_mode) {
          // NEU 2.30.67: 'tw'+Zahl+Enter = TimeWatch fuer einen AP.
          ssid_select_timewatch_prefix = true;
          Serial.print('t');
        } else if (c == 'w' && ssid_input_len == 0 && ssid_select_timewatch_prefix) {
          ssid_select_timewatch_prefix = false;
          ssid_select_timewatch_mode = true;
          Serial.print('w');
        } else if (c == 't' && ssid_input_len == 0 && ssid_select_analyze_mode && !ap_select_frametrap_mode) {
          // NEU 2.30.45: "wt"+Zahl+Enter macht stattdessen den Beacon-
          // FrameTrap fuer diesen AP scharf - analog zu "wp"+Zahl+Enter in
          // Menue 3a (dort 'p', hier 't' da 'p' in diesem Menue schon als
          // "nach RSSI sortieren" belegt ist).
          ap_select_frametrap_mode = true;
          Serial.print('t');
        } else if (c == 'u' && ssid_input_len == 0) {
          // NEU 2.17.4: Sortierung Liste 3 - u=unsortiert, n=SSID, g=Anzahl, p=Pegel
          // NEU 2.27.4: a=Age, m=MAC ergaenzt
          set_ap_sort_field(AP_SORT_NONE);
          menu_enter_ssid_select();
        } else if (c == 'n' && ssid_input_len == 0) {
          set_ap_sort_field(AP_SORT_SSID);
          menu_enter_ssid_select();
        } else if (c == 'g' && ssid_input_len == 0) {
          set_ap_sort_field(AP_SORT_COUNT);
          menu_enter_ssid_select();
        } else if (c == 'p' && ssid_input_len == 0) {
          set_ap_sort_field(AP_SORT_RSSI);
          menu_enter_ssid_select();
        } else if (c == 'a' && ssid_input_len == 0) {
          // NEU 2.27.4: Sortierung nach Age (Alter)
          set_ap_sort_field(AP_SORT_AGE);
          menu_enter_ssid_select();
        } else if (c == 'm' && ssid_input_len == 0) {
          // NEU 2.27.4: Sortierung nach MAC-Adresse
          set_ap_sort_field(AP_SORT_MAC);
          menu_enter_ssid_select();
        } else if (c == 'v' && ssid_input_len == 0) {
          // NEU 2.26.x: Toggle Vendor-Anzeige in Menue 3 (AP-Uebersicht)
          show_vendors_in_menu3 = !show_vendors_in_menu3;
          menu_enter_ssid_select();
        } else if (c == '+' && ssid_input_len == 0) {
          // NEU 2.27.4: Auto-Refresh-Intervall erhoehen (analog u/d in
          // anderen Menues, hier +/- da u/d bereits belegt sind)
          ssid_select_refresh_sec += 5;
          menu_enter_ssid_select();
        } else if (c == '-' && ssid_input_len == 0) {
          ssid_select_refresh_sec -= 5;
          if (ssid_select_refresh_sec < 5) ssid_select_refresh_sec = 5;
          menu_enter_ssid_select();
        } else if (c >= '0' && c <= '9') {
          if (ssid_input_len < 19) {  // Buffer ist jetzt [20], max 19 Zeichen
            ssid_input_buf[ssid_input_len] = c;
            ssid_input_len++;
            ssid_input_buf[ssid_input_len] = '\0';
            Serial.print(c);
          }
        } else if (c == ',' && ssid_select_combined && ssid_input_len < 19) {
          // Komma nur erlaubt, wenn 'S' aktiviert und Platz vorhanden
          ssid_input_buf[ssid_input_len] = c;
          ssid_input_len++;
          ssid_input_buf[ssid_input_len] = '\0';
          Serial.print(c);
        } else if (c == 13) {  // Enter
          Serial.println();
          if (ssid_select_timewatch_mode && ssid_input_len > 0) {
            int idx = atoi(ssid_input_buf);
            ssid_input_len = 0;
            ssid_input_buf[0] = '\0';
            ssid_select_timewatch_mode = false;
            if (idx >= 0 && idx < aps_known_count && !ap_slot_free(idx)) {
              memcpy(pending_timewatch_mac, aps_known[idx].bssid, ETH_MAC_LEN);
              timewatch_return_to = 1;
              menu_enter_timewatch_add_desc();
            } else {
              Serial.println(F(" Ungueltige Auswahl."));
            }
            break;
          }
          if (ssid_input_len > 0) {
            if (ssid_select_delete_mode) {
              // NEU 2.17.5: gezieltes Loeschen eines einzelnen AP
              // NEU 2.29.9: loescht jetzt auch die zugehoerigen Clients mit
              int idx = atoi(ssid_input_buf);
              int removed_clients = delete_ap_by_index(idx);
              if (removed_clients >= 0) {
                Serial.printf_P(PSTR(" AP #%d geloescht (%d zugehoerige Client(s) mitentfernt).\r\n"), idx, removed_clients);
              } else {
                Serial.println(F(" Ungueltige Auswahl."));
              }
              ssid_input_len = 0;
              ssid_select_delete_mode = false;
              menu_enter_ssid_select();  // Liste neu zeichnen (Indizes verschoben)
              break;
            } else if (ssid_select_analyze_mode) {
              // NEU 2.29.17: startet die Beacon-Frame-Rohanalyse - setzt
              // menu_state selbst um (STATE_BEACON_ANALYSIS), daher hier
              // direkt raus statt in den regulaeren Reset am Funktionsende
              // zu laufen.
              // NEU 2.30.45: bei "wt"+Zahl+Enter stattdessen den Beacon-
              // FrameTrap scharf machen, statt sofort zu erfassen.
              int idx = atoi(ssid_input_buf);
              ssid_input_len = 0;
              ssid_select_analyze_mode = false;
              bool frametrap = ap_select_frametrap_mode;
              ap_select_frametrap_mode = false;
              if (frametrap) {
                if (idx >= 0 && idx < aps_known_count && !ap_slot_free(idx)) {
                  if (frametrap_beacon_arm(aps_known[idx].bssid)) {
                    Serial.println(F(" FrameTrap scharf - wartet im Hintergrund auf den naechsten Beacon."));
                  }
                } else {
                  Serial.println(F(" Ungueltige Auswahl."));
                }
                break;
              }
              menu_start_beacon_capture(idx);
              break;
            } else if (ssid_select_combined) {
              // Unterscheide zwischen "S5" (SSID-Bündelung) und "S1,5,7" (Multi-AP)
              if (strchr(ssid_input_buf, ',')) {
                // Multi-AP-Modus: kommagetrennte Zahlen
                // Parse und rufe neue Funktion auf
                if (parse_multi_ap_selection(ssid_input_buf)) {
                  menu_enter_ssid_list_multi();
                } else {
                  Serial.println(F(" Fehler: Ungueltige Auswahl oder Nummer zu hoch."));
                  Serial.print(F(" Auswahl: "));
                }
              } else {
                // SSID-Bündelungs-Modus: einzelne Zahl
                int idx = atoi(ssid_input_buf);
                menu_enter_ssid_list_combined(idx);
              }
            } else {
              // Ohne 'S': einzelner AP
              int idx = atoi(ssid_input_buf);
              menu_enter_ssid_list(idx);
            }
          }
          ssid_input_len = 0;
          ssid_select_combined = false;
          ssid_select_delete_mode = false;
          ssid_select_analyze_mode = false;
          ssid_select_timewatch_prefix = false;
          ssid_select_timewatch_mode = false;
        }
        break;

      case STATE_SSID_LIST:
        if (traffic_stats_start_confirm_pending) {
          if (c == 'j' || c == 'J' || c == 'y' || c == 'Y') {
            traffic_stats_start_confirm_pending = false;
            Serial.println(c);
            Serial.println(F(" Neue Hintergrundverkehr-Aufzeichnung wird gestartet..."));
            traffic_stats_start(traffic_stats_pending_mode, traffic_stats_pending_ap_idx, traffic_stats_pending_ssid);
          } else if (c == 'n' || c == 'N') {
            traffic_stats_start_confirm_pending = false;
            Serial.println(c);
            Serial.println(F(" Abgebrochen. Die laufende Aufzeichnung bleibt erhalten."));
          }
          break;
        }
        if (threshold_input_active) {
          if (c >= '0' && c <= '9') {
            if (threshold_input_len < 3) {
              threshold_input_buf[threshold_input_len] = c;
              threshold_input_len++;
              threshold_input_buf[threshold_input_len] = '\0';
              Serial.print(c);
            }
          } else if (c == 13) {
            Serial.println();
            if (threshold_input_len > 0) {
              int val = atoi(threshold_input_buf);
              if (val > 0) rssi_trend_threshold = val;
            }
            threshold_input_active = false;
            threshold_input_len = 0;
            redraw_ssid_list();
          }
        } else if (client_select_analyze_mode) {
          // NEU 2.30.6: Zahleneingabe fuer die Client-Frame-Analyse (Probe
          // Request), ausgeloest durch 'w' unten - analog zum 'w'-Eingabe-
          // modus in STATE_SSID_SELECT (Punkt 3), nur hier mit dem
          // clients_known-Index statt eines AP-Index.
          // NEU 2.30.11: "wp"+Zahl+Enter (statt nur "w"+Zahl+Enter) macht
          // stattdessen die "Mausefalle" fuer diesen Client scharf - 'p'
          // wird nur akzeptiert, solange noch keine Ziffer eingegeben wurde.
          if (c == 'p' && ssid_input_len == 0 && !client_frametrap_mode && !client_timewatch_mode) {
            client_frametrap_mode = true;
            Serial.print('p');
          } else if (c == 't' && ssid_input_len == 0 && !client_frametrap_mode && !client_timewatch_mode) {
            client_timewatch_mode = true;
            Serial.print('t');
          } else if (c >= '0' && c <= '9') {
            if (ssid_input_len < 19) {
              ssid_input_buf[ssid_input_len] = c;
              ssid_input_len++;
              ssid_input_buf[ssid_input_len] = '\0';
              Serial.print(c);
            }
          } else if (c == 13) {
            Serial.println();
            int idx = (ssid_input_len > 0) ? atoi(ssid_input_buf) : -1;
            ssid_input_len = 0;
            client_select_analyze_mode = false;
            bool mousetrap = client_frametrap_mode;
            bool timewatch = client_timewatch_mode;
            client_frametrap_mode = false;
            client_timewatch_mode = false;
            if (idx >= 0 && idx < clients_known_count) {
              if (timewatch) {
                memcpy(pending_timewatch_mac, clients_known[idx].station, ETH_MAC_LEN);
                timewatch_return_to = 2;
                menu_enter_timewatch_add_desc();
              } else if (mousetrap) {
                // BUGFIX 2.30.12: redraw_ssid_list() direkt danach loeschte
                // den Bildschirm sofort wieder und wischte damit JEDE
                // Rueckmeldung von frametrap_client_arm() weg (Erfolg genauso wie
                // eine Fehlermeldung, z.B. "bereits scharf" oder "Maximal
                // erreicht") - der Nutzer sah nie, was passiert ist. Jetzt
                // bleibt die Meldung stehen; die Liste zeichnet sich beim
                // naechsten normalen Auto-Refresh von selbst neu.
                if (frametrap_client_arm(clients_known[idx].station)) {
                  Serial.println(F(" FrameTrap scharf - wartet im Hintergrund auf den naechsten Probe Request."));
                }
              } else {
                menu_start_client_capture(idx);
              }
            } else {
              redraw_ssid_list();
            }
          }
        } else {
          if (c == 'm') {
            set_sort_field(SORT_MAC);
            redraw_ssid_list();
          } else if (c == 'a') {
            set_sort_field(SORT_LASTSEEN);
            redraw_ssid_list();
          } else if (c == 'r') {
            set_sort_field(SORT_RSSI);
            redraw_ssid_list();
          } else if (c == 'u') {
            // NEU 2.30.14: "unsortiert" - Registrierungsreihenfolge, analog
            // 'u' in Menue 3 (set_ap_sort_field(AP_SORT_NONE)). 'u' war
            // bisher hier "Aktualisierung +5s" - dafuer jetzt '+'/'-'
            // (siehe unten), ebenfalls analog zu Menue 3.
            set_sort_field(SORT_NONE);
            redraw_ssid_list();
          } else if (c == 't') {
            threshold_input_active = true;
            threshold_input_len = 0;
            Serial.printf_P(PSTR("\r\n Neue RSSI-Schwelle in dB (aktuell %d): "), rssi_trend_threshold);
          } else if (c == '+') {
            // NEU 2.30.14: ersetzt 'u' fuer die Aktualisierungsrate, da 'u'
            // jetzt "unsortiert" ist (analog Menue 3, das +/- schon vorher
            // aus demselben Grund einsetzt).
            list_refresh_sec += 5;
            redraw_ssid_list();
          } else if (c == '-') {
            list_refresh_sec -= 5;
            if (list_refresh_sec < 5) list_refresh_sec = 5;
            redraw_ssid_list();
          } else if (c == 'i' && current_list_mode >= 1) {
            // NEU 2.17.2: Ignore-Filter in allen Varianten (1/2/3)
            // NEU 2.20.0 FEATURE 2: auch in Var.1 verfügbar
            list_hide_inactive = !list_hide_inactive;
            redraw_ssid_list();
          } else if (c == 'v') {
            // NEU 2.21.0: Toggle Vendor-Anzeige (Herstellererkennung)
            // NEU 2.26.x: gilt jetzt auch fuer Variante 2 (kombinierte SSID-
            // Ansicht), gleiches Flag, Lookup laeuft ueber den Vendor-Cache.
            show_vendors_in_menu3a = !show_vendors_in_menu3a;
            redraw_ssid_list();
          } else if (c == 'w' && current_list_mode == 1) {
            // NEU 2.30.6: w+Zahl+Enter startet die Probe-Request-Analyse
            // eines Clients. Bewusst nur Modus 1 (einzelner AP) - nur dort
            // werden die dafuer noetigen Nummern ("#"-Spalte) angezeigt;
            // Modi 2/3 (SSID-Buendelung/Multi-AP) bleiben unveraendert.
            client_select_analyze_mode = true;
            ssid_input_len = 0;
            ssid_input_buf[0] = '\0';
            Serial.print('w');
          } else if (c == 'b' && current_list_mode >= 1) {
            // NEU 2.30.39: Auftrag 1 - Hintergrundverkehr starten.
            // NEU 2.30.49: Auftrag 2 - jetzt auch fuer Modus 2 (SSID-
            // Buendelung) und Modus 3 (Multi-AP) statt nur Modus 1.
            traffic_stats_request_start(current_list_mode, current_list_ap_index, ssid_list_combined_ssid);
          }
        }
        break;

      case STATE_TRAFFIC_STATS:
        // Erfassung laeuft im Callback; hier nur Navigation und Refresh.
        if (traffic_detail_selecting) {
          if (c >= '0' && c <= '9') {
            if (traffic_detail_input_len < sizeof(traffic_detail_input_buf) - 1) {
              traffic_detail_input_buf[traffic_detail_input_len++] = c;
              traffic_detail_input_buf[traffic_detail_input_len] = '\0';
              Serial.print(c);
            }
          } else if (c == 13) {
            Serial.println();
            int idx = (traffic_detail_input_len > 0) ? atoi(traffic_detail_input_buf) : -1;
            traffic_detail_selecting = false;
            traffic_detail_input_len = 0;
            traffic_detail_input_buf[0] = '\0';
            traffic_detail_start(idx);
            if (menu_state == STATE_TRAFFIC_STATS) traffic_stats_redraw();
          }
        } else if (c == 'x') {
          traffic_stats_detailed_view = !traffic_stats_detailed_view;
          traffic_stats_redraw();
        } else if (c == 's') {
          traffic_stats_save_to_file();
        } else if (c == 'e') {
          traffic_stats_stop();
          menu_state = STATE_MENU;
          menu_draw();
        } else if (c == 'd') {
          traffic_detail_selecting = true;
          traffic_detail_input_len = 0;
          traffic_detail_input_buf[0] = '\0';
          Serial.print(F("\r\n Client-Index: "));
        }
        break;

      case STATE_TRAFFIC_DETAIL:
        if (c == 'r') traffic_detail_redraw();
        else if (c == 's') traffic_detail_save_to_file();
        break;

      case STATE_SETTINGS:
        if (settings_input_active) {
          if (c >= '0' && c <= '9') {
            if (settings_input_len < 4) {
              settings_input_buf[settings_input_len] = c;
              settings_input_len++;
              settings_input_buf[settings_input_len] = '\0';
              Serial.print(c);
            }
          } else if (c == 13) {
            Serial.println();
            if (settings_input_len > 0) {
              int val = atoi(settings_input_buf);
              if (val < 0) val = 0;
              // NEU 2.19.0: targets angepasst nach Reordering
              if (settings_input_target == 6) two_col_threshold_ssids = val;
              else if (settings_input_target == 7) two_col_threshold_devices = val;
            }
            settings_input_active = false;
            settings_input_len = 0;
            menu_enter_settings();
          }
        } else if (c == '1') {
          // Taste 1: Terminal-Modus (bleibt 1)
          color_enabled = !color_enabled;
          menu_enter_settings();
        } else if (c == '2') {
          // Taste 2: Start-Modus (war 5)
          startup_online = !startup_online;
          save_single_setting("startup_online", startup_online ? 1 : 0);
          menu_enter_settings();
        } else if (c == '3') {
          // Taste 3: Betriebsmodus (war 2)
          toggle_online_mode();
          menu_enter_settings();
        } else if (c == '4') {
          // Taste 4: Auto-Save (war 7)
          auto_save_on_overflow = !auto_save_on_overflow;
          menu_enter_settings();
        } else if (c == '5') {
          // Taste 5: Auto-Offline (war 8)
          auto_offline_on_overflow = !auto_offline_on_overflow;
          menu_enter_settings();
        } else if (c == '6') {
          // Taste 6: SSID-Liste zweispaltig (war 4)
          settings_input_active = true;
          settings_input_target = 6;
          settings_input_len = 0;
          Serial.printf_P(PSTR("\r\n Neuer Schwellenwert SSID-Liste (0=aus, aktuell %d): "), two_col_threshold_ssids);
        } else if (c == '7') {
          // Taste 7: Geraeteliste zweispaltig (war 3)
          settings_input_active = true;
          settings_input_target = 7;
          settings_input_len = 0;
          Serial.printf_P(PSTR("\r\n Neuer Schwellenwert Geraeteliste (0=aus, aktuell %d): "), two_col_threshold_devices);
        } else if (c == '8') {
          // Taste 8: NTFY (war 6)
          menu_enter_notif_settings();
        } else if (c == '9') {
          // Taste 9: NTP (bleibt 9)
          menu_enter_ntp_settings();
        } else if (c == 'a' || c == 'A') {
          // Taste a: Auto-Load (bleibt a)
          menu_state = STATE_NTP_TEXT_EDIT;  // Nutze existierenden Text-Edit State
          Serial.println(F("\r\n Auto-Load Dateiname eingeben (z.B. 'autosave_260801_103727'):"));
          Serial.println(F(" Oder leer eingeben um Auto-Load zu deaktivieren."));
          Serial.print(F(" > "));
          ntp_text_edit_len = 0;
          ntp_text_edit_buf[0] = '\0';
          ntp_edit_target = 7;  // Marker für Auto-Load Dateiname
        } else if (c == 'c' || c == 'C') {
          // NEU 2.30.5: Taste c: AP-Modus (fuer Punkt 7)
          menu_enter_apmode_settings();
        } else if (c == 's') {
          save_all_settings();
        } else if (c == 'E') {
          menu_enter_hidden_settings();
        }
        break;

      case STATE_APMODE_SETTINGS:
        if (c == '1') {
          ap_mode_enabled = !ap_mode_enabled;
          menu_enter_apmode_settings();
        } else if (c == '2') {
          menu_enter_apmode_text_edit(1);
        } else if (c == '3') {
          menu_enter_apmode_text_edit(2);
        } else if (c == 's') {
          save_all_settings();
        }
        break;

      case STATE_APMODE_TEXT_EDIT:
        if (c == 13) {
          Serial.println();
          char* dest = (ap_mode_edit_target == 1) ? ap_mode_ssid : ap_mode_pass;
          int destmax = (ap_mode_edit_target == 1) ? 33 : 65;  // ap_mode_ssid[33], ap_mode_pass[65]
          strncpy(dest, ap_mode_text_edit_buf, destmax - 1);
          dest[destmax - 1] = '\0';
          menu_enter_apmode_settings();
        } else if ((unsigned char)c >= 32 && (unsigned char)c < 127 && c != '=') {
          if (ap_mode_text_edit_len < 95) {
            ap_mode_text_edit_buf[ap_mode_text_edit_len] = c;
            ap_mode_text_edit_len++;
            ap_mode_text_edit_buf[ap_mode_text_edit_len] = '\0';
            Serial.print(ap_mode_edit_target == 2 ? '*' : c);  // Passwort maskiert anzeigen
          }
        }
        break;

      case STATE_NOTIF_SETTINGS:
        if (notif_interval_input_active) {
          if (c >= '0' && c <= '9') {
            if (notif_interval_input_len < 4) {
              notif_interval_input_buf[notif_interval_input_len] = c;
              notif_interval_input_len++;
              notif_interval_input_buf[notif_interval_input_len] = '\0';
              Serial.print(c);
            }
          } else if (c == 13) {
            Serial.println();
            if (notif_interval_input_len > 0) {
              int val = atoi(notif_interval_input_buf);
              if (val < 1) val = 1;
              notif_interval_min = val;
            }
            notif_interval_input_active = false;
            notif_interval_input_len = 0;
            menu_enter_notif_settings();
          }
        } else {
          if (c == '1') {
            notif_enabled = !notif_enabled;
            menu_enter_notif_settings();
          } else if (c == '2') {
            menu_enter_notif_text_edit(1);
          } else if (c == '3') {
            menu_enter_notif_text_edit(2);
          } else if (c == '4') {
            menu_enter_notif_text_edit(3);
          } else if (c == '5') {
            notif_interval_input_active = true;
            notif_interval_input_len = 0;
            Serial.printf_P(PSTR("\r\n Neues Intervall in Minuten (aktuell %d): "), notif_interval_min);
          } else if (c == '6') {
            // NEU 2.20.9 BUG6: Punkt 6 = Message-Header (war Punkt 7)
            menu_enter_notif_text_edit(4);
          } else if (c == '7') {
            // NEU 2.20.9 BUG6: Punkt 7 = Inhalt (war Punkt 6)
            notif_content_mode = (notif_content_mode + 1) % 4;
            menu_enter_notif_settings();
          } else if (c == '8') {
            // NEU 2.20.9 BUG6: Punkt 8 = SSID-Filter (war Punkt 7, nur bei Mode 1/2)
            if (notif_content_mode == 1 || notif_content_mode == 2) {
              menu_enter_notif_text_edit(5);  // target=5 für SSID-Filter
            }
          } else if (c == '9') {
            // NEU 2.20.9 BUG6: Punkt 9 = Senden (war Punkt 8)
            notif_send_pending = true;
            Serial.println(F("\r\n Sende jetzt einmalig (Ausgabe erscheint gleich unten) ..."));
          } else if (c == 's') {
            save_all_settings();
          }
        }
        break;

      case STATE_NOTIF_TEXT_EDIT:
        if (c == 13) {
          Serial.println();
          // NEU 2.20.5 BUG5: notif_edit_target == 4 für Header hinzugefügt
          // NEU 2.20.9 BUG6: notif_edit_target == 5 für SSID-Filter (war fallback)
          // NEU 2.20.12 MAJOR FIX: 
          // 1. destmax MUSS mit Array-Größe übereinstimmen (nicht "gefühlte" Größe!)
          // 2. save_all_settings() entfernt (wird nur bei Taste 's' aufgerufen)
          // 3. Kein Buffer-Overflow mehr möglich
          
          char* dest = (notif_edit_target == 1) ? notif_wifi_ssid :
                       (notif_edit_target == 2) ? notif_wifi_pass :
                       (notif_edit_target == 3) ? notif_channel :
                       (notif_edit_target == 4) ? notif_header_text : notif_ssid_filter;
          
          // NEU 2.20.12: KORREKTE destmax-Werte (Feld-Größe - 1 für \0)
          int destmax = (notif_edit_target == 1) ? 33 :      // notif_wifi_ssid[33]
                        (notif_edit_target == 2) ? 65 :      // notif_wifi_pass[65]
                        (notif_edit_target == 3) ? 24 :      // notif_channel[24]
                        (notif_edit_target == 4) ? 33 : 64;  // notif_header_text[33], notif_ssid_filter[64]
          
          strncpy(dest, notif_text_edit_buf, destmax - 1);
          dest[destmax - 1] = '\0';
          // NEU 2.20.12: Speichern nur bei Taste 's' im NTFY Settings Menü!
          menu_enter_notif_settings();
        } else if ((unsigned char)c >= 32 && (unsigned char)c < 127 && c != '=') {
          // NEU 2.20.12: Input-Limit 95 (96-1 für \0) um Buffer-Overflow zu vermeiden
          if (notif_text_edit_len < 95) {
            notif_text_edit_buf[notif_text_edit_len] = c;
            notif_text_edit_len++;
            notif_text_edit_buf[notif_text_edit_len] = '\0';
            Serial.print(notif_edit_target == 2 ? '*' : c);  // Passwort maskiert anzeigen
          }
        }
        break;

      case STATE_ADC_SETTINGS:
        if (c == '1') {
          // NEU 2.29.0: Spannung kalibrieren - Roh-ADC-Wert wurde beim
          // Aufruf dieses Menues bereits angezeigt (Kontrolle Spannungsteiler).
          menu_state = STATE_NTP_TEXT_EDIT;
          Serial.printf_P(PSTR("\r\nGemessene Spannung in mV eingeben (4-stellig, z.B. 5123 fuer 5,12V):\r\n"));
          Serial.print(F(" > "));
          ntp_text_edit_len = 0;
          ntp_text_edit_buf[0] = '\0';
          ntp_edit_target = 11;  // Marker für ADC-Kalibrierung
        } else if (c == 's') {
          save_all_settings();
        }
        break;

      case STATE_RAM_DEBUG:
        // NEU 2.30.34/2.30.35: Debug RAM Memory - Analyse EIN/AUS, Messwerte
        // loeschen, Call-Chain Analyse EIN/AUS, Call-Chain anzeigen, zurueck.
        // Reine Menuelogik, greift sonst in nichts ein.
        if (c == '1') {
          ram_debug.enabled = !ram_debug.enabled;
          if (ram_debug.enabled) {
            // NEU 2.30.34: Einschalten startet laut Vorgabe eine neue
            // Messperiode - alte Extremwerte werden verworfen.
            ram_debug_reset();
          }
          menu_enter_ram_debug();
        } else if (c == '2') {
          // NEU 2.30.35: setzt zusaetzlich die Call-Chain-Diagnosewerte
          // zurueck (Vorgabe Pkt.16) - keine Benutzereinstellungen betroffen.
          ram_debug_reset();
          call_chain_reset();
          menu_enter_ram_debug();
        } else if (c == '3') {
          // NEU 2.30.35: eigener Schalter, NICHT automatisch mit Punkt 1
          // gekoppelt (Vorgabe Pkt.2/14).
          call_chain_enabled = !call_chain_enabled;
          if (call_chain_enabled) call_chain_reset();  // neue Messperiode
          menu_enter_ram_debug();
        } else if (c == '4') {
          menu_enter_call_chain_view();
        } else if (c == '5') {
          menu_enter_hidden_settings();
        }
        break;

      case STATE_CALL_CHAIN_VIEW:
        // NEU 2.30.35: reine Anzeige - jede Taste (ausser den bereits ueber
        // Backspace/ESC abgedeckten) fuehrt zurueck zu Debug RAM Memory.
        menu_enter_ram_debug();
        break;

      case STATE_NTP_SETTINGS:
        if (c == '1') {
          ntp_enabled = !ntp_enabled;
          menu_enter_ntp_settings();
        } else if (c == '2') {
          menu_enter_ntp_text_edit(1);
        } else if (c == '3') {
          menu_enter_ntp_text_edit(2);
        } else if (c == '4') {
          menu_enter_ntp_text_edit(3);
        } else if (c == '5') {
          // NEU 2.17.8: Zeitzone (UTC-Offset) eingeben statt MEZ/MESZ-Toggle
          menu_state = STATE_NTP_TEXT_EDIT;
          Serial.printf_P(PSTR("Zeitzone: UTC-Offset in Stunden eingeben (-12 bis 12, aktuell %+d):\r\n"), ntp_timezone_hours);
          Serial.print(F(" > "));
          ntp_text_edit_len = 0;
          ntp_text_edit_buf[0] = '\0';
          ntp_edit_target = 9;  // Marker für Zeitzone
        } else if (c == '6') {
          // NEU 2.17.8: Daylight Saving Time (automatische Sommer-/
          // Winterzeit) an/aus - ersetzt das alte manuelle MEZ/MESZ-Toggle
          dst_enabled = !dst_enabled;
          save_single_setting("dst_enabled", dst_enabled ? 1 : 0);
          menu_enter_ntp_settings();
        } else if (c == 's') {
          save_all_settings();
        }
        break;

      case STATE_NTP_TEXT_EDIT:
        if (c == 13) {
          Serial.println();
          if (ntp_edit_target == 5) {
            // NEU 2.13.0: Channel-Filter speichern
            // NEU 2.20.6 BUG2: Wenn nichts/Null eingegeben → "alle" (nicht leer!)
            if (ntp_text_edit_len == 0 || strcmp(ntp_text_edit_buf, "0") == 0 || strcmp(ntp_text_edit_buf, "") == 0) {
              strcpy(channel_filter, "alle");
            } else {
              strncpy(channel_filter, ntp_text_edit_buf, 31);
              channel_filter[31] = '\0';
            }
            save_single_setting("channel_filter", 0);
            save_all_settings();
            menu_enter_hidden_settings();
          } else if (ntp_edit_target == 6) {
            // NEU 2.13.0: Scan-Verweilzeit speichern
            uint16_t new_dwell = (uint16_t)atoi(ntp_text_edit_buf);
            if (new_dwell >= 10 && new_dwell <= 5000) {  // Validierung: 10-5000ms
              channel_dwell_ms = new_dwell;
              save_all_settings();
              menu_enter_hidden_settings();
            } else {
              Serial.println(F(" Fehler: Verweilzeit muss 10-5000 ms sein!"));
              Serial.print(F(" > "));
            }
          } else if (ntp_edit_target == 7) {
            // NEU 2.16.0: Auto-Load Dateiname speichern
            if (ntp_text_edit_len == 0) {
              // Leer eingegeben = deaktivieren
              autoload_filename[0] = '\0';
              Serial.println(F(" Auto-Load deaktiviert."));
            } else {
              // Dateiname speichern - strippe .txt Endung falls vorhanden
              strncpy(autoload_filename, ntp_text_edit_buf, 39);
              autoload_filename[39] = '\0';
              // Entferne .txt am Ende, falls eingegeben
              if (strlen(autoload_filename) >= 4) {
                if (strcmp(autoload_filename + strlen(autoload_filename) - 4, ".txt") == 0) {
                  autoload_filename[strlen(autoload_filename) - 4] = '\0';
                }
              }
              Serial.printf_P(PSTR(" Auto-Load aktiviert: '%s'\r\n"), autoload_filename);
            }
            save_all_settings();
            menu_enter_settings();
          } else if (ntp_edit_target == 8) {
            // NEU 2.17.6: Status-LED GPIO-Pin speichern
            if (ntp_text_edit_len == 0) {
              // Leer eingegeben = deaktivieren
              led_write_digital(false);
              status_led_pin = -1;
              Serial.println(F(" Status-LED deaktiviert."));
              save_all_settings();
              menu_enter_hidden_settings();
            } else {
              int new_pin = atoi(ntp_text_edit_buf);
              // Grobe Plausibilitaetspruefung fuer ESP8266 (GPIO 0-16).
              // GPIO 1/3 (TX/RX) und 6-11 (Flash) sind zwar technisch
              // eingebbar, aber i.d.R. nicht sinnvoll nutzbar - deshalb nur
              // ein Hinweis, keine harte Sperre (evtl. bewusst gewaehlt).
              if (new_pin < 0 || new_pin > 16) {
                Serial.println(F(" Fehler: Pin muss zwischen 0 und 16 liegen!"));
                Serial.print(F(" > "));
              } else {
                status_led_pin = new_pin;
                led_apply_pin_config();
                status_led_test_state = false;
                save_all_settings();
                Serial.printf_P(PSTR(" Status-LED-Pin gesetzt: GPIO %d\r\n"), status_led_pin);
                if (new_pin == 1 || new_pin == 3 || (new_pin >= 6 && new_pin <= 11) || new_pin == 16) {
                  Serial.println(F(" Hinweis: dieser Pin hat auf dem ESP8266 typischerweise eine"));
                  Serial.println(F(" Sonderfunktion (seriell/Flash) oder keine PWM-Hardware (GPIO16)."));
                }
                menu_enter_hidden_settings();
              }
            }
          } else if (ntp_edit_target == 9) {
            // NEU 2.17.8: Zeitzone (UTC-Offset) speichern
            int val = atoi(ntp_text_edit_buf);
            if (val < -12 || val > 12) {
              Serial.println(F(" Fehler: Wert muss zwischen -12 und 12 liegen!"));
              Serial.print(F(" > "));
            } else {
              ntp_timezone_hours = val;
              save_all_settings();
              Serial.printf_P(PSTR(" Zeitzone gesetzt: UTC%+d\r\n"), ntp_timezone_hours);
              menu_enter_ntp_settings();
            }
          } else if (ntp_edit_target == 10) {
            // NEU 2.21.0: Signalisierungspin GPIO speichern
            if (ntp_text_edit_len == 0) {
              // Leer eingegeben = deaktivieren
              signal_force_off();
              signal_pin = -1;
              Serial.println(F(" Signalisierungspin deaktiviert."));
              save_all_settings();
              menu_enter_hidden_settings();
            } else {
              int new_pin = atoi(ntp_text_edit_buf);
              // Grobe Plausibilitaetspruefung fuer ESP8266 (GPIO 0-16).
              // GPIO 1/3 (TX/RX) und 6-11 (Flash) sind zwar technisch
              // eingebbar, aber i.d.R. nicht sinnvoll nutzbar - deshalb nur
              // ein Hinweis, keine harte Sperre (evtl. bewusst gewaehlt).
              if (new_pin < 0 || new_pin > 16) {
                Serial.println(F(" Fehler: Pin muss zwischen 0 und 16 liegen!"));
                Serial.print(F(" > "));
              } else {
                signal_pin = new_pin;
                signal_apply_pin_config();
                signal_test_state = false;
                save_all_settings();
                Serial.printf_P(PSTR(" Signalisierungspin gesetzt: GPIO %d\r\n"), signal_pin);
                if (new_pin == 1 || new_pin == 3 || (new_pin >= 6 && new_pin <= 11) || new_pin == 16) {
                  Serial.println(F(" Hinweis: dieser Pin hat auf dem ESP8266 typischerweise eine"));
                  Serial.println(F(" Sonderfunktion (seriell/Flash) oder keine PWM-Hardware (GPIO16)."));
                }
                menu_enter_hidden_settings();
              }
            }
          } else if (ntp_edit_target == 11) {
            // NEU 2.29.0: ADC-Kalibrierung speichern - gemessene Spannung
            // (mV) zusammen mit einem FRISCH genommenen ADC-Rohwert (nicht
            // dem beim Menue-Aufruf nur angezeigten) als Kalibrierpunkt.
            if (ntp_text_edit_len == 0) {
              Serial.println(F(" Abgebrochen (keine Eingabe)."));
              menu_enter_adc_settings();
            } else {
              int new_mv = atoi(ntp_text_edit_buf);
              if (new_mv < 500 || new_mv > 9999) {
                Serial.println(F(" Fehler: Spannung muss zwischen 500 und 9999 mV liegen!"));
                Serial.print(F(" > "));
              } else {
                int fresh_raw = analogRead(A0);
                if (fresh_raw <= 0) {
                  Serial.println(F(" Fehler: ADC liest 0 - Kalibrierung nicht moeglich (Spannungsteiler pruefen)."));
                  Serial.print(F(" > "));
                } else {
                  adc_calib_raw = (uint16_t)fresh_raw;
                  adc_calib_mv = (uint16_t)new_mv;
                  save_all_settings();
                  Serial.printf_P(PSTR(" Kalibrierung gespeichert: %d mV bei ADC-Rohwert %d\r\n"), adc_calib_mv, adc_calib_raw);
                  menu_enter_adc_settings();
                }
              }
            }
          } else {
            // Alt: NTP Text-Edit (SSID, Passwort, Server)
            char* dest = (ntp_edit_target == 1) ? ntp_wifi_ssid :
                         (ntp_edit_target == 2) ? ntp_wifi_pass : ntp_server;
            int destmax = (ntp_edit_target == 1) ? 32 :
                          (ntp_edit_target == 2) ? 64 : 64;
            strncpy(dest, ntp_text_edit_buf, destmax);
            dest[destmax] = '\0';
            menu_enter_ntp_settings();
          }
        } else if ((unsigned char)c >= 32 && (unsigned char)c < 127 && c != '=') {
          if (ntp_text_edit_len < 64) {
            ntp_text_edit_buf[ntp_text_edit_len] = c;
            ntp_text_edit_len++;
            ntp_text_edit_buf[ntp_text_edit_len] = '\0';
            Serial.print(ntp_edit_target == 2 ? '*' : c);  // Passwort maskiert anzeigen
          }
        }
        break;

      case STATE_HELP:
        // reine Anzeige, nur Backspace/ESC (oben global behandelt) fuehrt zurueck
        break;

      case STATE_INFO:
        // reine Anzeige, nur Backspace/ESC (oben global behandelt) fuehrt zurueck
        break;

      case STATE_HIDDEN_SETTINGS:
        if (c == '1') {
          show_logo = !show_logo;
          save_single_setting("show_logo", show_logo ? 1 : 0);
          menu_enter_hidden_settings();
        } else if (c == '2') {
          // NEU 2.12.0: Auto-Save täglich Toggle
          auto_save_enabled = !auto_save_enabled;
          save_single_setting("auto_save_enabled", auto_save_enabled ? 1 : 0);
          menu_enter_hidden_settings();
        } else if (c == '3') {
          // NEU 2.13.0: Channel-Filter eingeben
          menu_state = STATE_NTP_TEXT_EDIT;  // Nutze existierenden Text-Edit State
          Serial.println(F("Channel-Filter eingeben (z.B. 'alle' oder '1,6,11'):"));
          Serial.print(F(" > "));
          ntp_text_edit_len = 0;
          ntp_text_edit_buf[0] = '\0';
          ntp_edit_target = 5;  // Marker für Channel-Filter
        } else if (c == '4') {
          // NEU 2.13.0: Scan-Verweilzeit eingeben
          menu_state = STATE_NTP_TEXT_EDIT;
          Serial.printf_P(PSTR("Scan-Verweilzeit pro Kanal in ms (aktuell %u):\r\n"), channel_dwell_ms);
          Serial.print(F(" > "));
          ntp_text_edit_len = 0;
          ntp_text_edit_buf[0] = '\0';
          ntp_edit_target = 6;  // Marker für Dwell-Zeit
        } else if (c == '5') {
          // NEU 2.17.6: Status-LED GPIO-Pin eingeben
          menu_state = STATE_NTP_TEXT_EDIT;
          Serial.printf_P(PSTR("Status-LED GPIO-Pin eingeben (aktuell %s), leer = deaktivieren:\r\n"),
                         status_led_pin >= 0 ? String(status_led_pin).c_str() : "aus");
          Serial.print(F(" > "));
          ntp_text_edit_len = 0;
          ntp_text_edit_buf[0] = '\0';
          ntp_edit_target = 8;  // Marker für Status-LED-Pin
        } else if (c == '6' && status_led_pin >= 0) {
          // NEU 2.17.7: LED-Polaritaet umschalten (aktiv-LOW Onboard-LEDs)
          status_led_active_low = !status_led_active_low;
          save_single_setting("status_led_active_low", status_led_active_low ? 1 : 0);
          status_led_test_state = false;
          led_write_digital(false);
          menu_enter_hidden_settings();
        } else if (c == '9') {
          // NEU 2.21.0: Signalisierungspin GPIO eingeben
          menu_state = STATE_NTP_TEXT_EDIT;
          Serial.printf_P(PSTR("Signalisierungspin GPIO eingeben (aktuell %s), leer = deaktivieren:\r\n"),
                         signal_pin >= 0 ? String(signal_pin).c_str() : "aus");
          Serial.print(F(" > "));
          ntp_text_edit_len = 0;
          ntp_text_edit_buf[0] = '\0';
          ntp_edit_target = 10;  // Marker für Signal-PIN
        } else if (c == 's' || c == 'S') {
          // NEU 2.21.0: Signal aktiviert/deaktiviert Toggle
          if (signal_pin >= 0) {
            signal_enabled = !signal_enabled;
            save_single_setting("signal_enabled", signal_enabled ? 1 : 0);
            if (!signal_enabled) signal_force_off();
            Serial.printf_P(PSTR("\r\n Signal: %s\r\n"), signal_enabled ? "Aktiviert" : "Deaktiviert");
            menu_enter_hidden_settings();
          } else {
            Serial.println(F("\r\n Fehler: Kein Signalisierungspin konfiguriert!"));
            Serial.print(F(" > "));
          }
        } else if (c == '7') {
          // NEU 2.20.0 FEATURE 4: ESP-Neustart mit Sicherheitsabfrage
          menu_enter_esp_restart_confirm();
        } else if (c == '8') {
          // NEU 2.20.6 BUG8: Werksreset jetzt als letzter Punkt (Punkt 8)
          menu_enter_factory_reset_confirm();
        } else if (c == 'k' || c == 'K') {
          scenario_compression_enabled = !scenario_compression_enabled;
          save_single_setting("scenario_compression_enabled", scenario_compression_enabled ? 1 : 0);
          Serial.printf_P(PSTR("\r\n Szenario-Kompression: %s\r\n"), scenario_compression_enabled ? "EIN" : "AUS");
          menu_enter_hidden_settings();
        } else if (c == 'd' || c == 'D') {
          // NEU 2.30.32: Taste d: ADC-Einstellungen (Akkuspannung) - bisher
          // unter 'b' in den normalen Einstellungen, jetzt hierher verschoben
          menu_enter_adc_settings();
        } else if (c == 'r' || c == 'R') {
          // NEU 2.30.34: Taste r: Debug RAM Memory (passive RAM-/Stack-Diagnose)
          menu_enter_ram_debug();
        } else if (c == 't') {
          // NEU 2.19.0: Test LED Toggle (vereinfacht, ohne Polarität)
          if (status_led_pin >= 0) {
            status_led_test_state = !status_led_test_state;
            led_write_digital(status_led_test_state);
            Serial.printf_P(PSTR("\r\n [TEST] Status-LED an Pin %d: %s\r\n"),
                           status_led_pin, status_led_test_state ? "EIN" : "AUS");
          } else {
            Serial.println(F("\r\n [TEST] Keine Status-LED konfiguriert!"));
          }
        } else if (c == 'b' || c == 'B') {
          // NEU 2.21.0: Test Signal Toggle
          if (signal_pin >= 0 && signal_enabled) {
            signal_test_state = !signal_test_state;
            signal_write_digital(signal_test_state);
            Serial.printf_P(PSTR("\r\n [TEST] Signal an Pin %d: %s\r\n"),
                          signal_pin, signal_test_state ? "AN" : "AUS");
          } else if (signal_pin >= 0) {
            Serial.println(F("\r\n Fehler: Signal ist deaktiviert! (S-Taste zum Aktivieren)"));
          } else {
            Serial.println(F("\r\n Fehler: Kein Signalisierungspin konfiguriert!"));
          }
          Serial.print(F(" > "));
        } else if (c == 'A') {
          // NEU 2.14.0 HIDDEN: Shift+A → Auto-Save TEST Funktion
          // Triggert den Auto-Save Prozess sofort, als würde gerade 00:00 Uhr passiert
          // Versteckte Funktion zur Test ohne bis Mitternacht/24h zu warten
          Serial.println(F("\r\n [AUTO-SAVE TEST] Triggere Auto-Save jetzt..."));
          perform_auto_save_with_timestamp();
          // Aktualisiere timestamp, damit nicht sofort wieder getriggert wird
          auto_save_last_run_millis = millis();
          Serial.println(F(" [AUTO-SAVE TEST] Fertig. Datei sollte jetzt in Punkt 6 sichtbar sein."));
          delay(1000);  // kurze Pause für Lesbarkeit
          menu_enter_hidden_settings();
        }
        break;

      case STATE_FACTORY_RESET_CONFIRM:
        if (isalnum((unsigned char)c)) {
          if (factory_reset_input_len < 10) {
            factory_reset_input_buf[factory_reset_input_len] = c;
            factory_reset_input_len++;
            factory_reset_input_buf[factory_reset_input_len] = '\0';
            Serial.print(c);
          }
        } else if (c == 13) {
          Serial.println();
          if (strcmp(factory_reset_input_buf, "LOESCHEN") == 0) {
            perform_factory_reset();  // kehrt nie zurueck (Endlosschleife)
          } else {
            Serial.println(F(" Abgebrochen (falsches Bestaetigungswort)."));
            menu_enter_hidden_settings();
          }
        }
        break;

      case STATE_ESP_RESTART_CONFIRM:
        // NEU 2.20.0 FEATURE 4: ESP-Neustart mit Sicherheitsabfrage (ja/nein)
        if (isalnum((unsigned char)c)) {
          if (factory_reset_input_len < 5) {  // "ja" + Puffer = max 5
            factory_reset_input_buf[factory_reset_input_len] = c;
            factory_reset_input_len++;
            factory_reset_input_buf[factory_reset_input_len] = '\0';
            Serial.print(c);
          }
        } else if (c == 13) {
          Serial.println();
          if (strcmp(factory_reset_input_buf, "ja") == 0) {
            // Neustart bestätigt!
            Serial.println(F("\r\n========================================================"));
            Serial.println(F(" Neustart in 2 Sekunden..."));
            Serial.println(F("========================================================"));
            delay(2000);
            ESP.restart();  // Neustart auslösen - kehrt nie zurück
          } else {
            Serial.println(F(" Abgebrochen (falsches Bestaetigungswort - geben Sie 'ja' ein)."));
            menu_enter_hidden_settings();
          }
        }
        break;

      case STATE_SAVE_FILENAME:
        if (isalnum((unsigned char)c) || c == '_' || c == '-') {
          if (save_filename_len < 24) {
            save_filename_buf[save_filename_len] = c;
            save_filename_len++;
            save_filename_buf[save_filename_len] = '\0';
            Serial.print(c);
          }
        } else if (c == 13) {
          Serial.println();
          if (save_filename_len > 0) {
            save_current_lists(save_filename_buf);
          } else {
            Serial.println(F(" Kein Dateiname eingegeben, abgebrochen."));
          }
          menu_state = STATE_MENU;
          menu_draw();
        }
        break;

      case STATE_FILE_LIST:
        if (file_view_waiting) {
          file_view_waiting = false;
          file_send_mode = false;
          menu_enter_file_list();
          break;
        }
        // NEU 2.25.0: File Protection - Taste 'h' mit zwei Funktionen
        if (c == 'h' && file_input_len == 0 && !file_delete_mode && !file_load_mode && !file_protect_mode && !file_send_mode) {
          // 'h' allein gedrückt → starte file_protect_mode (wartet auf Ziffer oder Enter)
          file_protect_mode = true;
          file_protect_input_len = 0;
          Serial.print(F("h"));
        } else if (c == 'd' && file_input_len == 0 && !file_delete_mode && !file_load_mode && !file_protect_mode && !file_send_mode) {
          file_delete_mode = true;
          Serial.print(F("d"));
        } else if (c == 'l' && file_input_len == 0 && !file_delete_mode && !file_load_mode && !file_protect_mode && !file_send_mode) {
          file_load_mode = true;
          Serial.print(F("l"));
        } else if (c == 's' && file_input_len == 0 && !file_delete_mode && !file_load_mode && !file_protect_mode && !file_send_mode) {
          file_send_mode = true;
          Serial.print('s');
        } else if (c >= '0' && c <= '9') {
          // NEU 2.25.0: Unterscheide zwischen file_protect_mode und normal
          int* target_buf_len = file_protect_mode ? &file_protect_input_len : &file_input_len;
          char* target_buf = file_protect_mode ? file_protect_input_buf : file_input_buf;
          int max_len = 2;
          
          if (*target_buf_len < max_len) {
            target_buf[*target_buf_len] = c;
            (*target_buf_len)++;
            target_buf[*target_buf_len] = '\0';
            Serial.print(c);
          }
        } else if (c == 13) {
          Serial.println();
          
          // NEU 2.25.0: Handle file_protect_mode (h allein oder h + Nummer)
          if (file_protect_mode) {
            // Sonderfall: nur 'h' + Enter ohne Nummer → toggle show_hidden
            if (file_protect_input_len == 0) {
              show_hidden = !show_hidden;
              if (show_hidden) {
                Serial.println(F(" [OK] Geschuetzte Dateien sind nun sichtbar"));
              } else {
                Serial.println(F(" [OK] Geschuetzte Dateien sind nun verborgen"));
              }
            } else {
              // 'h' + Nummer + Enter → toggle Schutzstatus der Datei
              int idx = atoi(file_protect_input_buf);
              if (idx >= 0 && idx < file_list_count) {
                bool now_protected = toggle_file_protection(file_list_names[idx]);
                if (now_protected) {
                  Serial.printf_P(PSTR(" [OK] %s ist jetzt geschuetzt\r\n"), file_list_names[idx]);
                } else {
                  Serial.printf_P(PSTR(" [OK] %s ist nicht mehr geschuetzt\r\n"), file_list_names[idx]);
                }
              } else {
                Serial.println(F(" Ungueltige Auswahl."));
              }
            }
            file_protect_mode = false;
            file_protect_input_len = 0;
            menu_enter_file_list();
            return;
          }
          
          if (file_input_len > 0) {
            int idx = atoi(file_input_buf);
            if (idx >= 0 && idx < file_list_count) {
              char path[40];
              snprintf_P(path, sizeof(path), PSTR("/%s"), file_list_names[idx]);
              if (file_delete_mode) {
                // NEU 2.25.0: Prüfe Schutzstatus vor dem Löschen
                // NEU 2.29.6 BUGFIX: "&& !show_hidden" entfernt - show_hidden
                // steuert nur, ob geschuetzte Dateien in der Liste SICHTBAR
                // sind (siehe Filter oben), hat aber nichts mit dem Loesch-
                // schutz zu tun. Durch die gemeinsame Bedingung liess sich
                // eine geschuetzte Datei bisher ohne jede Warnung loeschen,
                // sobald show_hidden aktiv war (z.B. nach 'h'+Enter).
                if (is_file_protected(file_list_names[idx])) {
                  Serial.printf_P(PSTR(" [ERROR] %s ist geschuetzt! (Taste h druecken zum Entsperren)\r\n"), file_list_names[idx]);
                } else {
                  LittleFS.remove(path);
                  Serial.printf_P(PSTR(" Geloescht: %s\r\n"), file_list_names[idx]);
                }
              } else if (file_send_mode) {
                notif_send_file(path);
              } else if (file_load_mode) {
                // NEU 2.17.2 Bugfix: file_list_names[] enthaelt den Dateinamen
                // MIT ".txt"-Endung (so liefert es LittleFS.openDir()).
                // load_scenario_file() haengt selbst nochmal ".txt" an (wie
                // auch beim Autoload ueblich, das konsequent ohne Endung
                // arbeitet) - ohne Strip wurde also "name.txt.txt" gesucht,
                // die Datei nie gefunden und das Laden brach mit Fehler ab.
                char load_name[32];
                strncpy(load_name, file_list_names[idx], sizeof(load_name) - 1);
                load_name[sizeof(load_name) - 1] = '\0';
                int nlen = strlen(load_name);
                if (nlen >= 4 && strcmp(load_name + nlen - 4, ".txt") == 0) {
                  load_name[nlen - 4] = '\0';
                }
                // Vor dem Laden automatisch offline schalten, damit das
                // geladene Szenario nicht versehentlich mit Live-Daten
                // aus einer anderen Umgebung vermischt wird.
                online_mode = false;
                Serial.printf_P(PSTR(" Lade %s als aktiven Scan-Zustand (System automatisch offline geschaltet)...\r\n"), load_name);
                load_scenario_file(load_name);
                menu_state = STATE_MENU;
                menu_draw();
                return;
              } else {
                Serial.println(F("-------------------------------------------------------------------------------------"));
                scenario_print_file_content(path);
                Serial.println();
                Serial.println(F("-------------------------------------------------------------------------------------"));
                Serial.println(F(" Beliebige Taste = zurueck zur Dateiliste"));
                file_view_waiting = true;
              }
            } else {
              Serial.println(F(" Ungueltige Auswahl."));
            }
          }
          if (!file_view_waiting) {
            file_send_mode = false;
            menu_enter_file_list();  // Liste neu zeichnen (z.B. nach Loeschen aktualisiert)
          }
        }
        break;

      case STATE_WATCHLIST:
        if (watch_delete_mode) {
          if (c >= '0' && c <= '9') {
            if (watch_delete_input_len < 3) {
              watch_delete_input_buf[watch_delete_input_len] = c;
              watch_delete_input_len++;
              watch_delete_input_buf[watch_delete_input_len] = '\0';
              Serial.print(c);
            }
          } else if (c == 13) {
            Serial.println();
            if (watch_delete_input_len > 0) {
              int idx = atoi(watch_delete_input_buf);
              if (idx >= 0 && idx < watchlist_count) {
                remove_watchlist_entry(idx);  // NEU 2.30.11: gemeinsame Loeschen-Grundoperation
                save_watchlist();
                Serial.println(F(" Eintrag aus der Watchlist geloescht."));
              } else {
                Serial.println(F(" Ungueltige Auswahl."));
              }
            }
            watch_delete_mode = false;
            watch_delete_input_len = 0;
            menu_enter_watchlist();
          }
        } else {
          if (c == 'a') {
            menu_enter_watchlist_add_mac();
          } else if (c == 'x') {
            watch_delete_mode = true;
            watch_delete_input_len = 0;
            Serial.print(F("x"));
          } else if (c == 'u') {
            watchlist_refresh_sec += 5;
            menu_enter_watchlist();
          } else if (c == 'd') {
            watchlist_refresh_sec -= 5;
            if (watchlist_refresh_sec < 5) watchlist_refresh_sec = 5;
            menu_enter_watchlist();
          } else if (c == 'v') {
            // NEU 2.23.0: Toggle Vendor-Anzeige (Herstellererkennung) auch
            // in Menue 4 (MAC-Watchlist) - analog zu Menue 3a.
            // On-Demand Lookup beim Rendern (kein Batch-Cache!)
            show_vendors_in_watchlist = !show_vendors_in_watchlist;
            menu_enter_watchlist();
          } else if (c == 'p') {
            // NEU 2.27.1 REQ-4: Toggle Rueckkehr-Signalisierung
            enable_return_pulse = !enable_return_pulse;
            menu_enter_watchlist();
          }
        }
        break;

      case STATE_WATCHLIST_ADD_MAC:
        {
          char lc = c;
          if (lc >= 'A' && lc <= 'F') lc = lc - 'A' + 'a';
          if ((lc >= '0' && lc <= '9') || (lc >= 'a' && lc <= 'f')) {
            if (watch_mac_input_len < 12) {
              watch_mac_input_buf[watch_mac_input_len] = lc;
              watch_mac_input_len++;
              watch_mac_input_buf[watch_mac_input_len] = '\0';
              Serial.print(lc);
            }
          } else if (c == 13) {
            Serial.println();
            if (watch_mac_input_len == 12) {
              parse_mac_hex(watch_mac_input_buf, pending_watch_mac);
              menu_enter_watchlist_add_desc();
            } else {
              Serial.println(F(" Ungueltig: es werden genau 12 Hex-Zeichen benoetigt."));
              watch_mac_input_len = 0;
              watch_mac_input_buf[0] = '\0';
              Serial.print(F(" MAC: "));
            }
          }
        }
        break;

      case STATE_WATCHLIST_ADD_DESC:
        if (c == 13) {
          Serial.println();
          add_or_update_watchlist_entry(pending_watch_mac, watch_desc_input_buf);
          save_watchlist();
          Serial.println(F(" Watchlist-Eintrag gespeichert."));
          menu_enter_watchlist();
        } else if ((unsigned char)c >= 32 && (unsigned char)c < 127 && c != '=') {
          if (watch_desc_input_len < 32) {
            watch_desc_input_buf[watch_desc_input_len] = c;
            watch_desc_input_len++;
            watch_desc_input_buf[watch_desc_input_len] = '\0';
            Serial.print(c);
          }
        }
        break;

      case STATE_TIMEWATCH_ADD_DESC:
        if (c == 13) {
          Serial.println();
          add_or_update_watchlist_entry(pending_timewatch_mac, watch_desc_input_buf);

          int idx = -1;
          for (int i = 0; i < watchlist_count; i++) {
            if (!memcmp(watchlist[i].mac, pending_timewatch_mac, ETH_MAC_LEN)) {
              idx = i;
              break;
            }
          }

          if (idx >= 0) {
            if (!watchlist_entry_is_timewatched(idx)) {
              int existing_len = strlen(watchlist[idx].desc);
              int marker_len = strlen(TIMEWATCH_MARKER);
              int max_existing = 32 - marker_len;
              if (existing_len > max_existing) watchlist[idx].desc[max_existing] = '\0';
              strncat(watchlist[idx].desc, TIMEWATCH_MARKER,
                      32 - strlen(watchlist[idx].desc));
              watchlist[idx].desc[32] = '\0';
            }
            save_watchlist();
            Serial.println(F(" TimeWatch aktiviert."));
          } else {
            Serial.println(F(" TimeWatch konnte nicht aktiviert werden (Watchlist voll)."));
          }

          int origin = timewatch_return_to;
          timewatch_return_to = 0;
          watch_desc_input_len = 0;
          watch_desc_input_buf[0] = '\0';
          if (origin == 1) menu_enter_ssid_select();
          else if (origin == 2) redraw_ssid_list();
          else { menu_state = STATE_MENU; menu_draw(); }
        } else if ((unsigned char)c >= 32 && (unsigned char)c < 127 && c != '=') {
          if (watch_desc_input_len < 10) {
            watch_desc_input_buf[watch_desc_input_len] = c;
            watch_desc_input_len++;
            watch_desc_input_buf[watch_desc_input_len] = '\0';
            Serial.print(c);
          }
        }
        break;

      case STATE_BEACON_ANALYSIS:
        // NEU 2.29.17: reine Warte-/Ergebnisanzeige - Backspace/ESC werden
        // bereits zentral oben behandelt (cancel_beacon_capture() +
        // menu_go_back()), alle anderen Tasten werden hier bewusst ignoriert.
        break;

      case STATE_CLIENT_ANALYSIS:
        // NEU 2.30.6: analog zu STATE_BEACON_ANALYSIS oben (reine Warte-/
        // Ergebnisanzeige, Backspace/ESC zentral behandelt).
        break;

      // ==================== NEU 2.30.24: Filter-Untermenue ====================
      case STATE_FILTER_MENU:
        if (c == '1') {
          filter_has_mac = true;
          menu_enter_filter_mac_input();
        } else if (c == '2') {
          filter_has_mac = false;
          menu_enter_filter_criteria();
        } else if (c == '3') {
          menu_enter_mac_lookup_input();
        } else if (c == '4') {
          menu_enter_timing_test_mac_input();
        }
        break;

      case STATE_FILTER_MAC_INPUT:
        {
          char lc = c;
          if (lc >= 'A' && lc <= 'F') lc = lc - 'A' + 'a';
          if ((lc >= '0' && lc <= '9') || (lc >= 'a' && lc <= 'f')) {
            if (filter_mac_input_len < 12) {
              filter_mac_input_buf[filter_mac_input_len] = lc;
              filter_mac_input_len++;
              filter_mac_input_buf[filter_mac_input_len] = '\0';
              Serial.print(lc);
            }
          } else if (c == 13) {
            Serial.println();
            if (filter_mac_input_len == 12) {
              parse_mac_hex(filter_mac_input_buf, filter_mac);
              menu_enter_filter_criteria();
            } else {
              Serial.println(F(" Ungueltig: es werden genau 12 Hex-Zeichen benoetigt."));
              filter_mac_input_len = 0;
              filter_mac_input_buf[0] = '\0';
              Serial.print(F(" MAC-Adresse eingeben (12 Hex-Zeichen): "));
            }
          }
        }
        break;

      case STATE_FILTER_CRITERIA:
        if (filter_has_mac && c == '1') {
          filter_dir_out = !filter_dir_out;
          draw_filter_criteria_screen();
        } else if (filter_has_mac && c == '2') {
          filter_dir_in = !filter_dir_in;
          draw_filter_criteria_screen();
        } else if (c == '3') {
          filter_sel_beacon = !filter_sel_beacon;
          draw_filter_criteria_screen();
        } else if (c == '4') {
          bool on = !(filter_sel_probe_req || filter_sel_probe_resp);
          filter_sel_probe_req = on;
          filter_sel_probe_resp = on;
          draw_filter_criteria_screen();
        } else if (c == '5') {
          filter_mgmt_mask = (filter_mgmt_mask == FILTER_MGMT_FULL_MASK) ? 0 : FILTER_MGMT_FULL_MASK;
          draw_filter_criteria_screen();
        } else if (c == '6') {
          filter_ctrl_mask = (filter_ctrl_mask == FILTER_CTRL_FULL_MASK) ? 0 : FILTER_CTRL_FULL_MASK;
          draw_filter_criteria_screen();
        } else if (c == '7') {
          filter_data_mask = (filter_data_mask == FILTER_DATA_FULL_MASK) ? 0 : FILTER_DATA_FULL_MASK;
          draw_filter_criteria_screen();
        } else if (c == 'p') {
          menu_enter_filter_sub_probe();
        } else if (c == 'm') {
          menu_enter_filter_sub_mgmt();
        } else if (c == 'c') {
          menu_enter_filter_sub_ctrl();
        } else if (c == 'd') {
          menu_enter_filter_sub_data();
        } else if (c == 's') {
          menu_enter_filter_live();
        }
        break;

      case STATE_FILTER_SUB_PROBE:
        if (c == 'a') {
          filter_sel_probe_req = !filter_sel_probe_req;
          menu_enter_filter_sub_probe();
        } else if (c == 'b') {
          filter_sel_probe_resp = !filter_sel_probe_resp;
          menu_enter_filter_sub_probe();
        }
        break;

      case STATE_FILTER_SUB_MGMT:
        if (c == 'a') { filter_mgmt_mask ^= ((uint16_t)1<<0); menu_enter_filter_sub_mgmt(); }
        else if (c == 'b') { filter_mgmt_mask ^= ((uint16_t)1<<1); menu_enter_filter_sub_mgmt(); }
        else if (c == 'c') { filter_mgmt_mask ^= ((uint16_t)1<<2); menu_enter_filter_sub_mgmt(); }
        else if (c == 'd') { filter_mgmt_mask ^= ((uint16_t)1<<3); menu_enter_filter_sub_mgmt(); }
        else if (c == 'e') { filter_mgmt_mask ^= ((uint16_t)1<<9); menu_enter_filter_sub_mgmt(); }
        else if (c == 'f') { filter_mgmt_mask ^= ((uint16_t)1<<10); menu_enter_filter_sub_mgmt(); }
        else if (c == 'g') { filter_mgmt_mask ^= ((uint16_t)1<<11); menu_enter_filter_sub_mgmt(); }
        else if (c == 'h') { filter_mgmt_mask ^= ((uint16_t)1<<12); menu_enter_filter_sub_mgmt(); }
        else if (c == 'i') { filter_mgmt_mask ^= ((uint16_t)1<<13); menu_enter_filter_sub_mgmt(); }
        else if (c == 's') { filter_mgmt_mask ^= FILTER_MGMT_MISC_MASK; menu_enter_filter_sub_mgmt(); }
        break;

      case STATE_FILTER_SUB_CTRL:
        if (c == 'a') { filter_ctrl_mask ^= ((uint16_t)1<<8); menu_enter_filter_sub_ctrl(); }
        else if (c == 'b') { filter_ctrl_mask ^= ((uint16_t)1<<9); menu_enter_filter_sub_ctrl(); }
        else if (c == 'c') { filter_ctrl_mask ^= ((uint16_t)1<<10); menu_enter_filter_sub_ctrl(); }
        else if (c == 'd') { filter_ctrl_mask ^= ((uint16_t)1<<11); menu_enter_filter_sub_ctrl(); }
        else if (c == 'e') { filter_ctrl_mask ^= ((uint16_t)1<<12); menu_enter_filter_sub_ctrl(); }
        else if (c == 'f') { filter_ctrl_mask ^= ((uint16_t)1<<13); menu_enter_filter_sub_ctrl(); }
        else if (c == 's') { filter_ctrl_mask ^= FILTER_CTRL_MISC_MASK; menu_enter_filter_sub_ctrl(); }
        break;

      case STATE_FILTER_SUB_DATA:
        if (c == 'a') { filter_data_mask ^= ((uint16_t)1<<0); menu_enter_filter_sub_data(); }
        else if (c == 'b') { filter_data_mask ^= ((uint16_t)1<<4); menu_enter_filter_sub_data(); }
        else if (c == 'c') { filter_data_mask ^= ((uint16_t)1<<8); menu_enter_filter_sub_data(); }
        else if (c == 'd') { filter_data_mask ^= ((uint16_t)1<<12); menu_enter_filter_sub_data(); }
        else if (c == 's') { filter_data_mask ^= FILTER_DATA_MISC_MASK; menu_enter_filter_sub_data(); }
        break;

      case STATE_FILTER_LIVE:
        // Reine Live-Ausgabe, keine Tasteneingaben ausser Backspace/ESC
        // (zentral oben behandelt -> menu_go_back() -> zurueck zu den
        // Kriterien, siehe Nutzerwunsch).
        break;

      // ==================== NEU 2.30.29: MAC nachschlagen (Punkt 2.3) ====================
      case STATE_MAC_LOOKUP_INPUT:
        {
          char lc = c;
          if (lc >= 'A' && lc <= 'F') lc = lc - 'A' + 'a';
          if ((lc >= '0' && lc <= '9') || (lc >= 'a' && lc <= 'f')) {
            if (lookup_mac_input_len < 12) {
              lookup_mac_input_buf[lookup_mac_input_len] = lc;
              lookup_mac_input_len++;
              lookup_mac_input_buf[lookup_mac_input_len] = '\0';
              Serial.print(lc);
            }
          } else if (c == 13) {
            Serial.println();
            if (lookup_mac_input_len == 12) {
              parse_mac_hex(lookup_mac_input_buf, lookup_mac_result_mac);
              menu_enter_mac_lookup_result();
            } else {
              Serial.println(F(" Ungueltig: es werden genau 12 Hex-Zeichen benoetigt."));
              lookup_mac_input_len = 0;
              lookup_mac_input_buf[0] = '\0';
              Serial.print(F(" MAC-Adresse eingeben (12 Hex-Zeichen): "));
            }
          }
        }
        break;

      case STATE_MAC_LOOKUP_RESULT:
        // Reine Ergebnisanzeige, Backspace/ESC zentral behandelt (siehe
        // menu_go_back() - fuehrt zurueck zur Eingabe fuer den naechsten
        // Nachschlag).
        break;

      // ==================== NEU 2.30.32: Timing-Test (Punkt 2.4) ====================
      case STATE_TIMING_TEST_MAC_INPUT:
        {
          char lc = c;
          if (lc >= 'A' && lc <= 'F') lc = lc - 'A' + 'a';
          if ((lc >= '0' && lc <= '9') || (lc >= 'a' && lc <= 'f')) {
            if (timing_test_mac_input_len < 12) {
              timing_test_mac_input_buf[timing_test_mac_input_len] = lc;
              timing_test_mac_input_len++;
              timing_test_mac_input_buf[timing_test_mac_input_len] = '\0';
              Serial.print(lc);
            }
          } else if (c == 13) {
            Serial.println();
            if (timing_test_mac_input_len == 12) {
              parse_mac_hex(timing_test_mac_input_buf, timing_test_mac);
              menu_enter_timing_test_running();
            } else {
              Serial.println(F(" Ungueltig: es werden genau 12 Hex-Zeichen benoetigt."));
              timing_test_mac_input_len = 0;
              timing_test_mac_input_buf[0] = '\0';
              Serial.print(F(" MAC-Adresse eingeben (12 Hex-Zeichen): "));
            }
          }
        }
        break;

      case STATE_TIMING_TEST_RUNNING:
        // Bewusst leer - waehrend der Test laeuft, soll ihn ausser dem
        // zentral behandelten Backspace/ESC (siehe menu_go_back()) NICHTS
        // stoeren, auch keine sonstige Tastenauswertung hier.
        break;

      case STATE_TIMING_TEST_RESULT:
        // Reine Ergebnisanzeige, Backspace/ESC zentral behandelt.
        break;
    }
  }
}
