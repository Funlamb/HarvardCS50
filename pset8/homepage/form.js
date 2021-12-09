document.addEventListener('DOMContentLoaded', function() {
    document.querySelector('form').onsubmit = function() {
        alert('Hello, ' + document.querySelector('#fname').value + ". We will send you an email whenever we have something new. Your email address is: " + document.querySelector('#email').value + ".");
        return false;
    };

});