#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <regex>
#include <sstream>
#include <algorithm>
#include <charconv>
#include <iomanip>




/**
	 * Convierte un valor decimal en una representacion hexadecimal de 4 caracteres.
	 * Esta representacion es utilizada para estandarizar los valores a la longitud requerida en memoria en el ensamblador MARIEJS.
	 * 
	 * El metodo asegura una salida en formato hexadecimal con ceros a la izquierda, utilizando manipuladores de flujo de la biblioteca <iomanip>.
	 * 
	 * @param decimalValueFromVariableDefinition El valor decimal de la definicion de variable que se desea convertir a hexadecimal. 
	 *											Se espera que este sea un entero positivo.
	 * 
	 * @return Un `std::string` que contiene la representacion hexadecimal del valor recibido. 
	 *		 Siempre contiene exactamente 4 caracteres (con ceros a la izquierda si es necesario).
	 * 
	 * @throws No lanza excepciones directamente. Sin embargo, si el flujo de cadenas falla (por ejemplo, debido a limites de memoria),
	 *		 podria haber implicaciones de rendimiento en sistemas con recursos limitados.
	 * 
	 * @note Esta documentacion fue escrita por AI. El modelo utilizado fue GPT-4. La prompt utilizada para generarla fue:
	 *	   "Write the documentation for this method. Include mentions and appropiately tagged javadoc comments for the inputs it takes, 
	 *	   return type, exceptions, etc. Please present in your documentation the way the method works and the concepts it utilizes to work. 
	 *	   Write your documentation wrapped in a body tag with white text color. Write in spanish avoiding accentuated letters, 
	 *	   only use english non-accentuated letters, include a mention with a @ note tag that this documenation was written by AI."
	 */
const std::string HexDecimalValueForVariables(int
	decimalValueFromVariableDefinition)
{
	/*Como solo queremos conocer el valor en memoria que se guarda, convertimos a cuatro bits el tamano maximo que
	puede tener un numero*/
	std::stringstream ss;
	ss << std::setw(4) << std::hex << std::setfill('0') << decimalValueFromVariableDefinition;
	return ss.str();

}


/**
 * Convierte una direccion de memoria decimal (decimalVariableAddress) en una representacion hexadecimal 
 * como una cadena, tomando en cuenta un ajuste calculado basado en un salto definido por "jump".
 * 
 * Este metodo es utilizado en el ensamblador MARIEJS para manejar direcciones de memoria y ajustarlas 
 * adecuadamente segun las necesidades de la implementacion. Combina la logica para convertir valores 
 * a hexadecimal y manipula estos valores para asegurar que las direcciones sean unicas y correctas en el contexto del ensamblador.
 * 
 * La representacion hexadecimal que se genera incluye digitos en mayusculas y usa ceros para rellenar 
 * hasta la longitud deseada. Para asegurar consistencia y manejo adecuado, utiliza manipuladores de flujo 
 * proporcionados por `<iomanip>`.
 * 
 * @param decimalVariableAddress Entero que representa la direccion de una variable en decimal. 
 *								 Este es el valor que se desea convertir.
 * @param jump Una referencia constante a un entero que define el ajuste que se aplica a la direccion de la variable.
 *			 Este valor es utilizado para calcular el resultado final que sera representado como una cadena en hexadecimal.
 * 
 * @return Una `std::string` que contiene la direccion ajustada y convertida en formato hexadecimal.
 *		 La longitud de esta cadena asegura que cumple con los formatos esperados.
 * 
 * @throws Este metodo no lanza excepciones directamente. Sin embargo, si la conversion a hexadecimal falla 
 *		 por motivos del entorno, podria implicar problemas de rendimiento o mostrar errores conforme al flujo de salida.
 * 
 * @note Esta documentacion fue escrita por AI. El modelo utilizado fue GPT-4. La prompt fue: 
 * 		 "Write the documentation for this method. Include mentions and appropiately tagged javadoc comments 
 *		 for the inputs it takes, return type, exceptions, etc. Write your documentation wrapped in a body tag 
 *		 with white text color. Write in spanish avoiding accentuated letters, only use english non-accentuated 
 *		 letters, include a mention with a @note tag that this documentation was written by AI."
 */
const std::string HexDecimalToStringForVariables(int decimalVariableAddress, const int& jump)
{
	int afterJumpRecesion = decimalVariableAddress - jump;
	if (decimalVariableAddress < 100)
	{
		/*! Como el valor el menor, sabemos que en sus inicios fue un numero extremadamente pequeno, puede haber sido dos, o tres
		 * y si restamos el line jump siempre perdemos informacion, por tanto para esta seccion, vamos a tener en
		 * cuenta que solo usaremos el primer caracter del line jump y el address originakl
		 */
		std::stringstream ss;
		std::stringstream hexStream;
		hexStream << std::uppercase << std::hex << std::setfill('0') << std::setw(2)
				 << decimalVariableAddress;
		std::string hexValue = hexStream.str();

		char leftmostHexDigit = std::to_string(jump % 1000)[0];

		ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
		   << leftmostHexDigit
		   << hexValue.substr(0);

		return ss.str();
	}
	else
	{
		std::stringstream ss;
		std::stringstream hexStream;
		hexStream << std::uppercase << std::hex << std::setfill('0') << std::setw(2)
				 << afterJumpRecesion;
		std::string hexValue = hexStream.str();

		char leftmostHexDigit = std::to_string(jump % 1000)[0];

		ss  << std::uppercase << std::setw(2) << std::setfill('0')
		   << leftmostHexDigit
		   << hexValue.substr(0);

		return ss.str();
	}
}


