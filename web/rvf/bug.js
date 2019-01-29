    var ESI = require('./nodesi');

    var esi = new ESI();

    esi.process('<esi:incasdasdlude src="http://192.168.169.129:8080/admin" />').then(function(result) {
        console.log(result)
        // result is a fetched html
    });

   esi.process('<esi:include src="http://192.168.169.129:8080/admin" />').then(function(result) {
        console.log(result)
        // result is a fetched html
    });


