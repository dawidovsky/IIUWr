
require 'sketchup.rb'

module PluginLista9
  module Kula

    def self.create_cube(r,posx=0,posy=0,posz=0)

      model = Sketchup.active_model
      model.start_operation('Kula', true)

      group = model.active_entities.add_group

      entities = group.entities

      center = [posx, posy, posz]
      sphere = entities.add_circle(center, X_AXIS, r)
      sphere_face = entities.add_face(sphere)
      sphere_face.reverse!

      path = entities.add_circle(center, Z_AXIS, r + 1.m)

      sphere_face.followme(path)

      entities.erase_entities(path)
      model.commit_operation
    end

      menu = UI.menu('Plugins')

      menu.add_item('Create Sphere'){
        prompts  = ["Radius","Pos X","Pos Y", "Pos Z"]
        defaults = [1.m, 0.m, 0.m, 0.m]
        list     = [""]
        input = UI.inputbox(prompts, defaults, list, "Sphere settings")
        
        r = input[0]
        posX = input[1]
        posY = input[2]
        posZ = input[3]

        self.create_cube(r,posX,posY,posZ)
      }

      file_loaded(__FILE__)

  end
end