/**
* Convierte una direccion decimal de una variable ajustada por un salto en su correspondiente formato hexadecimal.
*
* El metodo toma en cuenta casos distintos dependiendo del tamanio del valor decimal recibido. 
* Si el valor de la direccion decimal es menor a 100, el metodo asegura un manejo especifico utilizando
* el caracter mas significativo del valor `jump` ajustado.
* 
* La representacion hexadecimal generada es consistente con formato MARIE, incluyendo ceros iniciales en caso necesario
* y utilizando letras mayusculas para los digitos hexadecimales A-F.
* 
* @param decimalVariableAddress Entero que representa la direccion decimal de la variable. 
* Este parametro especifica la direccion que sera ajustada y convertida al formato hexadecimal.
* 
* @param jump Una referencia constante a un entero que representa el ajuste de salto de linea. 
* Este parametro se utiliza para calcular la direccion final ajustada antes de convertirla.
* 
* @return Una `std::string` que contiene la direccion ajustada y convertida en formato hexadecimal. 
* La cadena resultante incluye ceros iniciales y asegura un formato de 2 caracteres minimos.
* 
* @throws Este metodo no lanza excepciones explicitamente; sin embargo, errores en los flujos de salida pueden
* ocasionar problemas en tiempo de ejecucion para conversores de cadenas o manipuladores de stream.
* 
* @note La documentacion de este metodo fue generada con AI. Prompt utilizado: 
* "Write the documentation for this method. Include mentions and appropiately tagged javadoc comments for the 
* inputs it takes, return type, exceptions, etc. Please present in your documentation the way the method works 
* and the concepts it utilizes to work. Write your documentation wrapped in a body tag with white text color. Write in 
* spanish avoiding accentuated letters, only use english non-accentuated letters."
*/
const std::string HexDecimalToStringForMethods(const int& hexValueFromOpCode, int decimalValueFromVariableDefinition,
	 int jump)
{
	std::stringstream ss;
	if (decimalValueFromVariableDefinition == 400 or decimalValueFromVariableDefinition == 800 or
	decimalValueFromVariableDefinition == 0)
	{
		ss  << std::hex << std::uppercase << hexValueFromOpCode;
		ss << std::dec << std::setw(3) <<
			std::setfill('0') << decimalValueFromVariableDefinition;
		return ss.str();
	}
	else if (decimalValueFromVariableDefinition == 3072)
	{
			ss << std::hex << std::uppercase << hexValueFromOpCode;
			ss << "C00";
		return ss.str();
	}
	else
	{

		// Convert the entire number to hex
		return std::to_string(hexValueFromOpCode) + HexDecimalToStringForVariables
		(decimalValueFromVariableDefinition, jump).substr(1);
	}

}

/**
    * Genera un mapa predefinido que asocia los nombres de operaciones de MARIEJS con sus respectivos codigos de operacion (opcodes).
    *
    * Este metodo utiliza un `std::map` para asignar cada instruccion de MARIEJS con un entero unico que representa su opcode.
    * Las instrucciones incluidas son tanto directas como indirectas, esenciales para la traduccion del codigo assembler
    * al formato utilizado por MARIEJS.
    * @return Un `std::map` donde cada clave es una `std::string` representando el nombre de una instruccion
    *         y cada valor asociado es un `int` que representa su codigo de operacion (opcode).
    *
    * @throws No genera excepciones directamente, pero en aplicaciones que lo utilicen, es importante asegurar
    *         que las claves del mapa se correspondan estrictamente con las instrucciones definidas por MARIEJS.
    *
    * @note  : Como parte del full disclosure, esta documentacion fue desarollada a traves de Jetbrains AI tooling utilizando
    * la funcionalidad interna para desarollo de documentacion por metodo. La prompt utilizada es la siguiente: "Write the documentation for this method.
    * Include mentions and appropiately tagged javadoc comments for the inputs it takes, return type, exceptions,. etc.
    * Please present in your documentation the way the method works and the concepts it utilizes to work. Write your documentation
    * wrapped in a body tag with white text color. Write in spanish avoiding accentuated letters,
    * only use english non-accentuated letters" . Algunas partes como el texto en blanco no se pudieron poner porque
    el formato de documentacion de C++ es diferente al de Java. El modelo con el que trabaja internamente no estoy
    seguro, porque la manera de decidir de eso es interna al sistema cuando pides documentacion.
    */
const std::map<std::string, int> initOperationCodeMappingImpl() {

    //? 1. Generamos un nuevo mapa con todos los valores precargados de las operaciones
    std::map<std::string, int> marieJSAvailableOperations = {
        {"Load", 1}, {"LoadI", 13},
        {"LoadImmi", 10}, {"Clear", 10},
        {"Store", 2}, {"StoreI", 14},
        {"Add", 3}, {"AddI", 11},
        {"Subt", 4}, {"Halt", 7},
        {"Input", 5}, {"Output", 6},
        {"Skipcond", 8}, {"Jump", 9},
        {"JnS", 0}, {"JumpI", 12},
        {"Org", 16}
    };
    return marieJSAvailableOperations;
}


