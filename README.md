# Meteostanice

Toto je projekt kroužku bastlení s rodiči z letního pololetí roku 2023. 

## Módy
Meteostanice je možné používat ve dvou módech. Podle toho zdali je připojena v lokální síti či nikoliv. Módy se liší pouze v tom, že pokud máte stanici připojenou k Wi-Fi, tak je možné se na ní připojit pomocí Vašeho telefonu či jiného zařízení a nechat si zobrazit teplotu a vlhkost ve webové stránce. V obou případech funguje display stejně, takže pokud se nechcete koukat přes webový prohlížeč na naměřené teploty, tak není potřeba si s tímto krokem lámat hlavu.
### Stanice není připojená k Wi-Fi
Stanici v tomto módu čeká, až se bude moci připojit na lokální Wi-Fi. Pro to aby to mohla udělat je nutné, jí předat ssid (jméno) a heslo k Vaší domácí Wi-Fi. Pro tento účel meteostanice vytvoří přístupový bod jehož jméno se objeví na horním řádku displaye.
Po připojení na přístupový bod je potřeba zadat do prohlížeče kam zadáváte doménu zadat IP adresu napsanou na displayi na druhém řádku. V tomto případě je IP adresa nastavena na 192.168.0.10. Po zadání adresy do prohlížeče by se Vám měla zobrazit webová stránka na které je možné vyplnit jméno a heslo lokální Wi-Fi sítě.
Do webové stránky zadejte Vaše přístupové údaje a potvrďte, poté začne blikat LED dioda na stanici označující, že se stanice snaží připojit na lokální síť. Poté až blikání ustane tak je Vaše stanice úspěšně připojena k lokální síti. 
Pokud blikání do cca půl minuty nepřestane tak je velice pravděpodobné, že jste udělali někde chybu při zadávání přihlašovacích údajů do stanice a stanice se nemůže připojit. Pokud se Vám toto stane tak je potřeba kkliknout na tlačítko RST_WIFI, ktera vymaže Wi-Fi nastavení a následně je potřeba restartovat zařízení pomocí tlačítka RST nebo zapnutím a vypnutím. Tím uvedete stanici do továrního nastavení a můžete to zkusit znovu.
Po zadání přihlašovacích údajů k Wi-Fi síti si je meteostanice sama uloží do paměti a bude se poté vždy automaticky připojovat.
### Stanice je připojena k Wi-Fi
V tomto módu máte Vaši stanici připojenou k Wi-Fi síti. Meteostanice Vám po svém zapnutí na display vypíše, že je připojena a napíše Vám IP adresu, kterou dostala přiřazenou od Vaše routeru (přístupového bodu). Tuto adresu je dobré si poznamenat, protože při každém restartu může meteostanice dostat jinou IP adresu pod kterou se na ni můžete připojit.
Po zadání IP adresy zařízení do prohlížeče Vaše telefonu či jiného zařízení se Vám objeví stránka s aktuálními naměřenými hodnotami a s možností vymazat přihlašovací údaje k lokální síti a tím opět uvést zařízení do předchozího módu.

#### Poznámka na závěr
Je důležité brát v potaz to, že se jedná o poměrně slabý čip a může se tak stát to, že bude prodleva načítání stránek trošku delší než jste zvyklí u běžných webových stránek. Ze stejného důvodu je omezen maximální počet připojených zařízení v prvním módu na 1 zařízení. 
