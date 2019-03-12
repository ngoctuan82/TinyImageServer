var OptsMixin = {
	
  // the `opts` argument is the option object received by the tag as well
  init: function(opts) {
      this.SESSION = this.opts.SESSION;
      console.log("Init Opts Mixin");
      console.log(opts);
      this.on('updated', function() { console.log('Updated!') })
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