/**
* Analiza un fragmento de codigo MARIEJS en forma de cadena de texto para identificar
* variables declaradas, junto con su ubicacion en el codigo (en terminos de linea) y sus valores asociados.
*
* Este metodo utiliza `std::regex` para analizar patrones especificos dentro del codigo
* y busca declaraciones de variables que siguen el formato típico de MARIEJS. El resultado
* es un mapa donde cada clave es una variable encontrada, y su valor asociado es un par
* que incluye la linea en que aparece y el valor numerico local (posicional).
*
* El proceso implica:
* 1. Leer el codigo MARIEJS proporcionado linea a linea.
* 2. Buscar declaraciones de variables que coincidan con patrones definidos por una expresion regular.
* 3. Convertir el valor de las variables detectadas segun el formato especificado
* (por ejemplo, DEC, HEX, etc.) y almacenarlas junto con la informacion de linea.
*
* @param sampleMarieCode Un `std::string` que contiene el codigo fuente escrito en MARIEJS.
*
* @return Un `std::map` que asocia cada nombre de variable (`std::string`) con un
* `std::pair` de:
*         - `int`: numero de linea donde aparece la variable.
*         - `long`: valor de la variable convertido segun el formato definido (DEC, HEX, etc.).
*
* @throws No lanza excepciones directamente. Sin embargo, asegurese de pasar un `std::string`
* con contenido valido que respete la sintaxis esperada de MARIEJS para evitar comportamientos
* inesperados.
*
* @note Esta documentacion fue generada utilizando AI (modelo GPT-4) para asistir en su creacion. Esta vez cambie la
prompt para que me diga que modelo lo hizo, pues resulta que es GPT-4o supongo que es uno de los modelos que ofrece
jetbrains! use la misma prompt btw.
*/
const std::map<std::string, std::pair<std::pair<int, long>, std::string>>
    forwardSearchForVariables(const std::string& sampleMarieCode, int& jump)
{
    std::map<std::string, std::pair<std::pair<int, long>, std::string>> variablesFoundWithinCode;
    std::istringstream streamForSampleMarieCode(sampleMarieCode);
    std::string lineBeingReadOnSampleMarieCode;

    int startingAddress = 0;
	int offset = 0;
    int instructionCount = 0;

    std::regex orgPattern = std::regex(R"(^[\s\t]*([oO][rR][gG])[\s\t]+([0-9]+)[\s\t]*(?:(\/)*[a-zA-Z\s])*)");
    /*! Este patron fue disenado por ChatGPT-4o para la identificacion de Patrones de tipo LoadI VariableName*/
    std::regex operationPattern(R"(^[\t\s]*([A-Za-z]+)[\t\s]+([A-Za-z0-9]+)(?:[\t\s]*\/.*)?$)");
    /*! Este patron fue disenado por ChatGPT-4o para la identificacion de subrutinas de MARIEJS*/
    std::regex
        subroutinePattern(R"(^[\s\t]*([A-Za-z][A-Za-z0-9]*)[\s\t]*,[\s\t]*([A-Za-z]+)(?:[\s\t]+([A-Za-z0-9]+))?(?:[\s\t]*\/.*)?$)");
    std::regex variablePattern =
        std::regex(R"(^[\n\r\s\t]*([A-Za-z][A-Za-z0-9_#@\-]*)[\s\t]*,[\s\t]*([dD][eE][cC]|[hH][eE][xX]|[oO][cC][tT]|[bB][iI][nN])[\s\t\r\n]*([0-9A-F]+|[0-9A-F]+)[\n\s\t]*.*$)");
    std::regex singleWordPatter =
        std::regex(R"(^[\t\s]*([cC][lL][eE][aA][rR]|[oO][uU][tT][pP][uU][tT]|[iI][nN][pP][uU][tT]|[hH][aA][lL][tT]|[lL][oO][aA][dD][iI][mM][mM][iI])[\t\s]*(?:\/.*)?$)");


    // First pass: Get the ORG value if present
    while (std::getline(streamForSampleMarieCode, lineBeingReadOnSampleMarieCode)) {
        std::smatch matches;
        if (std::regex_search(lineBeingReadOnSampleMarieCode, matches, orgPattern)) {
            jump = offset = std::stoi(matches[2]);
        }
    }
    streamForSampleMarieCode.clear();
    streamForSampleMarieCode.seekg(0);
    // Second pass: Count instructions
    std::istringstream secondPass(sampleMarieCode);
    while (std::getline(secondPass, lineBeingReadOnSampleMarieCode)) {
        lineBeingReadOnSampleMarieCode.erase(0, lineBeingReadOnSampleMarieCode.find_first_not_of(" \t"));
        if (lineBeingReadOnSampleMarieCode.empty()) continue;
        lineBeingReadOnSampleMarieCode.erase(lineBeingReadOnSampleMarieCode.find_last_not_of(" \t") + 1);

        // Skip comment lines
        if (lineBeingReadOnSampleMarieCode.find("//") == 0) continue;

        std::string upperLine = lineBeingReadOnSampleMarieCode;
        std::transform(upperLine.begin(), upperLine.end(), upperLine.begin(), ::toupper);

        std::smatch matches;
        if (std::regex_match(upperLine, matches, orgPattern)) {
            continue;
        }
        if (std::regex_match(upperLine, matches, variablePattern)) {
            continue;
        }
        if (std::regex_match(upperLine, matches, operationPattern) ||
            std::regex_match(upperLine, matches, subroutinePattern) ||
            std::regex_match(upperLine, matches, singleWordPatter)) {
            instructionCount++;
        }
    }

    std::istringstream thirdPass(sampleMarieCode);
    int memoryLocation = startingAddress + instructionCount + offset;

    while (std::getline(thirdPass, lineBeingReadOnSampleMarieCode)) {
        lineBeingReadOnSampleMarieCode.erase(0, lineBeingReadOnSampleMarieCode.find_first_not_of(" \t"));
        if (lineBeingReadOnSampleMarieCode.empty()) continue;
        lineBeingReadOnSampleMarieCode.erase(lineBeingReadOnSampleMarieCode.find_last_not_of(" \t") + 1);

        std::smatch sub_matches;
        if (std::regex_match(lineBeingReadOnSampleMarieCode, sub_matches, variablePattern)) {
            std::string varName = sub_matches[1];
            std::string format = sub_matches[2];
            std::string value = sub_matches[3];

            varName.erase(0, varName.find_first_not_of(" \t"));
            varName.erase(varName.find_last_not_of(" \t") + 1);

            long numValue = 0;
        	std::string formattedToMatch;
	        for (auto var_name : format)
	        {
		        formattedToMatch += std::toupper(var_name);
	        }
            if ( formattedToMatch == "DEC") {
                numValue = std::stol(value);
            } else if (formattedToMatch == "HEX") {
                numValue = std::stol(value, nullptr, 16);
            } else if (formattedToMatch == "OCT") {
                numValue = std::stol(value, nullptr, 8);
            } else if (formattedToMatch == "BIN") {
                numValue = std::stol(value, nullptr, 2);
            }
            variablesFoundWithinCode[varName] = std::make_pair(std::make_pair(memoryLocation, numValue), format);
            memoryLocation++;
        }
    }

    return variablesFoundWithinCode;
}


