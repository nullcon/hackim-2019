(function(name, context, definition) {
    if (typeof module !== 'undefined' && module.exports) {
        module.exports = definition()
    } else if (typeof define === 'function' && define.amd) {
        define(definition)
    } else {
        context[name] = definition()
    }
})('fpbrowser_v1', this, function() {
    'use strict';
    var Fingerprint = function(options) {
        var nativeForEach, nativeMap;
        nativeForEach = Array.prototype.forEach;
        nativeMap = Array.prototype.map;
        this.each = function(obj, iterator, context) {
            if (obj === null) {
                return
            }
            if (nativeForEach && obj.forEach === nativeForEach) {
                obj.forEach(iterator, context)
            } else if (obj.length === +obj.length) {
                for (var i = 0, l = obj.length; i < l; i++) {
                    if (iterator.call(context, obj[i], i, obj) === {}) return
                }
            } else {
                for (var key in obj) {
                    if (obj.hasOwnProperty(key)) {
                        if (iterator.call(context, obj[key], key, obj) === {}) return
                    }
                }
            }
        };
        this.map = function(obj, iterator, context) {
            var results = [];
            if (obj == null) return results;
            if (nativeMap && obj.map === nativeMap) return obj.map(iterator, context);
            this.each(obj, function(value, index, list) {
                results[results.length] = iterator.call(context, value, index, list)
            });
            return results
        };
        if (typeof options == 'object') {
            this.hasher = options.hasher;
            this.screen_resolution = options.screen_resolution;
            this.screen_orientation = options.screen_orientation;
            this.canvas = options.canvas;
            this.ie_activex = options.ie_activex
        } else if (typeof options == 'function') {
            this.hasher = options
        }
    };
    Fingerprint.prototype = {
        get: function() {
            var keys = [];
            keys.push(navigator.userAgent);
            keys.push(navigator.language);
            keys.push(screen.colorDepth);
            if (this.screen_resolution) {
                var resolution = this.getScreenResolution();
                if (typeof resolution !== 'undefined') {
                    keys.push(resolution.join('x'))
                }
            }
            keys.push(new Date().getTimezoneOffset());
            keys.push(this.hasSessionStorage());
            keys.push(this.hasLocalStorage());
            keys.push(!!window.indexedDB);
            if (document.body) {
                keys.push(typeof(document.body.addBehavior))
            } else {
                keys.push(typeof undefined)
            }
            keys.push(typeof(window.openDatabase));
            keys.push(navigator.cpuClass);
            keys.push(navigator.platform);
            keys.push(navigator.doNotTrack);
            keys.push(this.getPluginsString());
            if (this.canvas && this.isCanvasSupported()) {
                keys.push(this.getCanvasFingerprint())
            }
            if (this.hasher) {
                return this.hasher(keys.join('###'), 31)
            } else {
                return this.fingerprint_js_browser(keys.join('###'), 31)
            }
        },
        fingerprint_js_browser: function(key, seed) {
            var remainder, bytes, h1, h1b, c1, c2, k1, i;
            remainder = key.length & 3;
            bytes = key.length - remainder;
            h1 = seed;
            c1 = 0xcc9e2d51;
            c2 = 0x1b873593;
            i = 0;
            while (i < bytes) {
                k1 = ((key.charCodeAt(i) & 0xff)) | ((key.charCodeAt(++i) & 0xff) << 8) | ((key.charCodeAt(++i) & 0xff) << 16) | ((key.charCodeAt(++i) & 0xff) << 24);
                ++i;
                k1 = ((((k1 & 0xffff) * c1) + ((((k1 >>> 16) * c1) & 0xffff) << 16))) & 0xffffffff;
                k1 = (k1 << 15) | (k1 >>> 17);
                k1 = ((((k1 & 0xffff) * c2) + ((((k1 >>> 16) * c2) & 0xffff) << 16))) & 0xffffffff;
                h1 ^= k1;
                h1 = (h1 << 13) | (h1 >>> 19);
                h1b = ((((h1 & 0xffff) * 5) + ((((h1 >>> 16) * 5) & 0xffff) << 16))) & 0xffffffff;
                h1 = (((h1b & 0xffff) + 0x6b64) + ((((h1b >>> 16) + 0xe654) & 0xffff) << 16))
            }
            k1 = 0;
            switch (remainder) {
                case 3:
                    k1 ^= (key.charCodeAt(i + 2) & 0xff) << 16;
                case 2:
                    k1 ^= (key.charCodeAt(i + 1) & 0xff) << 8;
                case 1:
                    k1 ^= (key.charCodeAt(i) & 0xff);
                    k1 = (((k1 & 0xffff) * c1) + ((((k1 >>> 16) * c1) & 0xffff) << 16)) & 0xffffffff;
                    k1 = (k1 << 15) | (k1 >>> 17);
                    k1 = (((k1 & 0xffff) * c2) + ((((k1 >>> 16) * c2) & 0xffff) << 16)) & 0xffffffff;
                    h1 ^= k1
            }
            h1 ^= key.length;
            h1 ^= h1 >>> 16;
            h1 = (((h1 & 0xffff) * 0x85ebca6b) + ((((h1 >>> 16) * 0x85ebca6b) & 0xffff) << 16)) & 0xffffffff;
            h1 ^= h1 >>> 13;
            h1 = ((((h1 & 0xffff) * 0xc2b2ae35) + ((((h1 >>> 16) * 0xc2b2ae35) & 0xffff) << 16))) & 0xffffffff;
            h1 ^= h1 >>> 16;
            return h1 >>> 0
        },
        hasLocalStorage: function() {
            try {
                return !!window.localStorage
            } catch (e) {
                return true
            }
        },
        hasSessionStorage: function() {
            try {
                return !!window.sessionStorage
            } catch (e) {
                return true
            }
        },
        isCanvasSupported: function() {
            var elem = document.createElement('canvas');
            return !!(elem.getContext && elem.getContext('2d'))
        },
        isIE: function() {
            if (navigator.appName === 'Microsoft Internet Explorer') {
                return true
            } else if (navigator.appName === 'Netscape' && /Trident/.test(navigator.userAgent)) {
                return true
            }
            return false
        },
        getPluginsString: function() {
            if (this.isIE() && this.ie_activex) {
                return this.getIEPluginsString()
            } else {
                return this.getRegularPluginsString()
            }
        },
        getRegularPluginsString: function() {
            return this.map(navigator.plugins, function(p) {
                var mimeTypes = this.map(p, function(mt) {
                    return [mt.type, mt.suffixes].join('~')
                }).join(',');
                return [p.name, p.description, mimeTypes].join('::')
            }, this).join(';')
        },
        getIEPluginsString: function() {
            if (window.ActiveXObject) {
                var names = ['ShockwaveFlash.ShockwaveFlash', 'AcroPDF.PDF', 'PDF.PdfCtrl', 'QuickTime.QuickTime', 'rmocx.RealPlayer G2 Control', 'rmocx.RealPlayer G2 Control.1', 'RealPlayer.RealPlayer(tm) ActiveX Control (32-bit)', 'RealVideo.RealVideo(tm) ActiveX Control (32-bit)', 'RealPlayer', 'SWCtl.SWCtl', 'WMPlayer.OCX', 'AgControl.AgControl', 'Skype.Detection'];
                return this.map(names, function(name) {
                    try {
                        new ActiveXObject(name);
                        return name
                    } catch (e) {
                        return null
                    }
                }).join(';')
            } else {
                return ""
            }
        },
        getScreenResolution: function() {
            var resolution;
            if (this.screen_orientation) {
                resolution = (screen.height > screen.width) ? [screen.height, screen.width] : [screen.width, screen.height]
            } else {
                resolution = [screen.height, screen.width]
            }
            return resolution
        },
        getCanvasFingerprint: function() {
            var canvas = document.createElement('canvas');
            var ctx = canvas.getContext('2d');
            var txt = 'I am not admin';
            ctx.textBaseline = "top";
            ctx.font = "12.5px 'Arial'";
            ctx.textBaseline = "numeric";
            ctx.fillStyle = "#f60";
            ctx.fillRect(101, 5, 48, 30);
            ctx.fillStyle = "#069";
            ctx.fillText(txt, 2, 15);
            ctx.fillStyle = "rgba(111, 177, 0.1, 0.7)";
            ctx.fillText(txt, 4, 17);
            return canvas.toDataURL()
        }
    };
    return Fingerprint
});

