/* global countriesData, ui, util */

window.onload = function () {
  /**
   * Register click handlers for every menu item in the page.  Use the objects
   * and functions defined in the other JavaScript files to update/populate
   * the #table-rows table body with the appropriate set of countries, based on the
   * menu item clicked, specifically:
   *
   *  - countriesData array of country data Objects
   *  - util methods for working with the country data
   *  - ui methods for working with the DOM
   *
   * Make sure you also update the #subtitle heading to properly reflect what
   * is in the table after you populate it.
   *
   * For example: "List of Countries and Dependencies - Population between 1 and 2 million"
   * or "List of Countries and Dependencies - All countries in Asia" etc.
   */
  //event handlers for country list (by language)
  var english = document.querySelector('#menu_english');
  var arabic = document.querySelector('#menu_arabic');
  var chinese = document.querySelector('#menu_chinese');
  var french = document.querySelector('#menu_french');
  var hindi = document.querySelector('#menu_hindi');
  var korean = document.querySelector('#menu_korean');
  var japanese = document.querySelector('#menu_japanese');
  var russian = document.querySelector('#menu_russian');
  var temp = document.querySelector('#subtitle');
  english.addEventListener('click', function() {
    ui.countriesToTable(countriesData, 'English');
    temp.innerText = 'List of Countries and Dependencies - English';
  });
  arabic.addEventListener('click', function() {
    ui.countriesToTable(countriesData, 'Arabic');
    temp.innerText = 'List of Countries and Dependencies - Arabic';
  });
  chinese.addEventListener('click', function() {
    ui.countriesToTable(countriesData, 'Chinese');
    temp.innerText = 'List of Countries and Dependencies - Chinese';
  });
  french.addEventListener('click', function() {
    ui.countriesToTable(countriesData, 'French');
    temp.innerText = 'List of Countries and Dependencies - French';
  });
  hindi.addEventListener('click', function() {
    ui.countriesToTable(countriesData, 'Hindi');
    temp.innerText = 'List of Countries and Dependencies - Hindi';
  });
  korean.addEventListener('click', function() {
    ui.countriesToTable(countriesData, 'Korean');
    temp.innerText = 'List of Countries and Dependencies - Korean';
  });
  japanese.addEventListener('click', function() {
    ui.countriesToTable(countriesData, 'Japanese');
    temp.innerText = 'List of Countries and Dependencies - Japanese';
  });
  russian.addEventListener('click', function() {
    ui.countriesToTable(countriesData, 'Russian');
    temp.innerText = 'List of Countries and Dependencies - Russian';
  });

  //event handlers for (by population)
  var popGreater100m = document.querySelector('#menu_population_100_000_000m');
  var pop1To2m = document.querySelector('#menu_population_1m_2m') 
  popGreater100m.addEventListener('click', function() {
    ui.countriesToTable(util.countriesByPopulation(100000000));
    temp.innerText = 'List of Countries and Dependencies - Population > 100 million';
  });
  pop1To2m.addEventListener('click', function() {
    ui.countriesToTable(util.countriesByPopulation(1000000, 2000000));
    temp.innerText = 'List of Countries and Dependencies - Population between 1 and 2 million';
  });

  //event handlers for (by area & continent)
  var americas_1mkm = document.querySelector('#menu_americas_1mkm');
  var asia_all = document.querySelector('#menu_asia_all');
  americas_1mkm.addEventListener('click',function() {
    ui.countriesToTable(util.countriesByAreaAndContinent('Americas', 1000000));
    temp.innerText = 'List of Countries and Dependencies - Area Greater than 1 million km2 in Americas';
  });
  asia_all.addEventListener('click', function() {
    ui.countriesToTable(util.countriesByAreaAndContinent('Asia', 0));
    temp.innerText = 'List of Countries and Dependencies - All countries in Asia';
  });
};