/**
 * @brief Realiza una busqueda avanzada en un codigo de MARIE para identificar lineas de operaciones, variables y subrutinas.
 *
 * Este metodo analiza un codigo fuente en formato MARIE y crea un mapa detallado de las operaciones, subrutinas y variables 
 * encontradas en el codigo. Utiliza varias expresiones regulares para identificar tipos de lineas dentro del codigo fuente, 
 * incluyendo operaciones internas, variables, palabras clave y subrutinas. 
 *
 * El metodo realiza varias pasadas sobre el codigo fuente para cumplir con estos objetivos:
 *
 * 1. **Deteccion de Linea ORG**: Busca una linea de tipo `ORG <direccion>` para determinar el punto de inicio (offset) 
 *	de la memoria. Esto se realiza con una expresion regular que valida el patron `ORG` y extrae la direccion indicada.
 *
 * 2. **Conteo de Instrucciones**: Identifica lineas que contienen instrucciones utilizando diversas expresiones regulares:
 *	- Operaciones basicas (`LoadI <VariableName>`, entre otras).
 *	- Subrutinas, en donde una linea contiene un nombre de etiqueta seguido por otros comandos.
 *	- Operaciones de un solo comando como `CLEAR`, `HALT`, etc.
 *
 * 3. **Extraccion de Variables**: Reconoce y valida lineas de variables con formatos como `DEC`, `HEX`, `OCT` y `BIN`. 
 *	Calcula el valor numerico de dichas variables y las almacena asociadas a sus respectivas posiciones de memoria.
 *
 * Utilizando estructuras como `std::map` y `std::regex`, la funcion organiza estos datos en un formato util para 
 * trabajos posteriores, como la conversion del codigo a instrucciones maquina.
 *
 * @param sampleMarieCode Codigo fuente en lenguaje MARIE representado como un `std::string`.
 * 
 * @return Un mapa que relaciona un par clave compuesto por:
 * - `NombreDelMetodo: Linea` (std::pair<std::string, int>)
 * Con un par de valores que representan:
 * - `Operacion Interna` y `Registro/Input` (std::pair<std::string, std::string>).
 * 
 * Ejemplo de salida:
 * [[Load, 0], [NumX, null]]
 * [[MyModule, 1], [Load, 400]]
 *
 * @note Esta documentacion fue creada por AI utilizando el modelo ChatGPT-4o bajo el siguiente prompt: "Write 
 * the documentation for this method. Include mentions and appropiately tagged javadoc comments for the inputs it takes, 
 * return type, exceptions,. etc. Please present in your documentation the way the method works and the concepts 
 * it utilizes to work. Write your documentation wrapped in a body tag with white text color. Write in spanish avoiding 
 * accentuated letters, only use english non-accentuated letters , include, using the @note that this documentation was 
 * creatd by AI and with what model and the prompt".
 */