function bjs_1(e) {
    var r = new fpbrowser_v1,
        t = new fpbrowser_v1({
            canvas: !0
        }),
        n = r.get(),
        o = t.get(),
        i = n + "" + o,
        a = getbrowser(),
        d = new XMLHttpRequest,
        s = "trackuser.php",
        w = "m=" + i;
    w += "&token=" + e, w += "&b=" + a, d.open("POST", s, !0), d.setRequestHeader("Content-type", "application/x-www-form-urlencoded"), d.onreadystatechange = function() {
        if (4 == d.readyState && 200 == d.status) {
            d.responseText;
            "index.php" == e && (document.getElementById("loaderDiv").innerHTML = "")
        }
    }, d.send(w)
}

function getbrowser() {
    var e = !!window.opr && !!opr.addons || !!window.opera || navigator.userAgent.indexOf(" OPR/") >= 0;
    if (e) return "Opera";
    var r = "undefined" != typeof InstallTrigger;
    if (r) return "FireFox";
    var t = Object.prototype.toString.call(window.HTMLElement).indexOf("Constructor") > 0;
    if (t) return "Safari";
    var n = !1 || !!document.documentMode;
    if (n) return "IE";
    var o = !n && !!window.StyleMedia;
    if (o) return "Edge";
    var i = !!window.chrome && !!window.chrome.webstore;
    return i ? "Chrome" : "other Browser"
}
