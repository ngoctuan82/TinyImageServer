var OptsMixin = {	
  // the `opts` argument is the option object received by the tag as well
  init: function(opts) {
      this.SESSION = this.opts.SESSION;
      console.log("Init Opts Mixin");
      console.log(opts);
      this.on('updated', function() { console.log('Updated Mixin!') })
  },

  getOpts: function() {
    return this.opts
  },

  setOpts: function(opts, update) {
    this.opts = opts
    if (!update) this.update()
    return this
  }
}

function  QueryStr(obj)
  {
  	if(obj)
  	{
		let query = Object.keys(obj)
             .map(key => encodeURIComponent(key) + '=' + encodeURIComponent(obj[key])).join('&');
        return query;
  	}
  	return null;
  }