const std::map< std::pair<std::string, int>, std::pair<std::string, std::string>>
    forwardSearchForLines(const std::string&
sampleMarieCode)
{

    /*! Para empezar a trabajar en la busqueda de las variables, primero necesitamos una estructura para almacenarlas*/
        std::map<std::pair<std::string, int> /*Par que representa Nombre del Metodo: Linea*/,
                 std::pair<std::string, std::string> /*Par que representa Operacion Interna e Input*/>
                 mapaDeOperacionesEncontradas;
    /*! La segunda parte del mapa anterior solo se utiliza cuando tenemos una subrutina!*/
        std::istringstream streamForSampleMarieCode(sampleMarieCode);
        std::string lineBeingReadOnSampleMarieCode;
        const std::map<std::string, int> marieOperations = initOperationCodeMappingImpl();

        int instructionLineAt = 0;
		int offset = 0;
        std::regex orgPattern = std::regex("^[\\s\t]*([oO][rR][gG])[\\s\t]+([0-9]+)[\\s\t]*(?:(\\/)*[a-zA-Z\\s])*");
        /*! Este patron fue disenado por ChatGPT-4o para la identificacion de Patrones de tipo LoadI VariableName*/
        std::regex
    operationPattern(R"(^[\t\s]*([A-Za-z]+)[\t\s]+([A-Za-z0-9]+)(?:[\t\s]*\/.*)?$)");
        /*! Este patron fue disenado por ChatGPT-4o para la identificacion de subrutinas de MARIEJS*/
        std::regex
    subroutinePattern(R"(^[\s\t]*([A-Za-z][A-Za-z0-9]*)[\s\t]*,[\s\t]*([A-Za-z]+)(?:[\s\t]+([A-Za-z0-9]+))?(?:[\s\t]*\/.*)?$)");
        std::regex variablePattern =
            std::regex(R"(^\s*([A-Za-z][A-Za-z0-9_#@\-]*)\s*,\s*((DEC|HEX|OCT|BIN)\s*([0-9]+|[0-9A-F]+))\s*(?:(\/)*[a-zA-Z\s]*)$)");
        std::regex singleWordPatter =
std::regex(
    R"(^[\t\s]*([cC][lL][eE][aA][rR]|[oO][uU][tT][pP][uU][tT]|[iI][nN][pP][uU][tT]|[hH][aA][lL][tT]|[lL][oO][aA][dD][iI][mM][mM][iI])[\t\s]*(?:\/.*)?$)");

    /*
     * Intentamos obtener la entrada ORG Num para determinar el numero de saltos de lineas que tenemos que hacer
     * desde 0. Para esto utilizamos un smatch de C++ para usar una sentencia de regex que encuentra la linea ORG con cualquier
     * numero y la usamos para particionar nuestra string en diferences secciones. La ultima de estas tiene el numero
     * que usamos para determinar los saltos desde 0
     */
        while (std::getline(streamForSampleMarieCode, lineBeingReadOnSampleMarieCode)) {
            std::smatch matches;
            if (std::regex_search(lineBeingReadOnSampleMarieCode, matches, orgPattern)) {
                int orgNumber = std::stoi( matches[2]);
                offset = orgNumber;
            }
        }
    /*
     * Una vez encontramos esta linea, debemos iteraro sobre todas las lineas restantes (incluyendo la anterior, pero
     *  ya no es util y nada la marca) para encontrar las operaciones. El proposito es armar instrucciones que sean
     * del tipo [OpName: Linea],[InputAdicional, InputAdicionalDos]. Un ejemplo de este tipo de linea puede ser
     * [[Load, 0],[NumX, null]] u otra puede ser [[MyModule, 1],[Load, 400]] por ejemplo, en donde el usuario puede
     * enviar lineas anidadas.
     */
                streamForSampleMarieCode.clear();
                streamForSampleMarieCode.seekg(0);
                while (std::getline(streamForSampleMarieCode, lineBeingReadOnSampleMarieCode)) {
            /*! Limpiamos la linea por si acaso*/
            lineBeingReadOnSampleMarieCode.erase(0, lineBeingReadOnSampleMarieCode.find_first_not_of(" \t"));
            if (lineBeingReadOnSampleMarieCode.empty()) continue;
            lineBeingReadOnSampleMarieCode.erase(lineBeingReadOnSampleMarieCode.find_last_not_of(" \t") + 1);

            if (lineBeingReadOnSampleMarieCode.find("//") == 0) continue;

            std::smatch matches;
            /*! Esta linea indica que es una operacion, es decir que tiene la forma de Load smth, Store smth, JumpI,
            JnS etc*/
            if (std::regex_match(lineBeingReadOnSampleMarieCode, matches, operationPattern)) {
                std::string operation = matches[1];
                std::string variable = matches[2];

                /*Capitalizamos para matchear con el formato del mapa interno de operaciones*/
                std::transform(operation.begin(), operation.end(), operation.begin(), ::tolower);
                operation[0] = std::toupper(operation[0]);
                if (operation == "Org"){continue;}

                if (marieOperations.find(operation) != marieOperations.end()) {
                    mapaDeOperacionesEncontradas[std::make_pair(operation, instructionLineAt + offset)] =
                        std::make_pair(operation, variable);
                    instructionLineAt++;
                }
            }
            /*! Esta linea intenta encontrar todas las sentencia de tipo de subrutina, es decir Nombre, Operacion
            (valor o no)*/
            else if (std::regex_match(lineBeingReadOnSampleMarieCode, matches, subroutinePattern))
            {
                std::string label = matches[1];
                std::string operation = matches[2];
                std::string operationTarget = matches[3];
                std::transform(operation.begin(), operation.end(), operation.begin(), ::tolower);
                operation[0] = std::toupper(operation[0]);

                if (marieOperations.find(operation) != marieOperations.end())
                {
                    mapaDeOperacionesEncontradas[std::make_pair(label, instructionLineAt + offset)] =
                        std::make_pair(operation,  operationTarget);
                    instructionLineAt++;
                }
                else
                {
                    std::transform(operation.begin(), operation.end(), operation.begin(), ::tolower);
                    operation[0] = std::toupper(operation[0]);
                    if (marieOperations.find(operation) != marieOperations.end())
                    {
                        mapaDeOperacionesEncontradas[std::make_pair(label, instructionLineAt + offset)] =
                            std::make_pair(operation, "");
                        instructionLineAt++;
                    }
                }
            }
            /*! Si tenemos un halt tambien hay que agregarlo*/
            else if (std::regex_match(lineBeingReadOnSampleMarieCode, matches, singleWordPatter))
            {
            	std::string matchedSingleWord = matches[1].str();
            	std::transform(matchedSingleWord.begin(), matchedSingleWord.end(), matchedSingleWord.begin(), ::tolower);
            	matchedSingleWord[0] = std::toupper(matchedSingleWord[0]);
                mapaDeOperacionesEncontradas[std::make_pair(matchedSingleWord, instructionLineAt + offset)] =
                    std::make_pair(matchedSingleWord, "");
                instructionLineAt++;
            }
            /*! Si tenemos una variable, es decir si no cuadro con nada mas simplemente evitamos*/
            else if (std::regex_match(lineBeingReadOnSampleMarieCode, matches, variablePattern)) {;}
        }



        return mapaDeOperacionesEncontradas;

}


