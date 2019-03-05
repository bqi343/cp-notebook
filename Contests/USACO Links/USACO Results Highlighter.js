javascript: void function() { // originally posted by eygmath on USACO discord?
  	var co = [0,0,0];
    var tot = 0;
    function e(e, a, n) { 
        if (void 0 == e) return !1;
        e = e.substring(7, 11);
        for (var i = 0; i < n.length; i++)
            if (n[i][0] == e && n[i][1] == a) return !0;
        return !1
    }

    function a(a, n, i) {
        for (var r = 0; r < a.length; r += 2) e(a[r].childNodes[1].innerHTML, a[r].childNodes[2].innerHTML, n) && (a[r].childNodes[2].style["background-color"] = i)
    }

    function n(e) {
        var a = document.createElement("th");
        a.innerHTML = "Rank", e[0].insertBefore(a, e[0].firstChild);
        for (var n = 0, i = 1, r = "", o = !0, l = 2; l < e.length; l += 2) {
            var h = e[l].childNodes[3].innerHTML;
            h == r ? i++ : (n += i, i = 1, o = !o), r = h;
            var t = document.createElement("th");
            t.innerHTML = "" + n, e[l].insertBefore(t, e[l].firstChild), o && (e[l].childNodes[0].style["background-color"] = "#d0d0d0")
        }
    }

    function i(e, a, n, o) {
      	var bad = 0;
        for (var i = a; a + n > i; i++) 
            if ("*" != e[i].innerHTML) 
              	bad ++;
     	if (bad > 2) return;
        co[o] ++;
        for (var i = a; a + n > i; i++) {
          if (bad > 0) e[i].style["background-color"] = "#ffff00"
          else e[i].style["background-color"] = "#39ff14"
        }
    }

    function r(e) {
        for (var a = [], n = 10; n < e[0].childNodes.length; n++) e[0].childNodes[n].hasAttribute("colspan") && a.push(e[0].childNodes[n].getAttribute("colspan") - 1);
        console.log(a);
        for (var n = 2; n < e.length; n += 2) {
            for (var r = 5, o = 0; 3 > o; o++) i(e[n].childNodes, r, a[o], o), r += a[o] + 2;
            tot ++;
        }
    }
    for (var o = [
            ["2014", "Joshua Brakensiek", "2012"],
            ["2014", "Stanley Cen", "2012"],
            ["2012", "Alex Chen", "2012"],
            ["2013", "Yimo Chen", "2012"],
            ["2013", "Calvin Deng", "2012"],
            ["2014", "Michael Gao", "2012"],
            ["2014", "Steven Hao", "2012"],
            ["2013", "Johnny Ho", "2012"],
            ["2012", "Mitchell Lee", "2012"],
            ["2013", "Ray Li", "2012"],
            ["2014", "Jerry Ma", "2012"],
            ["2013", "Kalki Seksaria", "2012"],
            ["2015", "Videh Seksaria", "2012"],
            ["2015", "Alexandr Wang", "2012"],
            ["2015", "Scott Wu", "2012"],
            ["2013", "Daniel Ziegler", "2012"],
            ["2014", "Joshua Brakensiek", "2013"],
            ["2014", "Stanley Cen", "2013"],
            ["2014", "Bill Cooperman", "2013"],
            ["2016", "Ross Dempsey", "2013"],
            ["2016", "Demi Guo", "2013"],
            ["2014", "Steven Hao", "2013"],
            ["2015", "Andrew He", "2013"],
            ["2013", "Johnny Ho", "2013"],
            ["2016", "Jasper Hugunin", "2013"],
            ["2016", "Lawrence Li", "2013"],
            ["2013", "Ray Li", "2013"],
            ["2014", "Jerry Ma", "2013"],
            ["2014", "Alex Pei", "2013"],
            ["2016", "Jonathan Sadun", "2013"],
            ["2013", "Kalki Seksaria", "2013"],
            ["2015", "Videh Seksaria", "2013"],
            ["2014", "Brian Shimanuki", "2013"],
            ["2016", "Kevin Sun", "2013"],
            ["2015", "Alexandr Wang", "2013"],
            ["2016", "Tony Wang", "2013"],
            ["2016", "Alexander Wei", "2013"],
            ["2015", "Scott Wu", "2013"],
            ["2014", "Qingqi Zeng", "2013"],
            ["2013", "Daniel Ziegler", "2013"],
            ["2015", "James Bloxham", "2014"],
            ["2014", "Joshua Brakensiek", "2014"],
            ["2017", "Bryan Chen", "2014"],
            ["2014", "Bill Cooperman", "2014"],
            ["2015", "Alexander Dai", "2014"],
            ["2015", "Matthew Das Sarma", "2014"],
            ["2016", "Demi Guo", "2014"],
            ["2014", "Steven Hao", "2014"],
            ["2015", "Andrew He", "2014"],
            ["2016", "Samuel Hsiang", "2014"],
            ["2018", "William Hu", "2014"],
            ["2017", "James Li", "2014"],
            ["2015", "Kevin Liu", "2014"],
            ["2015", "Yang Liu", "2014"],
            ["2017", "Tiger Luo", "2014"],
            ["2014", "Jerry Ma", "2014"],
            ["2015", "Vivek Miglani", "2014"],
            ["2018", "Dhruv Rohatgi", "2014"],
            ["2018", "Nicholas Sun", "2014"],
            ["2015", "Scott Wu", "2014"],
            ["2016", "Yang Yan", "2014"],
            ["2015", "David Zeng", "2014"],
            ["2015", "Hugh Zhang", "2014"],
            ["2017", "David Zhu", "2014"],
            ["2016", "Jordan Alexander", "2015"],
            ["2015", "James Bloxham", "2015"],
            ["2017", "Nikhil Cheerla", "2015"],
            ["2017", "Daniel Chiu", "2015"],
            ["2016", "Michael Colavita", "2015"],
            ["2015", "Alexander Dai", "2015"],
            ["2015", "Corwin de Boor", "2015"],
            ["2016", "Brian Gu", "2015"],
            ["2016", "Demi Guo", "2015"],
            ["2017", "Nicholas Guo", "2015"],
            ["2015", "Andrew He", "2015"],
            ["2016", "Calvin Lee", "2015"],
            ["2016", "Lawrence Li", "2015"],
            ["2015", "Kevin Liu", "2015"],
            ["2015", "Yang Liu", "2015"],
            ["2017", "Tiger Luo", "2015"],
            ["2016", "Sanjeev Murty", "2015"],
            ["2018", "Shwetark Patel", "2015"],
            ["2016", "Sean Shi", "2015"],
            ["2017", "Alec Sun", "2015"],
            ["2016", "Tony Wang", "2015"],
            ["2016", "Alexander Wei", "2015"],
            ["2016", "Alexander Yang", "2015"],
            ["2017", "David Zhu", "2015"],
            ["2016", "Suchir Balaji", "2016"],
            ["2017", "Christopher Chang", "2016"],
            ["2017", "Bryan Chen", "2016"],
            ["2018", "Hongyi Chen", "2016"],
            ["2018", "Katherine Cheng", "2016"],
            ["2017", "Daniel Chiu", "2016"],
            ["2017", "Amanda Du", "2016"],
            ["2018", "Swapnil Garg", "2016"],
            ["2018", "Avichal Goel", "2016"],
            ["2018", "Louis Golowich", "2016"],
            ["2019", "Alexander Gu", "2016"],
            ["2016", "Demi Guo", "2016"],
            ["2018", "Aayush Gupta", "2016"],
            ["2018", "William Hu", "2016"],
            ["2019", "Anson Hu", "2016"],
            ["2016", "Calvin Lee", "2016"],
            ["2016", "Lawrence Li", "2016"],
            ["2018", "Kevin Liu", "2016"],
            ["2019", "Kyle Liu", "2016"],
            ["2018", "Shwetark Patel", "2016"],
            ["2017", "Nicholas Pipitone", "2016"],
            ["2017", "Dhruv Rohatgi", "2016"],
            ["2018", "Mihir Singhal", "2016"],
            ["2019", "Eric Zhang", "2016"],
            ["2018", "Justin Zhang", "2016"],
            ["2018", "Jessica Zheng", "2016"],
            ["2019", "Riya Arora", "2017"],
            ["2019", "Grace Cai", "2017"],
            ["2018", "Spencer Compton", "2017"],
            ["2018", "Swapnil Garg", "2017"],
            ["2018", "David Hou", "2017"],
            ["2018", "William Hu", "2017"],
            ["2021", "David Hu", "2017"],
            ["2019", "Kyle Liu", "2017"],
            ["2018", "William Luo", "2017"],
            ["2017", "Zhezheng Luo", "2017"],
            ["2018", "Karthik Nair", "2017"],
            ["2019", "Benjamin Qi", "2017"],
            ["2019", "Kevin Qian", "2017"],
            ["2017", "Dhruv Rohatgi", "2017"],
            ["2019", "Jonathan Shoemaker", "2017"],
            ["2019", "Eric Tong", "2017"],
            ["2018", "Franklyn Wang", "2017"],
            ["2020", "Brandon Wang", "2017"],
            ["2019", "Archer Wang", "2017"],
            ["2019", "Daniel Wisdom", "2017"],
            ["2017", "Andrew Yang", "2017"],
            ["2019", "Stan Zhang", "2017"],
            ["2019", "Eric Zhang", "2017"],
            ["2019", "Daniel Zhang", "2017"],
            ["2018", "Jason Zhao", "2017"],
            ["2019", "Adam Zheng", "2017"],
            ["2019", "Riya Arora", "2018"],
            ["2020", "Steven Cheng", "2018"],
            ["2018", "Spencer Compton", "2018"],
            ["2021", "David Hu", "2018"],
            ["2018", "William Hu", "2018"],
            ["2019", "Yibo Huang", "2018"],
            ["2024", "Rain Jiang", "2018"],
            ["2020", "Jiajie (Tony) Li", "2018"],
            ["2019", "Kyle Liu", "2018"],
            ["2020", "Michael Liu", "2018"],
            ["2019", "Anne Ouyang", "2018"],
            ["2019", "Chris Pan", "2018"],
            ["2019", "Benjamin Qi", "2018"],
            ["2019", "Mehul Raheja", "2018"],
            ["2020", "Chaitanya Ravuri", "2018"],
            ["2019", "Jonathan Shoemaker", "2018"],
            ["2019", "George Tang", "2018"],
            ["2018", "Franklyn Wang", "2018"],
            ["2020", "Walden Yan", "2018"],
            ["2021", "Eric Zhang", "2018"],
            ["2019", "Eric Zhang", "2018"],
            ["2019", "Michael Zhang", "2018"],
            ["2019", "Nicholas Zhang", "2018"],
            ["2020", "Patrick Zhang", "2018"],
            ["2019", "Stan Zhang", "2018"],
            ["2019", "Adam Zheng", "2018"]
        ], l = document.getElementsByTagName("tbody"), h = 1; h < l.length - 1; h++) a(l[h].childNodes, o, "#ffff00"), r(l[h].childNodes), n(l[h].childNodes)
    console.log(" TOTAL: "+tot+" PERCENT: "+Math.round(100*co[0]/tot)+" "+Math.round(100*co[1]/tot)+" "+Math.round(100*co[2]/tot));
}();