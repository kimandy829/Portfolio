/**
 * Helper object for working with countries data and extracting information.
 * See countries-data.js for format of the countries data set.
 */

const util = {
  /**
   * Given a language name, returns the 2-letter language code for this language.
   * Supports all of the following languages:
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
   * If any other language is passed, return null
   *
   * For example:
   *
   * util.langCodeForLanguage('Korean') returns "ko"
   * util.langCodeForLanguage('German') returns null (i.e., not one of the supported languages)
   *
   * @param {String} language - the full language name
   */
  langCodeForLanguage(language) {
    var lang;
    var langArr = ['English', 'Arabic', 'Chinese', 'French', 'Hindi', 'Korean', 'Japanese', 'Russian'];
    if (langArr.includes(language)) {
      lang = language.slice(0,2).toLowerCase();
    }
    else {
      lang = null;
    }
    return lang;
  },
  /**
   * Formats a given number for display using the specified language.
   *
   * For example, given a number 652230 and language "Russian", return
   * the string:
   *
   * '652 230'
   *
   * Or if the language is "Hindi", return the string:
   *
   * '6,52,230'
   *
   * Your function should use util.langCodeForLanguage to map the language name to a language code.
   *
   * Use Intl.NumberFormat to generate the formatted numbers for each locale, see:
   *
   * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Intl/NumberFormat
   *
   * @param {Number} number - the number to format
   * @param {String} language - the language name to use
   */
  formatNumberForLanguage(number, language) {
    return new Intl.NumberFormat(util.langCodeForLanguage(language)).format(number);
  },

  /**
   * Returns a copy of the given country Object with the name property switched
   * to the specified language, and numbers formatted for this language. For example,
   * if the following country object is passed:
   *
   * {
   *   code: 'AF',
   *   continent: 'Asia',
   *   areaInKm2: 652230,
   *   population: 35530081,
   *   capital: 'Kabul',
   *   name: {
   *     English: 'Afghanistan',
   *     Arabic: 'أفغانستان',
   *     Chinese: '阿富汗',
   *     French: 'Afghanistan',
   *     Hindi: 'अफ़ग़ानिस्तान',
   *     Korean: '아프가니스탄',
   *     Japanese: 'アフガニスタン',
   *     Russian: 'Афганистан'
   *   }
   * }
   *
   * And if the language parameter is "Korean", return the following new object:
   *
   * {
   *   code: 'AF',
   *   continent: 'Asia',
   *   areaInKm2: '652,230',
   *   population: '35,530,081'
   *   capital: 'Kabul',
   *   name: '아프가니스탄',
   * }
   *
   * NOTE: do not modify the original object.  Create and return a new one.
   *
   * You should support the following languages:
   *
   * English, Arabic, Chinese, French, Hindi, Korean, Japanese, Russian
   *
   * If any other language is passed, throw an error indicating that an unrecognized
   * language name was used.
   *
   * NOTE: you should call `util.formatNumberForLanguage` to format the areaInKm2
   * and population values for the given language.
   *
   * @param {Object} country - the country object to use
   * @param {String} language - the language name to use
   */
  countryForLanguage: function (country, language) {
    var new_country = {};
    if (util.langCodeForLanguage(language) == null) {
      throw new Error ('unrecognized language name was used');
    }
    else {
      new_country.code = country.code;
      new_country.continent = country.continent;
      new_country.areaInKm2 = util.formatNumberForLanguage(country.areaInKm2, language);
      new_country.population = util.formatNumberForLanguage(country.population, language);
      new_country.capital = country.capital;
      new_country.name = country.name[language];
    }
    return new_country;
  },

  /**
   * Return an array of all countries, with the `name` property replaced by the
   * appropriate translation, or English if not specified (or unknown).  For
   * example, when language="English", you would process the Object for Canada into:
   *
   * {
   *     code: "CA",
   *     continent: "Americas",
   *     areaInKm2: "9,984,670",
   *     population: "36,624,199",
   *     capital: "Ottawa",
   *     name: "Canada"
   * }
   *
   * Supported languages include:
   *
   * English, Arabic, Chinese, French, Hindi, Korean, Japanese, Russian
   *
   * Uses `countriesData` as the underlying array of countries to be processed
   * and `util.countryForLanguage`.
   *
   * @param {String} language - the language name to use
   */
  countriesByLanguage: function (language) {
    var langArr = ['English', 'Arabic', 'Chinese', 'French', 'Hindi', 'Korean', 'Japanese', 'Russian'];
    var newArr = [];
    if (!langArr.includes(language)) {
      language = 'English';
    }
    for (let i = 0; i < countriesData.length; i++) {
      newArr.push(util.countryForLanguage(countriesData[i], language));
    }
    return newArr;
  },

  /**
   * Return an array of countries with a population greater than or equal to
   * `minPopulation`, and possibly less than equal to `maxPopulation` (if defined)
   * otherwise allow any number greater than `minPopulation`.
   *
   * Use `util.countriesByLanguage('English')` to get English names for countries
   * by default (i.e., you don't need to support multiple languages for population)
   *
   * @param {Number} minPopulation - (Required) minimum population value
   * @param {Number} maxPopulation - (Optional) maximum population value
   */
  countriesByPopulation: function (minPopulation, maxPopulation) {
    var newArr = [];
    if (maxPopulation === undefined) {
        for (let i = 0; i < countriesData.length; i++) {
          if (countriesData[i].population >= minPopulation) {
            newArr.push(util.countriesByLanguage('English')[i]);
          }
      }
    }
    else {
      for (let i = 0; i < countriesData.length; i++) {
        if (countriesData[i].population >= minPopulation && countriesData[i].population <= maxPopulation) {
          newArr.push(util.countriesByLanguage('English')[i]);
        }
      }
    }
    return newArr;
  },

  /**
   * Return an array of countries for the given `continent` with an area
   * greater than or equal to the given `area` in square KM.
   *
   * Use `util.countriesByLanguage('English')` to get English names for countries
   * by default (i.e., you don't need to support multiple languages for area)
   *
   * @param {String} continent - (Required) name of the continent (e.g., Europe)
   * @param {Number} minArea - (Required) minimum number of KM2 area
   */
  countriesByAreaAndContinent: function (continent, minArea) {
    var newArr = [];
    for (let i = 0; i < countriesData.length; i++) {
      if (countriesData[i].continent === continent && countriesData[i].areaInKm2 >= minArea) {
        newArr.push(util.countriesByLanguage('English')[i]);
      }
    }
    return newArr;
  }
};
