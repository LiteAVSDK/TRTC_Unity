import resourceManager from "@ohos.resourceManager"
import fs from '@ohos.file.fs';
import common from '@ohos.app.ability.common';

export class RawFileUtils {

  static hasRawFile(rawFilePath: string): boolean {
    try {
      const context = getContext() as common.UIAbilityContext;
      const mgr = context.resourceManager;

      const rawFd = mgr.getRawFdSync(rawFilePath);
      if (rawFd && rawFd.fd > 0) {
        mgr.closeRawFdSync(rawFilePath);
        return true;
      }
    } catch (error) {
      console.error(`hasRawFile error: ${error.message}`);
    }
    return false;
  }

  static copyRawFile(fileName: string, targetDir: string): boolean {
    const context = getContext() as common.UIAbilityContext;
    const mgr = context.resourceManager;
    const tmpPath = `${targetDir}/${fileName}.tmp`;
    const finalPath = `${targetDir}/${fileName}`;

    try {
      try {
        if (!fs.accessSync(targetDir)) {
          fs.mkdirSync(targetDir);
        }
      } catch (error) {
        console.error(`Failed to create directory: ${error.message}`);
      }

      let content = mgr.getRawFileContentSync(fileName);
      let tmpFile = fs.openSync(tmpPath, fs.OpenMode.READ_WRITE | fs.OpenMode.CREATE);
      try {
        fs.writeSync(tmpFile.fd, content.buffer);
      } finally {
        fs.closeSync(tmpFile);
      }

      fs.renameSync(tmpPath, finalPath);
      return true;

    } catch (error) {
      console.error(`copyRawFile error: ${error.message}`);
      try {
        if (fs.accessSync(tmpPath)) {
          fs.unlinkSync(tmpPath);
        }
      } catch (cleanError) {
        console.error(`Cleanup error: ${cleanError.message}`);
      }
      return false;
    }
  }
}