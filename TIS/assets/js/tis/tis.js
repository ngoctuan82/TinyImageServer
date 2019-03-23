var OptsMixin = {
  APIKEY:null,
  API:null, //`/api/user/get/${this.APIKEY}`,
	
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