/*
Name: Andy Kim
Email: akim83@myseneca.ca
Student #: 105945308
Date: 2020-12-11
*/
const script = {
    clearTable: function () {
        document.querySelector('#listofproducts').innerHTML = '';
    },

    itemCategory: function(category) {
        var items = [];
        for (let i = 0; i < productsData.length; i++) {
            if (productsData[i].category === category) {
                items.push(productsData[i]);
            }
        }
        return items;
    },

    categoryToRow: function(product) {
    var card = document.createElement('div');
    var name = document.createElement('h2')
    var description = document.createElement('p');
    var price = document.createElement('h4');
    var image = document.createElement('img');
    
    name.innerHTML = product.name;
    description.innerHTML = product.description;
    price.innerHTML = new Intl.NumberFormat('en-CA', {style: 'currency', currency: 'CAD'}).format(product.price);
    image.setAttribute('src', product.imageUrl);
    image.setAttribute('alt', `image of ${product.name}`);

    card.appendChild(name);
    card.appendChild(description);
    card.appendChild(price);
    card.appendChild(image);
    return card;
    },

    categoriesToTable: function (products) {
        script.clearTable();
        var newItems = document.querySelector('#listofproducts');
        for (let i = 0; i < products.length; i++) {
            newItems.appendChild(script.categoryToRow(products[i]));
        }
    }
}

window.onload = function () {
    //event handlers for products
    var laptops = document.querySelector('#menu_laptops');
    var tablets = document.querySelector('#menu_tablets');
    var televisions = document.querySelector('#menu_televisions');
    var headphones = document.querySelector('#menu_headphones');
    var temp = document.querySelector('#storedesc');
    var temp2 = document.querySelector('#subtitle');

    laptops.addEventListener('click', function() {
        script.categoriesToTable(script.itemCategory('Laptops'));
        temp.innerText = 'Home > Laptops';
        temp2.innerText = '';
        document.querySelector('#mainimage1').style.visibility = 'hidden';
        document.querySelector('#mainimage2').style.visibility = 'hidden';
        document.querySelector('#homepage-products').style.visibility = 'hidden';
    });
    tablets.addEventListener('click', function() {
        script.categoriesToTable(script.itemCategory('Tablets'));
        temp.innerText = 'Home > Tablets';
        temp2.innerText = '';
        document.querySelector('#mainimage1').style.visibility = 'hidden'
        document.querySelector('#mainimage2').style.visibility = 'hidden';
        document.querySelector('#homepage-products').style.visibility = 'hidden';

    });
    televisions.addEventListener('click', function() {
        script.categoriesToTable(script.itemCategory('Televisions'));
        temp.innerText = 'Home > Televisions';
        temp2.innerText = '';
        document.querySelector('#mainimage1').style.visibility = 'hidden';
        document.querySelector('#mainimage2').style.visibility = 'hidden';
        document.querySelector('#homepage-products').style.visibility = 'hidden';

    });
    headphones.addEventListener('click', function() {
        script.categoriesToTable(script.itemCategory('Headphones'));
        temp.innerText = 'Home > Headphones';
        temp2.innerText = '';
        document.querySelector('#mainimage1').style.visibility = 'hidden';
        document.querySelector('#mainimage2').style.visibility = 'hidden';
        document.querySelector('#homepage-products').style.visibility = 'hidden';
    });
}