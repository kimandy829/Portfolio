/* global util */

/**
 * Helper functions for building and working with UI elements.
 */

const ui = {
  /**
   * Clears (any) existing rows from the #table-rows table body element.
   */
  clearTable: function () {
    document.querySelector('#table-rows').innerHTML = '';
  },

  /**
   * Decorates (i.e., adds) a `lang` attribute to the given HTML element using the
   * provided `language`.  For example, if a table data element was passed
   * to this function, and the language was "French", the element would
   * be updated to look like this in the DOM:
   *
   *   <td lang="fr">...</td>
   *
   * Your function should accept the following language names, and return the
   * associated 2-letter language code:
   *
   *  - English: "en"
   *  - Arabic: "ar"
   *  - Chinese: "zh"
   *  - French: "fr"
   *  - Hindi: "hi"
   *  - Korean: "ko"
   *  - Japanese: "ja"
   *  - Russian: "ru"
   *
   * If any other language name is given, return the "unknown" language code,
   * which is represented by the empty string "" (e.g., <p lang="">...</p>)
   *
   * See https://developer.mozilla.org/en-US/docs/Web/HTML/Global_attributes/lang
   *
   * Use util.langCodeForLanguage to get the 2-letter language code.
   *
   * @param {HTMLElement} element - the element to decorate with a lang attribute
   * @param {String} language - the language name to use
   */
  addLangToElement: function (element, language) {
    var newElement = document.createElement(element);
    var tempLang = util.langCodeForLanguage(language);
    if (tempLang != null) {
      newElement.lang = tempLang;
    }
    else {
      newElement.lang = '';
    }
    return newElement;
  },

  /**
   * Takes a `country.code` (e.g., "CA" for Canada) and returns a URL
   * to the image for this country's flag on the Country Flags web service:
   * https://www.countryflags.io/.  For example, given the country code String
   * "CA" and a size of 24, the function should return the following URL string:
   *
   * https://www.countryflags.io/CA/flat/24.png
   *
   * For sizes, you should support 16, 24, 32, 48, and 64, and throw an error
   * if a different size is given.
   *
   * @param {String} countryCode - the country code, for example "CA"
   * @param {Size} size - the size of the flag to use
   */
  countryCodeToFlagUrl: function (countryCode, size) {
    var validSize = [16, 24, 32, 48, 64];
    if (validSize.includes(size)) {
      return `https://www.countryflags.io/${countryCode}/flat/${size}.png`;
    }
    else {
      throw new Error ('size not supported');
    }
  },

  /**
   * Takes a `country.code` (e.g., "CA" for Canada) and returns an <img> element,
   * using the ui.countryCodeToFlagUrl function to generate the img src attribute.
   *
   * @param {String} countryCode - the country code, for example "CA"
   */
  countryCodeToImg: function (countryCode) {
    var newImg = document.createElement('img');
    newImg.src = ui.countryCodeToFlagUrl(countryCode, 32); 
    newImg.alt = `Official flag of ${countryCode}`;
    return newImg;
  },

  /**
   * Takes a single `country` object and converts it to a <tr> with <td>
   * child elements for every column in the row.  The row should match the
   * expected format of the table (i.e., flag, code, country, continent, etc).
   * Return the newly created  <tr>...</tr> row element.
   *
   * Use the DOM methods document.createElement(), element.appendChild(), etc
   * to create your <tr> row.
   *
   * Use `ui.countryCodeToImg` to generate the <img> element for the flag.
   *
   * Use `ui.addLangToElement` to decorate the country column in your row so that
   * its `lang` attribute is correct for the given language.
   *
   * @param {Object} country - the country object to format as a table row
   */
  countryToRow: function (country, language = 'default') {
    var newRow = document.createElement('tr');

    var flag = document.createElement('td');
    var code = document.createElement('td');
    var continent = document.createElement('td');
    var areaInKm2 = document.createElement('td');
    var population = document.createElement('td');
    var capital = document.createElement('td');
    if (language == 'default') {
      var countryName = ui.addLangToElement('td', 'English');
    }
    else {
      var countryName = ui.addLangToElement('td', language);
    }
    
    flag.appendChild(ui.countryCodeToImg(country.code));
    code.innerHTML = country.code;
    continent.innerHTML = country.continent;
    areaInKm2.innerHTML = country.areaInKm2;
    population.innerHTML = country.population;
    capital.innerHTML = country.capital;
    if (language == 'default') {
      countryName.innerHTML = country.name;
    }
    else {
      countryName.innerHTML = country.name[language];
    }

    newRow.appendChild(flag);
    newRow.appendChild(code);
    newRow.appendChild(countryName);
    newRow.appendChild(continent);
    newRow.appendChild(areaInKm2);
    newRow.appendChild(population);
    newRow.appendChild(capital);
    
    return newRow;
  },

  /**
   * Takes an array of `country` Objects named `countries`, and passes each
   * `country` in the array  to `ui.countryToRow`.  The resulting
   * rows are then appended to the #table-rows table body element.  Make sure
   * you use `ui.clearTable()` to remove any existing rows before you do this.
   *
   * Also make sure to pass the `language` value into `ui.countryToRow` so that
   * the country names in the table get the appropriate `lang` attribute set.
   *
   * @param {Array<Object>} countries - the country objects to be turned into rows in a table
   * @param {String} language - the language name being used for these countries
   */
  countriesToTable: function (countries, language = 'default') {
    ui.clearTable();
    var newRows = document.querySelector('#table-rows');
    for (let i = 0; i < countries.length; i++) {
      if (language == 'default') {
        newRows.appendChild(ui.countryToRow(countries[i]));
      }
      else {
        newRows.appendChild(ui.countryToRow(countries[i], language));
      }   
    }
  }
};