/*
 * El tercer paso a realizar es la conversion entre las variables, y las entradas hacia los opcodes numerico, es decir
 * tenemos que encontrar una forma de unir las variables que encontramos con el mapa de operaciones que encontramos y
 *  formar un nuevo mapa que tiene una llave, es decir la operacion y luego de esta el numero de operacion (es decir
 * en donde va en memoria). El otro parametro del mapa es el pair de string con un valor opcional. Por ejemplo en
 * este caso podemos tener el nombre de una variable y nulo para operaciones como Load o LoadI, Store o StoreI etc
 * etc. Pero para casos como MyModule, Load Var1, esta parte tiene que guardar la operacion interna. Para darnos
 * cuenta que tipo de estructura hay que escribir simplemente tenemos que tener en cuenta que si el operation name no
 *  coincide en ambas partes, entonces tenemos una subrutina!
 */
 /**
 * Este metodo tiene como finalidad mapear las operaciones encontradas en el codigo MARIEJS, asignandoles un numero
 * de operacion (opcode) y un valor auxiliar (variable o direccion). Posteriormente las agrupa y las convierte
 * en un vector ordenado de instrucciones en base a las lineas que las contienen.
 * 
 * El proceso se divide en varias etapas:
 * 
 * 1. **Ordenamiento de las instrucciones**: Los datos de entrada se ordenan en base al numero de linea. Se utiliza
 *    un `std::vector` y la funcion `std::sort` con una comparacion lambda.
 * 
 * 2. **Conversion de las operaciones**: Itera sobre las instrucciones ordenadas y las convierte en su representacion
 *    numerica utilizando un mapeo interno (MARIE opcode). Ademas, maneja variables, subrutinas y numeros constantes.
 * 
 * 3. **Construccion del formato final**: Una vez convertidas, las operaciones se almacenan en un vector como 
 *    cadenas que incluyen la direccion de memoria, el opcode calculado en formato hexadecimal y una descripcion 
 *    legible.
 * 
 * El metodo utiliza conceptos como lambdas para comparacion y manipulacion de contenedores como mapas y vectores 
 * propios de la STL. Adicionalmente, se manejan casos especiales como las operaciones "ORG" que definen saltos.
 * 
 * @param resultsFromSentenceParsing Mapa que contiene las operaciones encontradas en el codigo MARIEJS. La llave 
 * es un par compuesto por el nombre de la operacion y el numero de linea, mientras que el valor es otro par con 
 * detalles (operacion o subrutina y parametro adicional).
 * 
 * @param resultFromVariableParsing Mapa que contiene las variables encontradas en la seccion de datos del codigo 
 * MARIEJS. Cada entrada esta representada por un nombre de variable y su correspondiente valor o direccion.
 * 
 * @param jump Referencia a un entero que define el offset de memoria, calculado a partir de las declaraciones ORG 
 * en el codigo fuente.
 * 
 * @return Un vector de pares que representan las instrucciones convertidas. Cada par contiene el numero de 
 * linea y una cadena que describe tanto su representacion legible como la codificacion hexadecimal.
 * 
 * @throws std::out_of_range En caso de que alguna operacion o variable no pueda ser encontrada en los mapas de 
 * entrada correspondientes.
 * 
 * @note Documentacion generada por AI utilizando el modelo GPT-4o bajo el prompt proporcionado.
 */
