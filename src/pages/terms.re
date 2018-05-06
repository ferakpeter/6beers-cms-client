let component = ReasonReact.statelessComponent("Terms");

let make = _children => {
  ...component,
  render: _self =>
    <div className="section section-terms" id="terms">
      <div className="container">
        <div className="row"> <br /> </div>
        <div className="row">

            <h1> (ReasonReact.stringToElement("Terms & Conditions")) </h1>
            <h3> (ReasonReact.stringToElement("1. Site Contents")) </h3>
            <p>
              (
                ReasonReact.stringToElement(
                  "Unless otherwise noted, the design of the Site, the Site as a whole and all materials that are part of the Site\n      (collectively, 'Contents') are copyrights, trademarks, trade dress or other intellectual properties owned, controlled\n      or licensed by 6beers brewing co. or its subsidiaries and affiliates. Any use of the Contents without Nordstrom's\n      express written consent is strictly prohibited.",
                )
              )
            </p>
            <h3>
              (
                ReasonReact.stringToElement(
                  "2. Links to Other Websites and Services",
                )
              )
            </h3>
            <p>
              (
                ReasonReact.stringToElement(
                  "This website may include links to other Internet sites maintained by third parties. 6beers provides 'Linked Sites'\n      to users solely as a convenience. You access Linked Sites at your own risk and by accessing them you leave the\n      6beers website.",
                )
              )
            </p>
            <h3>
              (ReasonReact.stringToElement("3. Creative- and Trademarks"))
            </h3>
            <p>
              (
                ReasonReact.stringToElement(
                  "6beers.at strives to comply to trademark and copyright laws in all our publications, including images, graphics,\n      sound, video, and text elements. Content created by 6beers (including images, graphics, sound, video, and text\n      elements) can only be used and replicated by express written consent by 6beers.",
                )
              )
            </p>
            <h3> (ReasonReact.stringToElement("5. Privacy")) </h3>
            <p>
              (
                ReasonReact.stringToElement(
                  "In case the website prompts the user for personal or business related data (emails, names, addresses) the data\n      will not be shared with any third parties unless the user is notified and agrees to the procedure. Usage and\n      payment for the websites services can be done with anonymous data or pseudonyms, as long as it is technically\n      feasible. The usage of information published in the imprint or similar content including postal addresses, telefon\n      and fax numbers, or email addresses cannot be used to deliver information that was not explicitely requested\n      by 6beers. We reserve our rights to take legal steps against publishers of such 'Spam emails'.",
                )
              )
            </p>
            <h3>
              (ReasonReact.stringToElement("6. Legal force of Disclaimer"))
            </h3>
            <p>
              (
                ReasonReact.stringToElement(
                  "This Disclaimer is to be understood as part of the web offering of 6beers. If parts of the disclaimer should not\n      abide to current law, the valid content is to be understood as valid.",
                )
              )
            </p>
            <h3> (ReasonReact.stringToElement("7. Tracking")) </h3>
            <p>
              (
                ReasonReact.stringToElement(
                  "6beers uses Tracking software of third parties in order to monitor the usage of the site. The analysis tools use\n      Cookies, which are text files saved to the users computer hard-drive. These files contain information about the\n      user, such as IP-addresses, browser type, timestamps, length of usage, viewed pages, and produced clickstream-data.\n      Most browsers allow the user to control the usage of Cookies, Tracking software, or offer features to remove\n      such data from the hard-drive. We would like to highlight that the restriction of Cookies usage and Tracking\n      software can limit the functionality of the website.",
                )
              )
            </p>
            <h3> (ReasonReact.stringToElement("Google Analytics")) </h3>
            <p>
              (
                ReasonReact.stringToElement(
                  "is used as Tracking software. This is a service of Google Inc. (1600 Amphitheatre Parkway, Mountain View, CA 94043,\n      USA). Google Analytics uses 'Cookies'. The user data resulting from Tracking (including the users IP-address)\n      are sent to servers owned by Google situated in the USA. In case of activating anonymous IP addresses the IP-address\n      will be shortened to the member states of the European Union, or the members of the European Economy treaty by\n      Google. Only in special cases will the full IP-address delivered to the servers of Google in the USA and then\n      shortened on the server. Google will use this information in our name, in order to create reports of website\n      usage. In all cases Google will not link the users IP-address to other recorded data. The user can control the\n      installation of Cookies through browser settings. We would like to highlight that in these cases the user may\n      not be able to use the full functionality of the website. The user can restrict the information saved in the\n      Cookie (including the IP-address) by installing the following browser plugin:",
                )
              )
              <a href="http://tools.google.com/dlpage/gaoptout?hl=de">
                (
                  ReasonReact.stringToElement(
                    "http://tools.google.com/dlpage/gaoptout?hl=de",
                  )
                )
              </a>
              (
                ReasonReact.stringToElement(
                  ".\n      For more information please visit",
                )
              )
              <a
                href="http://www.google.com/intl/de/analytics/privacyoverview.html">
                (
                  ReasonReact.stringToElement(
                    "http://www.google.com/intl/de/analytics/privacyoverview.html",
                  )
                )
              </a>
              (ReasonReact.stringToElement("."))
            </p>
            <h3> (ReasonReact.stringToElement("8. Social Plugins")) </h3>
            <p>
              (
                ReasonReact.stringToElement(
                  "Our websites social plugins are embedded by social network Facebook. The plugins can be recognized by the logo\n      of the company. When visiting a page that uses such plugins (for example: Facebook 'like'), the browser will\n      connect to the servers of the social network. 6beers has no way of finding out which data is transferred. To\n      avoid unwanted data being sent and stored by the social networks the user needs to logout of all social networks\n      before using the website. When using the Socia Connect Button of the various providers (for example: Facebook)\n      while registering, data is sent only with the users consent. For further information about the purpose and scope\n      of the data please turn to the social networks' privacy conditions.",
                )
              )
            </p>
          </div>
          /* <h1>
               (ReasonReact.stringToElement("Allgemeine Geschäftsbedingungen"))
             </h1>
             <h3>
               (ReasonReact.stringToElement("1. Inhalt des Onlineangebotes"))
             </h3>
             <p>
               (
                 ReasonReact.stringToElement(
                   "6beers.at übernimmt keinerlei Gewähr für die Aktualität, Korrektheit, Vollständigkeit oder Qualität der bereitgestellten\n      Informationen. Haftungsansprüche gegen 6beers.at, welche sich auf Schäden materieller oder ideeller Art beziehen,\n      die durch die Nutzung oder Nichtnutzung der dargebotenen Informationen bzw. durch die Nutzung fehlerhafter und\n      unvollständiger Informationen verursacht wurden, sind grundsätzlich ausgeschlossen, sofern seitens 6beers.at\n      kein nachweislich vorsätzliches oder grob fahrlässiges Verschulden vorliegt. Alle Angebote sind freibleibend\n      und unverbindlich. 6beers.at behält es sich ausdrücklich vor, Teile der Seiten oder das gesamte Angebot ohne\n      gesonderte Ankündigung zu verändern, zu ergänzen, zu löschen oder die Veröffentlichung zeitweise oder endgültig\n      einzustellen.",
                 )
               )
             </p>
             <h3> (ReasonReact.stringToElement("2. Verweise und Links")) </h3>
             <p>
               (
                 ReasonReact.stringToElement(
                   "Bei direkten oder indirekten Verweisen auf fremde Webseiten ('Hyperlinks'), die au�\159erhalb des Verantwortungsbereiches\n      des Autors liegen, würde eine Haftungsverpflichtung ausschlie�\159lich in dem Fall in Kraft treten, in dem 6beers.at\n      von den Inhalten Kenntnis hat und es ihm technisch möglich und zumutbar wäre, die Nutzung im Falle rechtswidriger\n      Inhalte zu verhindern. 6beers.at erklärt hiermit ausdrücklich, dass zum Zeitpunkt der Linksetzung keine illegalen\n      Inhalte auf den zu verlinkenden Seiten erkennbar waren. Auf die aktuelle und zukünftige Gestaltung, die Inhalte\n      oder die Urheberschaft der verlinkten/verknüpften Seiten hat 6beers.at keinerlei Einfluss. Deshalb distanziert\n      6beers.at sich hiermit ausdrücklich von allen Inhalten aller verlinkten / verknüpften Seiten, die nach der Linksetzung\n      verändert wurden. Diese Feststellung gilt für alle innerhalb des eigenen Internetangebotes gesetzten Links. Für\n      illegale, fehlerhafte oder unvollständige Inhalte und insbesondere für Schäden, die aus der Nutzung oder Nichtnutzung\n      solcherart dargebotener Informationen entstehen, haftet allein der Anbieter der Seite, auf welche verwiesen wurde,\n      nicht derjenige, der über Links auf die jeweilige Veröffentlichung lediglich verweist.",
                 )
               )
             </p>
             <h3>
               (ReasonReact.stringToElement("3. Urheber- und Kennzeichenrecht"))
             </h3>
             <p>
               (
                 ReasonReact.stringToElement(
                   "6beers.at ist bestrebt, in allen Publikationen die Urheberrechte der verwendeten Bilder, Grafiken, Tondokumente,\n      Videosequenzen und Texte zu beachten, von 6beers.at selbst erstellte Bilder, Grafiken, Tondokumente, Videosequenzen\n      und Texte zu nutzen oder auf lizenzfreie Grafiken, Tondokumente, Videosequenzen und Texte zurückzugreifen. Alle\n      innerhalb des Internetangebotes genannten und ggf. durch Dritte geschützten Marken- und Warenzeichen unterliegen\n      uneingeschränkt den Bestimmungen des jeweils gültigen Kennzeichenrechts und den Besitzrechten der jeweiligen\n      eingetragenen Eigentümer. Allein aufgrund der blo�\159en Nennung ist nicht der Schluss zu ziehen, dass Markenzeichen\n      nicht durch Rechte Dritter geschützt sind! Das Copyright für veröffentlichte, vom Autor selbst erstellte Objekte\n      bleibt allein beim Autor der Seiten. Eine Vervielfältigung oder Verwendung solcher Grafiken, Tondokumente, Videosequenzen\n      und Texte in anderen elektronischen oder gedruckten Publikationen ist ohne ausdrückliche Zustimmung von 6beers.at\n      nicht gestattet.",
                 )
               )
             </p>
             <h3> (ReasonReact.stringToElement("5. Datenschutz")) </h3>
             <p>
               (
                 ReasonReact.stringToElement(
                   "Sofern innerhalb des Internetangebotes die Möglichkeit zur Eingabe persönlicher oder geschäftlicher Daten (Emailadressen,\n      Namen, Anschriften) besteht, so erfolgt die Preisgabe dieser Daten seitens des Nutzers auf ausdrücklich freiwilliger\n      Basis. Die Inanspruchnahme und Bezahlung aller angebotenen Dienste ist - soweit technisch möglich und zumutbar\n      - auch ohne Angabe solcher Daten bzw. unter Angabe anonymisierter Daten oder eines Pseudonyms gestattet, ja sogar\n      erwünscht. Die Nutzung der im Rahmen des Impressums oder vergleichbarer Angaben veröffentlichten Kontaktdaten\n      wie Postanschriften, Telefon- und Faxnummern sowie Emailadressen durch Dritte zur �\156bersendung von nicht ausdrücklich\n      angeforderten Informationen ist nicht gestattet. Rechtliche Schritte gegen die Versender von sogenannten Spam-Mails\n      bei Verstössen gegen dieses Verbot sind ausdrücklich vorbehalten.",
                 )
               )
             </p>
             <h3>
               (
                 ReasonReact.stringToElement(
                   "6. Rechtswirksamkeit dieses Haftungsausschlusses",
                 )
               )
             </h3>
             <p>
               (
                 ReasonReact.stringToElement(
                   "Dieser Haftungsausschluss ist als Teil des Internetangebotes zu betrachten, von dem aus auf diese Seite verwiesen\n      wurde. Sofern Teile oder einzelne Formulierungen dieses Textes der geltenden Rechtslage nicht, nicht mehr oder\n      nicht vollständig entsprechen sollten, bleiben die übrigen Teile des Dokumentes in ihrem Inhalt und ihrer Gültigkeit\n      davon unberührt.",
                 )
               )
             </p>
             <h3> (ReasonReact.stringToElement("7. Tracking")) </h3>
             <p>
               (
                 ReasonReact.stringToElement(
                   "Wir setzen die Tracking Software anderer Hersteller ein, um die Nutzung der Website, der Inhalte und der Dienstleistungen\n      durch Sie zu analysieren. Diese Analysewerkzeuge verwenden Cookies, bei denen es sich um Textdateien handelt,\n      die von der Website auf der Festplatte Ihres Computers gespeichert werden und bestimmte Informationen und Daten\n      über Sie und Ihre Zugriffe auf die Website erheben, wie z. B. Ihre IP-Adresse, Ihr Browsertyp, Uhrzeit und Dauer\n      Ihres Besuches, die von Ihnen aufgesuchten Seiten der Website und andere Clickstream-Daten. Die meisten Webbrowser\n      ermöglichen es Ihnen, Cookies und Tracking Software von der Festplatte Ihres Computers zu löschen, eine Warnmeldung\n      vor der Speicherung zu erhalten oder die Speicherung von Cookies oder Tracking Software generell zu untersagen.\n      Wenn Sie wissen möchten, wie dies funktioniert, dann lesen Sie bitte die Bedienungsanleitung oder die Hilfeseiten\n      Ihres Browsers. Wir weisen Sie aber daraufhin, dass die Ablehnung von Cookies oder Tracking Software den Funktionsumfang\n      der Website erheblich einschränken kann.",
                 )
               )
             </p>
             <h3> (ReasonReact.stringToElement("Google Analytics")) </h3>
             <p>
               (
                 ReasonReact.stringToElement(
                   "ist eine von uns eingesetzte Tracking Software; dabei handelt es sich um einen Webanalysedienst der Google Inc.\n      (1600 Amphitheatre Parkway, Mountain View, CA 94043, USA). Google Analytics verwendet auch �\128\158Cookies�\128\156. Die durch\n      den Cookie erzeugten Informationen über Ihre Benutzung dieser Website (einschlie�\159lich Ihrer IP-Adresse) werden\n      üblicherweise an einen Server von Google in den USA übermittelt und dort gespeichert. Im Falle der Aktivierung\n      der IP-Anonymisierung auf unserer Website wird Ihre IP-Adresse von Google jedoch innerhalb von Mitgliedstaaten\n      der Europäischen Union oder in anderen Vertragsstaaten des Abkommens über den Europäischen Wirtschaftsraum zuvor\n      gekürzt. Nur in Ausnahmefällen wird die Ihre volle IP-Adresse an einen Server von Google in den USA übertragen\n      und dort gekürzt. Google wird diese Informationen in unserem Namen benutzen, um Ihre Nutzung der Website auszuwerten,\n      um Berichte über die Websiteaktivitäten für die Websitebetreiber zusammenzustellen und um weitere mit der Website-\n      und der Internetnutzung verbundene Dienstleistungen zu erbringen. Google wird in keinem Fall Ihre IP-Adresse\n      mit anderen Daten von Google in Verbindung bringen. Sie können die Installation der Cookies durch eine entsprechende\n      Einstellung Ihrer Browser-Software verhindern; wir weisen Sie jedoch darauf hin, dass Sie in diesem Fall gegebenenfalls\n      nicht sämtliche Funktionen unserer Website vollumfänglich nutzen können. Sie können die Erfassung von Daten durch\n      den Cookie (einschlie�\159lich Ihrer IP-Adresse) auch verhindern, wenn Sie das unter dem folgenden Link verfügbare\n      Browser-Plugin herunterladen und installieren:",
                 )
               )
               <a href="http://tools.google.com/dlpage/gaoptout?hl=de">
                 (
                   ReasonReact.stringToElement(
                     "http://tools.google.com/dlpage/gaoptout?hl=de",
                   )
                 )
               </a>
               (
                 ReasonReact.stringToElement(
                   ". Weitere Informationen\n      dazu finden Sie unter",
                 )
               )
               <a
                 href="http://www.google.com/intl/de/analytics/privacyoverview.html">
                 (
                   ReasonReact.stringToElement(
                     "http://www.google.com/intl/de/analytics/privacyoverview.html",
                   )
                 )
               </a>
               (ReasonReact.stringToElement("."))
             </p>
             <h3> (ReasonReact.stringToElement("8. Social Plugins")) </h3>
             <p>
               (
                 ReasonReact.stringToElement(
                   "Auf unseren Internetseiten sind Social Plugins der sozialen Netzwerke Facebook eingebunden. Die Plugins erkennen\n      Sie an den Logos der Unternehmen. Wenn Sie unsere Seiten besuchen, die ein solches Plugin (z.B. Facebook �\128\158Gefällt\n      mir�\128\156) enthält, baut Ihr Browser eine direkte Verbindung mit den Servern des Sozialen Netzwerks auf. 6 beers brewing\n      co. erhält keine Kenntnis von den übermittelten Daten. Um zu vermeiden, dass die Sozialen Netzwerke während Ihres\n      Besuchs auf den Websites 6 beers brewing co. Daten über Sie sammeln, müssen Sie sich zu Beginn Ihres Besuchs\n      auf einer Website 6 beers brewing co. bei sämtlichen Sozialen Netzwerken ausloggen. Bei Nutzung der Social Connect\n      Button, der jeweiligen Anbieter (zB: Facebook), im Zuge der Registrierung auf unserer Internetseite, werden nur\n      mit Erlaubnis des Nutzers die Daten zur Anmeldung übertragen. Informationen zu Zweck und Umfang der Datenerhebung\n      durch die Sozialen Netzwerke, die weitere Verarbeitung und Nutzung der Daten durch die Sozialen Netzwerke sowie\n      Ihre diesbezüglichen Rechte und Einstellungsmöglichkeiten zum Schutz Ihrer Privatsphäre entnehmen Sie bitte den\n      Datenschutzhinweisen des jeweiligen Sozialen Netzwerks.",
                 )
               )
             </p> */
      </div>
    </div>,
};