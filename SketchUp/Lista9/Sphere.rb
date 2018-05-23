require 'sketchup.rb'
require 'extensions.rb'

module PluginLista9
  module Kula

      ex = SketchupExtension.new('Sphere', 'Sphere/main')

      ex.description = 'Plugin tworzący kulę'
      ex.version     = '1.0.0'
      ex.copyright   = '© 2018'
      ex.creator     = 'Dawid Paluszak'

      Sketchup.register_extension(ex, true)

      file_loaded(__FILE__)
  end
end