const std::vector<std::pair<int, std::string>> mapFromStringToOperationCodeComplete(const std::map< std::pair<std::string,
int>,
std::pair<std::string,
std::string>>& resultsFromSentenceParsing, const std::map<std::string, std::pair<std::pair<int, long>, std::string>>&
resultFromVariableParsing, int& jump)
{

    /*! El primer paso de nuestro programa es ordenar basado en una clave. Esto seria mucho mas facil en Java usando
    Streams y ordenariamos basados en el segundo parametro del std::pair del primer parametro de esta funcion. Pero
    como es C++ lo que haremos sera iterar y crear un vector de estas entradas del mapa.*/
        std::vector<std::pair<std::pair<std::string,int>,std::pair<std::string, std::string>>> vectorDeInstruccionesOrdenadas;
        for (const auto& entry : resultsFromSentenceParsing) {
            vectorDeInstruccionesOrdenadas.push_back(entry);
        }
    /*! Ahora ordenamos el vector basado en el segundo parametro del primer parametro de cada entrada del vector*/
        std::sort(vectorDeInstruccionesOrdenadas.begin(), vectorDeInstruccionesOrdenadas.end(),
                  [](const std::pair<std::pair<std::string,int>,std::pair<std::string, std::string>>& a,
                     const std::pair<std::pair<std::string,int>,std::pair<std::string, std::string>>& b) {
                      return a.first.second < b.first.second;
                  });


    /* El codigo anterior presenta una operacion de tipo lambda que se puede realizar en C++, el primer parametro
     * del lambda es una referencia costante (para evitar modificaion y duplicacion en memoria) a una variable del tipo
     * interno del vector que usamos en el codigo. La idea de este es que la segunda variable tiene el mismo tipo, lo
     * que nos permite evaluar su valor basados simplemente en sus parametros internos. Para ordenar, realizamos una
     * comparacion basada en el segundo parametro del primer parametro del vector, es decir, el numero de operacion
     * que se guarda en memoria. Con esto al final tenemos un arreglo ordenado desde 0 hacia n, ya que
    */
    /*
     * Una vez ordenado, lo que tenemos que hacer es agrupar estas operaciones basandonos en el nombre de sus
     * variables y el valor de las operaciones. para esto creamos un nuevo vector, en donde se guardara las
     * operaciones del sistema ya realizadas y presentadas en el formato solicitado desde un principio.
     */

        std::vector<std::pair<int, std::string>> vectorDeOperacionesYaRealizadas;
        const std::map<std::string, int> marieOperations = initOperationCodeMappingImpl();

        for (const auto& orderedEntry : vectorDeInstruccionesOrdenadas)
        {
            /*Tenemos tres casos posibles, el primero es que sea un ORG, en el cual saltamos de linea^^ ni siquiera
            lo agregramos porque no sirve para mas que definir el salto de direcciones. El segundo es si tanto el
            caller como el receiver son iguales, si lo son entonces tenemos que simplemente revisar si la variable es
             un numero o texto, si es texto buscamos por una variable, si no es una variable buscamos por instruccion
             . El tercero es el de que las instrucciones no sean las mismas, usualmente eso es una querida subrutina,
              y para esto el trabajo es simplemente manejar la operacion contingua*/
            if (orderedEntry.first.first == "Org")
            {
                /*!NO hacemos nada*/
                continue;
            }
            else if (orderedEntry.first.first == orderedEntry.second.first)
            {
                /*En este caso sabemos que es una operacion de Tipo Load, Store, LoadI, JumpI, JnS, Add, Subt,
                cualquiera que tenga un operador adicional a su lado, ahora el proceso tiene dos partes, o es un
                nombre, en cual cas hay dos busquedas que hacer, o es un numero, en cual caso solo lo ponemos adentro
                 como si nada!*/

                //! 1. Agarramos el opcode basado en el nombre de la operacion
                int opCode = marieOperations.at(orderedEntry.first.first);
                int varCode = 0;
                std::string hexStringForPrinting;
                //! 2. Analizamos el caso para poder realizar la construccion de una operacion
                 /*Es un texto, puede ser variable o modulo*/

            	bool flagFound = false;
            	if (resultFromVariableParsing.contains(orderedEntry.second.second))
            	{
            		/*Se encontro como una variable. En este caso solo hay que ponerle la direccion de la
					variable en sentido de memoria*/
            		varCode = resultFromVariableParsing.at(orderedEntry.second.second).first.first;
            		std::cout << varCode << std::endl;
            		flagFound = true;
            	}
            		bool foundInSentences = false;

            	if (!flagFound)
            	{
            		for (const auto& secondEntry : resultsFromSentenceParsing)
            		{
            			if (secondEntry.first.first == orderedEntry.second.second)
            			{
            				varCode = secondEntry.first.second;
            				foundInSentences = true;
            				break;
            			}
            		}

            		if (!foundInSentences)
            		{
            			/*Es un numero pero tomamos exactamente como debe ser, como numero sin conversion*/
            			if (!orderedEntry.second.second.empty())
            			{
            				std::cout <<orderedEntry.second.second << std::endl;
            				varCode = std::stoi(orderedEntry.second.second, nullptr, (orderedEntry.second.second ==
            				"0C00" ? 16:10));
            				std::cout << varCode << std::endl;
            			}
            		}
            	}


            	std::cout << "Equal Case opCode " << opCode << " varCode " << varCode << std::endl;

            	hexStringForPrinting = HexDecimalToStringForMethods(opCode, varCode, jump);
                /*3. Armamos la string representativa*/

                std::string resultString = "[" + std::to_string(orderedEntry.first.second) + "] " + "[" + hexStringForPrinting + "]: " +
                orderedEntry.first.first + " " + orderedEntry.second.second;
                vectorDeOperacionesYaRealizadas.push_back(std::make_pair(orderedEntry.first.second, resultString));
            }
            else if (orderedEntry.first.first != orderedEntry.second.first)
            {
                /*! En este caso, podemos estar tratando de dos operaciones diferentes, ya sea una variable (que no
                se cubre en esta parte, o una subrutina. En si deberiamos de trabajar buscando igualmente en que si
                no esl mismo nombre hay que buscar a que esta llamando, lo cual puede ser o un numero o una variable*/
                //! 1. Agarramos el opcode basado en el nombre de la operacion
                int opCode = marieOperations.at(orderedEntry.second.first);
                int varCode = 0;
                std::string hexStringForPrinting;
                //! 2. Analizamos el caso para poder realizar la construccion de una operacion
                bool isAlpha = true;
            	bool flagFound = false;
            	if (resultFromVariableParsing.contains(orderedEntry.second.second))
            	{
            		/*Se encontro como una variable. En este caso solo hay que ponerle la direccion de la
					variable en sentido de memoria*/
            		varCode = resultFromVariableParsing.at(orderedEntry.second.second).first.first;
            		std::cout << std::endl;
            		flagFound = true;
            	}

            	if (!flagFound)
            	{
            		bool foundInSentences = false;
            		for (const auto& secondEntry : resultsFromSentenceParsing)
            		{
            			if (secondEntry.first.first == orderedEntry.second.second)
            			{
            				varCode = secondEntry.first.second;
            				foundInSentences = true;
            				break;
            			}
            		}

            		if (!foundInSentences)
            		{
            			/*Es un numero pero tomamos exactamente como debe ser, como numero sin conversion*/
            			if (!orderedEntry.second.second.empty())
            			{
            				std::cout <<orderedEntry.second.second << std::endl;
            				varCode = std::stoi(orderedEntry.second.second);
            				std::cout << varCode << std::endl;
            			}
            		}
            	}
            	std::cout << "Unequal Case opCode" << opCode << " varCode" << varCode << std::endl;
            	hexStringForPrinting = HexDecimalToStringForMethods(opCode, varCode, jump);

                std::string resultString = "[" + std::to_string(orderedEntry.first.second) + "] " + "[" + hexStringForPrinting + "]: " +
                orderedEntry.first.first + ", " + orderedEntry.second.first + " " + orderedEntry.second.second;
                vectorDeOperacionesYaRealizadas.push_back(std::make_pair(orderedEntry.first.second, resultString));
            }
        }

		/*! Ordenamos las variables*/
		std::vector<std::pair<std::string, std::pair<std::pair<int, long>, std::string>>> sortedVariables(
	    resultFromVariableParsing.begin(), resultFromVariableParsing.end());
    std::sort(sortedVariables.begin(), sortedVariables.end(),
              [](const std::pair<std::string, std::pair<std::pair<int, long>, std::string>>& a,
                 const std::pair<std::string, std::pair<std::pair<int, long>, std::string>>& b)
              {
	              return a.second.first.first < b.second.first.first;
              });
    /*! El ultimo metodo que tenemos que defininir es la posicion de las variables, lo bueno es que estan bien
    puestas en el arreglo desde su analisis.*/
        for (const auto& entry : sortedVariables)
        {
            std::string resultString = "[" + std::to_string(entry.second.first.first) + "] " + "["+
                HexDecimalToStringForVariables(entry.second.first.first,jump) + "] [" + HexDecimalValueForVariables(
                	entry.second.first.second) + "]: "
            + entry.first + ", " + entry.second.second + " " + std::to_string(entry.second.first.second);
            vectorDeOperacionesYaRealizadas.push_back(std::make_pair(entry.second.first.first, resultString));
        }
    return vectorDeOperacionesYaRealizadas;
}


int main()
{
    std::string testString =
    	R"(
 /*Class 18th feb 2025*/

/*Key new keywrods*/
/* ORG: Stores the ORIGIN address of our program. It can be though of as the pointer that tells the CPU to look for address 100 to
/* to find the beginning of our program. ORG does not add to the total PC it only redirects the CPUs MAR.
/* LOAD (Mem Instruction 1000 + Mem Addres Octal) tells the control unit to load the value from the address section, into the AC
/* ADD (Mem Instruction 3000 + Octal Address) tells the control unit to store the second value into the MBR and then pass it to the ALU with the accumulator
/* to add.
/*
/* STORE (Mem Instruction 2000 + Octal Address) tells the control unit to pass whatever is in the accumulator and store it in the provided MEMORY ADDRESS
/* HALT: Stops the program !
/* HEX can be used like DEC to declare the value of a number.

/* Re-study conversion mechanisms, make them fast and practice a to of these
/* Marie works with a binary two's complement representation. Program's have a fixed word length. Word length is basically the amount of bits usable for data
/* storage. We have a a 16 bit data word, i.e. a 0x000 to 0xFF0. Having 4096 usable memory addresses. Four bits are always reserved for theopcode,
/* and 12 are used for the address.
/* 16 Bit arithmetic logic units and has specifically seven registers for control and data movement. Every instruction holds 4 address bits and it matches
/* that those 12 left bits are left for addresses

/** Harvey Deitel 2.18 Comparing Integers! **/
/** Santiago Arellano 	00328370**/
/** 18th February, 2025 **/
ORG 100

defMain, Clear
		 Jump RegisterValues
		 returnOfRegisterValues, Clear
		 						 Load userNumOne
								 Output
								 Load userNumTwo
								 Output
		 ifNumOneHigherThanNumB, Clear
		 					     Load userNumOne
								 Subt userNumTwo
								 SkipCond 800
								 Jump ifNumOneIsEqualToNumB
								 Load outputOne
								 Output
								 Halt
		 ifNumOneIsEqualToNumB, Clear
		 						Load userNumOne
								Subt userNumTwo
		 						 SkipCond 400
								 Jump ifNumOneIsLessThanNumB
		 						 Load outputZero
								 Output
								 Halt
		 ifNumOneIsLessThanNumB, Clear
		 						Load outputMinusOne
								Output
								Halt
		Halt




RegisterValues, Clear
				Load userNumOne
				Input
				Store userNumOne
				Load userNumTwo
				Input
				Store userNumTwo
				Jump returnOfRegisterValues


userNumOne, DEC 0
userNumTwo, DEC 0
outputOne, HEX 0001
outputZero, HEX 0000
outputMinusOne, HEX 100A
)";
		int jump = 0;
	auto variables = forwardSearchForVariables(testString, jump);
    for (auto test_string : variables)
    {
        std::cout << test_string.first << " " << test_string.second.first.first << " " << test_string.second.second << test_string.second.first.second << std::endl;

    }
    std::cout << jump << std::endl;
    auto operations = forwardSearchForLines(testString);

        // Print the results
        for (const auto& [key, value] : operations) {
            std::cout << "Line " << key.second << ": "
                      << key.first << " -> Operation: " << value.first;
            if (!value.second.empty()) {
                std::cout << ", Parameter: " << value.second;
            }
            std::cout << std::endl;
        }

        auto orderedOperations =   mapFromStringToOperationCodeComplete(operations, variables, jump);
        for (const auto& entry : orderedOperations) {
            std::cout << entry.first << " " << entry.second << std::endl;
        }


    return 0;

}
